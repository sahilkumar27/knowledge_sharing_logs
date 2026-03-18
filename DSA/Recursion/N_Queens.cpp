#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Solution {
public:
    bool isSafe(vector<string>& board, int row, int col, int n) {

        // horizontal (row where we want to place the queen)
        for (int j = 0; j < n; j++) {
            if (board[row][j] == 'Q')
                return false;
        }

        // vertical (column where we want to place the queen)
        for (int i = 0; i < n; i++) {
            if (board[i][col] == 'Q')
                return false;
        }

        // left diagonal (top-left to bottom-right)
        for (int i = row, j = col; i >= 0 && j >= 0; i--, j--) {
            if (board[i][j] == 'Q')
                return false;
        }

        // right diagonal (top-right to bottom-left)
        for (int i = row, j = col; i >= 0 && j < n; i--, j++) {
            if (board[i][j] == 'Q')
                return false;
        }

        return true;
    }

    void nQueens(vector<string>& board, int row, int n,
                 vector<vector<string>>& ans) {

        if (row == n) {
            ans.push_back(board);
            return;
        }

        for (int j = 0; j < n; j++) {
            if (isSafe(board, row, j, n)) {
                board[row][j] = 'Q';
                nQueens(board, row + 1, n, ans);
                board[row][j] = '.';
            }
        }
    }

    vector<vector<string>> solveNQueens(int n) {
        vector<string> board(n, string(n, '.'));        // board = Current chessboard
        vector<vector<string>> ans;
        nQueens(board, 0, n, ans);
        return ans;
    }
};


int main() {
    int n;
    cout << "Enter value of n: ";
    cin >> n;               // n = 4 (4 queens) (N X N chessboard)

    Solution sol;
    vector<vector<string>> result = sol.solveNQueens(n);

    cout << "\nTotal solutions: " << result.size() << endl;

    for (int idx = 0; idx < result.size(); idx++) {
        cout << "\nSolution " << idx + 1 << ":\n";
        for (auto row : result[idx]) {
            cout << row << endl;
        }
    }

    return 0;
}