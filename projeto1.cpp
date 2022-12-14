//
// Created by henriquesilva on 12/11/22.
//
#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <unordered_map>

using namespace std;

typedef vector<int> Board;
unordered_map<unsigned long long, unsigned long> memorization;

unsigned long long hashFunction(Board board, int n){
    unsigned long long h = board[0];
    for (int i = 1; i < n; i ++ )
        h += h*10 + board[i];
    return h;
}

/* initialises the b */
int parse_input(Board &board){
    int n,m;                    /* n - rows; m - columns */
    int j;
    cin >> n >> m;
    board = vector<int>(n);
    for(int i=0;i<n || j == EOF;i++){
        cin >> j;
        board[i] = j;
    }
    return n;
}

int find_square_index(Board b){
    int max_idx = (int)(max_element(b.begin(),b.end()) - b.begin());
    return max_idx;
}


int max_size_square(Board p, int row) {
    int tam = (int)p.size();
    int i;
    for (i = row; i < tam; i++){
        if(p[i] < p[row]) break;
    }
    return min(i - row, p[row]);
}

/* there are only squares of size 1*1 */
bool only_1_squares(Board b,int n){
    bool ok = true;
    for (int i = 0; i < n - 1; i++) {
        if (b[i] > 1){
            ok = false;
            break;
        }
    }
    return ok;
}


unsigned long checkMaxCombinations(Board& board, int row, int ana_row, int side){
    unsigned long  total;
    bool full = false;
    unsigned long key = hashFunction(board,row);
    if(memorization.count(key) == 1) {
        return memorization[key];
    }
    if(side==-1) {
        if(only_1_squares(board,row)){total = 1; full = true;}
        else{
            ana_row = find_square_index(board);
            side = max_size_square(board, ana_row);
        }
    }
    if(!full) {
        if (only_1_squares(board, row)) {
            if (side == 1) total = 1;
            else total = 1 + checkMaxCombinations(board, row, ana_row, side - 1);
        } else {
            for (int i = 0; i < side; i++) {
                board[ana_row + i] -= side;
            }
            if (side == 1) {
                total = checkMaxCombinations(board, row, 0, -1);
                for (int i = 0; i < side; i++) {
                    board[ana_row + i] += side;
                }
            }
            else {
                total = checkMaxCombinations(board, row, 0, -1);
                for (int i = 0; i < side; i++) {
                    board[ana_row + i] += side;
                }
                total += checkMaxCombinations(board, row, ana_row, side - 1);
            }
        }
        memorization[hashFunction(board,row) ] = total;
    }
    return total;
}

int main(){
    Board b;
    int rows = parse_input(b);
    if(rows == 0 || b[rows - 1] == 0) cout << 0 << endl; // verifies if the board is full
    else if(only_1_squares(b,rows)) cout << 1 << endl;
    else {
        int begin = find_square_index(b);
        int side = max_size_square(b, begin);
        cout << checkMaxCombinations(b, rows, begin, side) << endl;
    }
    return 0;
}

