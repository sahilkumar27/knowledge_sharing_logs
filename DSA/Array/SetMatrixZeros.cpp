void setZeroes(vector<vector<int>> &matrix)
{
    int rowSize = matrix.size(), colSize = matrix[0].size();
    // declaring row array to store 0 at particular rowIndex, using this particular index will set that particular row to be 0
    vector<int> row(rowSize, 1);
    // declaring col array to store 0 at particular column Index, using this particular index will set that particular col to be 0
    vector<int> col(colSize, 1);
    for (int i = 0; i < rowSize; i++)
    {
        for (int j = 0; j < colSize; j++)
        {
            if (matrix[i][j] == 0)
            {
                // storing the row index
                row[i] = 0;
                // storing the column index
                col[j] = 0;
            }
        }
    }

    // marking the row and column as 0
    for (int i = 0; i < rowSize; i++)
    {
        for (int j = 0; j < colSize; j++)
        {
            if (row[i] == 0 || col[j] == 0)
            {
                matrix[i][j] = 0;
            }
        }
    }
}