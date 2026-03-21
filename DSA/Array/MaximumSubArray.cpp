int maxSubArray(vector<int> &nums)
{
    int maxSum = nums[0], currentMax = nums[0];
    for (int i = 1; i < nums.size(); i++)
    {
        currentMax = max(nums[i], currentMax + nums[i]);
        maxSum = max(maxSum, currentMax);
    }
    return maxSum;
}

// Time Complexity: O(n) where n is the size of the input array.
// Space Complexity: O(1) as we are using only a constant amount of extra space