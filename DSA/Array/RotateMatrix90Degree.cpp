// Brute Force Approach
#include <iostream>
#include <vector>
using namespace std;

int main() {

    vector<vector<int>> matrix = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}
    };

    int n = matrix.size();

    // Extra matrix — SC = n²
    vector<vector<int>> ans(n, vector<int>(n));

    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < n; j++)
        {
            ans[j][n-1-i] = matrix[i][j];   // Col = N-1-i
        }
    }

    // Print result
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++)
            cout << ans[i][j] << " ";
        cout << endl;
    }
}
// Index starts from 0, so last index = n-1
// Rotating clockwise → row i becomes column, but reversed → n-1-i




// Optimal Approach ----------------------
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {

    vector<vector<int>> matrix = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}
    };

    int n = matrix.size();

    // Step 1: Transpose — swap(matrix[i][j], matrix[j][i])
    for(int i = 0; i < n; i++)
    {
        for(int j = i+1; j < n; j++)   // j = i+1 avoids double swap
        {
            swap(matrix[i][j], matrix[j][i]);
        }
    }

    // Step 2: Reverse each row
    for(int i = 0; i < n; i++)
    {
        reverse(matrix[i].begin(), matrix[i].end());
    }

    // Print
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++)
            cout << matrix[i][j] << " ";
        cout << endl;
    }
}

/*
Why j = i+1 in transpose?
If j starts from 0, every swap happens twice and matrix reverts to original. Starting j = i+1 swaps only upper triangle → correct transpose.
*/