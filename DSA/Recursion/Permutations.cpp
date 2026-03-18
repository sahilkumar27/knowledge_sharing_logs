void getPrams(vector<int> &nums, int idx, vector<vector<int>> &ans)
{

    // Base Condition
    if (idx == nums.size())
    {
        ans.push_back({nums});
        return;
    }

    for (int i = idx; i < nums.size(); i++)
    {
        swap(nums[idx], nums[i]);       // idx place => ith element choice

        getPrams(nums, idx + 1, ans);       // Recusive calling

        swap(nums[idx], nums[i]); // BackTracking
    }
}
vector<vector<int>> permute(vector<int> &nums)
{
    vector<vector<int>> ans;
    getPrams(nums, 0, ans);
    return ans;
}

// Time Complexity: O(N! * N) => O(N!)
// Space Complexity: O(N! * N) => O(N!) (for storing ans)