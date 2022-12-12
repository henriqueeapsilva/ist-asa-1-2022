//
// Created by henriquesilva on 12/11/22.
//
#include <iostream>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;

typedef vector<int> Board;

map<vector<int>,long long> memory;

/* initialises the b */
void parse_input(Board &board){
    int n,m;                    /* n - rows; m - columns */
    int j;
    cin >> n >> m;
    board = vector<int>(n);
    for(int i=0;i<n;i++){
        cin >> j;
        board[i] = j;
    }
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

bool fullBoard(Board b, int n){
    bool ok = true;
    for(int i=0;i<n;i++)
        if(b[i]!= 0) ok = false;
    return ok;
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


long long checkMaxCombinations(const Board& board, int row, int ana_row, int side){
    long long total;
    bool full = false;
    if(memory.count(board) == 1) {
        total = memory[board];
        full = true;
    }
    if(side==-1) {
        if(fullBoard(board,row)){total = 1; full = true;}
        ana_row = find_square_index(board);
        side = max_size_square(board, ana_row);
    } 
    if(!full){
        Board new_board = board;
        for(int i = 0; i < side; i++){
            new_board[ana_row + i] -= side;
        }
        if(only_1_squares(board,row)){
            if(side == 1) total = 1;
            else total =  1 + checkMaxCombinations(board, row, ana_row, side - 1);
        }
        else {
            if (side == 1) total = checkMaxCombinations(new_board, row, 0, -1);
            else total = checkMaxCombinations(board, row, ana_row , side-1) + checkMaxCombinations(new_board, row, 0, -1);
        }
        memory[board] = total;
    }
    return total;
}

int main(){
    Board b;
    long long combinations;
    parse_input(b);
    if(fullBoard(b,(int)b.size())) cout << 0 << endl; // verifies if the board is full 
    else {
        int begin = find_square_index(b);
        int side = max_size_square(b, begin);
        combinations = checkMaxCombinations(b, (int) b.size(), begin, side);
        cout << combinations << endl;
    }
    return 0;
}