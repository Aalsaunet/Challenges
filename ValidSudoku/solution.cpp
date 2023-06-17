#include <vector>

using namespace std;

class Solution {
public:
    bool isValidSudoku(vector<vector<char> > &board) {
        
        int rows[9][9] = {false}, colums[9][9] = {false}, boxes[9][9] = {false};
        
        for(int i = 0; i < board.size(); ++ i)
            for(int j = 0; j < board[i].size(); ++ j)
                if(board[i][j] != '.') { // we've encountered a filled cell
                    int num = board[i][j] - '0' - 1; // from ASCII to 0-indexed int
                    int k = i / 3 * 3 + j / 3; // Finds box number (0-9)
                    if(rows[i][num] || colums[j][num] || boxes[k][num])
                        return false;
                    rows[i][num] = colums[j][num] = boxes[k][num] = true;
                }      
        return true;
    }
};