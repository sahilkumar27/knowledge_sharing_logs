vector<vector<int>> generate(int numRows)
{
    vector<vector<int>> ans;
    int i = 0;
    while (i < numRows)
    {
        vector<int> row(i + 1, 0);
        // if it's the first row then we will fill it with 1 as the first row of Pascal's triangle is always 1.
        if (i == 0)
        {
            row[0] = 1;
        }
        else
        {
            // for other rows we will fill the values based on the previous row.
            for (int j = 0; j < row.size(); j++)
            {
                // the value of the current cell will be the sum of the value of the previous row's left cell and the previous row's up cell.
                int prevLeft = j - 1 >= 0 ? ans[i - 1][j - 1] : 0;
                int prevUp = j == ans[i - 1].size() ? 0 : ans[i - 1][j];
                row[j] = prevLeft + prevUp;
            }
        }
        // we will push the current row to the answer vector.
        ans.push_back(row);
        i++;
    }
    return ans;
}

// Time Complexity: O(numRows^2) where numRows is the number of rows in the Pascal's triangle.
// Space Complexity: O(numRows^2) as we are storing the entire Pascal's triangle in a 2D vector.