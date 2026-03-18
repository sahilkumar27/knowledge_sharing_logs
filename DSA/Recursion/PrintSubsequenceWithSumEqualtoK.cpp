#include <bits/stdc++.h>
using namespace std;

void printSubsequence(vector<int>& nums, int k, int ind, vector<int>& ans)
{
    // Base Case: if required sum achieved
    if (k == 0)
    {
        for (int i = 0; i < ans.size(); i++)
        {
            cout << ans[i] << " ";
        }
        cout << endl;
        return;
    }

    // Base Case: reached end or sum becomes negative
    if (ind == nums.size() || k < 0)
        return;

    // Take the current element
    ans.push_back(nums[ind]);
    printSubsequence(nums, k - nums[ind], ind + 1, ans);

    // Backtrack
    ans.pop_back();

    // Do not take the element
    printSubsequence(nums, k, ind + 1, ans);
}

int main()
{
    vector<int> nums = {1,2,1};
    int k = 2;

    vector<int> ans;

    printSubsequence(nums, k, 0, ans);

    return 0;
}