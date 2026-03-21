void helper(int ind, int sum, vector<int> &arr, vector<int> &ans)
{
    // base case
    if (ind == arr.size())
    {
        ans.push_back(sum);
        return;
    }

    // take
    helper(ind + 1, sum + arr[ind], arr, ans);

    // notTake
    helper(ind + 1, sum, arr, ans);
}
vector<int> subsetSums(vector<int> &arr)
{
    // code here
    int sum = 0;
    vector<int> ans;
    helper(0, sum, arr, ans);
    sort(ans.begin(), ans.end());
    return ans;
}
// Time complexity: O(2^n*log(2^n))=O(n*2^n)
// Space complexity: O(n)