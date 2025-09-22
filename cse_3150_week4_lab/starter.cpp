
#include <iostream>
#include <vector>
#include <stack>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <numeric> // needed for accumulate in compute_score
#include <random>

using namespace std;

void write_board_csv(const vector<vector<int>>& board, bool first) {
    ios_base::openmode mode = ios::app;
    if (first) mode = ios::trunc;
    ofstream fout("game_output.csv", mode);
    if (!fout) return;
    for (int r=0;r<4;r++){
        for (int c=0;c<4;c++){
            fout<<board[r][c];
            if (!(r==3 && c==3)) fout<<",";
        }
    }
    fout<<"\n";
}

void print_board(const vector<vector<int>>& board, bool first) {
    for (const auto &row : board) {
        for (auto val : row) {
            if (val == 0) cout << ".\t";
            else cout << val << "\t";
        }
        cout << "\n";
    }
    cout << endl;
    write_board_csv(board, first);
}

// TODO: use algorithms to spawn properly
void spawn_tile(vector<vector<int>>& board) {
    vector<pair<int, int>> empty_positions;
    for (int r = 0; r < 4; r++) {
        for (int c = 0; c < 4; c++) {
            if (board[r][c] == 0) {
                empty_positions.push_back({r, c});
            }
        }
    }
    
    if (empty_positions.empty()) return;
        static std::mt19937 gen(time(nullptr));
    std::uniform_int_distribution<> pos_dist(0, empty_positions.size() - 1);
    std::uniform_int_distribution<> val_dist(1, 10);
    
    // Select random position
    int idx = pos_dist(gen);
    pair<int, int> pos = empty_positions[idx];
    
    // 90% chance for 2, 10% chance for 4
    int value = (val_dist(gen) <= 9) ? 2 : 4;
    board[pos.first][pos.second] = value;
}

// TODO: implement using STL algorithms
bool move_left(vector<vector<int>>& board)
{
    bool moved = false;
    for (int r = 0; r < 4; r++) {
        vector<int> original_row = board[r];
        
        // Step 1: Compress - remove zeros using copy_if
        vector<int> compressed;
        copy_if(original_row.begin(), original_row.end(), back_inserter(compressed), 
                [](int val) { return val != 0; });
        compressed.resize(4, 0); // Pad with zeros
        
        // Step 2: Merge adjacent equal tiles
        for (int i = 0; i < 3; i++) {
            if (compressed[i] != 0 && compressed[i] == compressed[i + 1]) {
                compressed[i] *= 2;
                compressed[i + 1] = 0;
            }
        }
        
        // Step 3: Compress again to remove zeros created by merging
        vector<int> final_row;
        copy_if(compressed.begin(), compressed.end(), back_inserter(final_row), 
                [](int val) { return val != 0; });
        final_row.resize(4, 0); // Pad with zeros
        
        // Update the board and check if it changed
        board[r] = final_row;
        if (board[r] != original_row) {
            moved = true;
        }
    }
    return moved;
}

