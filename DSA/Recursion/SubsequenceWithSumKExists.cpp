bool checkIfExists(int index, int n, vector<int> &arr, int k, int sum)
{
        // base case
        if (index == n)
        {
                return sum == k;
        }

        // recursion
        bool take = checkIfExists(index + 1, n, arr, k, sum + arr[index]);
        bool notTake = checkIfExists(index + 1, n, arr, k, sum);

        return take || notTake;
}
bool checkSubsequenceSum(int n, vector<int> &arr, int k)
{
        // Code here
        int sum = 0;
        return checkIfExists(0, n, arr, k, sum);
}