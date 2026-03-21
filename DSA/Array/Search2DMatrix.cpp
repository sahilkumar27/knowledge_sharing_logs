class Solution {
public:

    // 🔍 Binary search inside a specific row
    bool SearchInRow(vector<vector<int>> &mat, int target, int row)
    {
        int n = mat[0].size();   // number of columns

        int start = 0, end = n - 1;

        while (start <= end)
        {
            int mid = start + (end - start) / 2;

            // 🎯 target found
            if (target == mat[row][mid])
            {
                return true;
            }
            // 🔼 move right
            else if (target > mat[row][mid])
            {
                start = mid + 1;
            }
            // 🔽 move left
            else
            {
                end = mid - 1;
            }
        }

        // ❌ target not found in this row
        return false;
    }


    // 🔍 Main function: binary search on rows
    bool searchMatrix(vector<vector<int>> &mat, int target)
    {
        int n = mat[0].size();       // number of columns
        int startRow = 0;
        int endRow = mat.size() - 1; // number of rows - 1

        while (startRow <= endRow)
        {
            int mid = startRow + (endRow - startRow) / 2;

            // ✅ Check if target lies in this row's range
            if (target >= mat[mid][0] && target <= mat[mid][n - 1])
            {
                // 👉 Apply binary search in this row
                return SearchInRow(mat, target, mid);
            }
            // 🔼 Target is in lower rows
            else if (target > mat[mid][n - 1])
            {
                startRow = mid + 1;
            }
            // 🔽 Target is in upper rows
            else
            {
                endRow = mid - 1;
            }
        }

        // ❌ Target not found in any row
        return false;
    }
};

// Time Complexity: O(log(m) + log(n)) where m is the number of rows and n is the number of columns in the matrix.
// Space Complexity: O(1) as we are using only constant extra space.