bool move_right(vector<vector<int>>& board){
    bool moved = false;
    for (int r = 0; r < 4; r++) {
        vector<int> original_row = board[r];
        
        // Reverse the row to process as left movement
        vector<int> reversed_row = board[r];
        reverse(reversed_row.begin(), reversed_row.end());
        
        // Step 1: Compress - remove zeros using copy_if
        vector<int> compressed;
        copy_if(reversed_row.begin(), reversed_row.end(), back_inserter(compressed), 
                [](int val) { return val != 0; });
        compressed.resize(4, 0);
        
        // Step 2: Merge adjacent equal tiles
        for (int i = 0; i < 3; i++) {
            if (compressed[i] != 0 && compressed[i] == compressed[i + 1]) {
                compressed[i] *= 2;
                compressed[i + 1] = 0;
            }
        }
        
        // Step 3: Compress again
        vector<int> final_row;
        copy_if(compressed.begin(), compressed.end(), back_inserter(final_row), 
                [](int val) { return val != 0; });
        final_row.resize(4, 0);
        
        // Reverse back to get right movement
        reverse(final_row.begin(), final_row.end());
        
        // Update board and check if changed
        board[r] = final_row;
        if (board[r] != original_row) {
            moved = true;
        }
    }
    return moved;
}
bool move_up(vector<vector<int>>& board){
    bool moved = false;
    for (int c = 0; c < 4; c++) {
        // Extract column into a vector
        vector<int> original_col;
        for (int r = 0; r < 4; r++) {
            original_col.push_back(board[r][c]);
        }
        
        // Step 1: Compress - remove zeros using copy_if
        vector<int> compressed;
        copy_if(original_col.begin(), original_col.end(), back_inserter(compressed), 
                [](int val) { return val != 0; });
        compressed.resize(4, 0);
        
        // Step 2: Merge adjacent equal tiles
        for (int i = 0; i < 3; i++) {
            if (compressed[i] != 0 && compressed[i] == compressed[i + 1]) {
                compressed[i] *= 2;
                compressed[i + 1] = 0;
            }
        }
        
        // Step 3: Compress again
        vector<int> final_col;
        copy_if(compressed.begin(), compressed.end(), back_inserter(final_col), 
                [](int val) { return val != 0; });
        final_col.resize(4, 0);
        
        // Put column back into board
        for (int r = 0; r < 4; r++) {
            board[r][c] = final_col[r];
        }
        
        if (final_col != original_col) {
            moved = true;
        }
    }
    return moved;
}


bool move_down(vector<vector<int>>& board){
    bool moved = false;
    for (int c = 0; c < 4; c++) {
        // Extract column into a vector
        vector<int> original_col;
        for (int r = 0; r < 4; r++) {
            original_col.push_back(board[r][c]);
        }
        
        // Reverse column to process as up movement
        vector<int> reversed_col = original_col;
        reverse(reversed_col.begin(), reversed_col.end());
        
        // Step 1: Compress - remove zeros using copy_if
        vector<int> compressed;
        copy_if(reversed_col.begin(), reversed_col.end(), back_inserter(compressed), 
                [](int val) { return val != 0; });
        compressed.resize(4, 0);
        
        // Step 2: Merge adjacent equal tiles
        for (int i = 0; i < 3; i++) {
            if (compressed[i] != 0 && compressed[i] == compressed[i + 1]) {
                compressed[i] *= 2;
                compressed[i + 1] = 0;
            }
        }
        
        // Step 3: Compress again
        vector<int> final_col;
        copy_if(compressed.begin(), compressed.end(), back_inserter(final_col), 
                [](int val) { return val != 0; });
        final_col.resize(4, 0);
        
        // Reverse back to get down movement
        reverse(final_col.begin(), final_col.end());
        
        // Put column back into board
        for (int r = 0; r < 4; r++) {
            board[r][c] = final_col[r];
        }
        
        if (final_col != original_col) {
            moved = true;
        }
    }
    return moved;
}


// TODO: compute score by summing board values
int compute_score(const vector<vector<int>>& board) {
    int total = 0;
    for (const auto& row : board) {
        total = accumulate(row.begin(), row.end(), total);
    }
    return total;
}

int main(){
    srand(time(nullptr));
    vector<vector<int>> board(4, vector<int>(4,0));
    spawn_tile(board);
    spawn_tile(board);

    stack<vector<vector<int>>> history;
    bool first=true;

    while(true){
        print_board(board, first);
        first=false;
        cout << "Score: " << compute_score(board) << "\n";
        cout<<"Move (w=up, a=left, s=down, d=right), u=undo, q=quit: ";
        char cmd;
        if (!(cin>>cmd)) break;
        if (cmd=='q') break;

        if (cmd=='u') {
            // TODO: Implement undo handling here using the history stack
            if (!history.empty()) {
                board = history.top();
                history.pop();
            }
            print_board(board,false);
            continue;
        }

        vector<vector<int>> prev = board;
        bool moved=false;
        if (cmd=='a') moved=move_left(board);
        else if (cmd=='d') moved=move_right(board);
        else if (cmd=='w') moved=move_up(board);
        else if (cmd=='s') moved=move_down(board);

        if (moved) {
            // TODO: push prev to history stack for undo
            history.push(prev);
            spawn_tile(board);
        }
    }
    return 0;
}
