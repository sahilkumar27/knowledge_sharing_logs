#include <bits/stdc++.h>
using namespace std;

vector<int> productExpectedSelf(vector<int>& nums)
{
    int n = nums.size();
    vector<int> ans(n, 1);  //Create a vector of size n where every element is initialized to 1.

    int leftProduct = 1;
    for(int i=0;i<n;i++){
        ans[i]=leftProduct;
        leftProduct *= nums[i];
    }

    int rightProduct =1;
    for (int i = n-1; i >= 0; i--)
    {
        ans[i] *= rightProduct;
        rightProduct *= nums[i];
    }
    return ans;
    
}

int main()
{
    int n;
    cout<<"Enter the size of the array \n";
    cin>>n;
    vector<int> nums(n);
    for (int i = 0; i < n; i++)
    {
        cin>>nums[i];
    }

    vector<int> ans = productExpectedSelf(nums);
    for (int i = 0; i < ans.size(); i++)
    {
        cout<<ans[i]<<" ";
    }
    
    return 0;
    
}

/* LC: 238

Example 1:
Input: nums = [1,2,3,4]
Output: [24,12,8,6]

Example 2:
Input: nums = [-1,1,0,-3,3]
Output: [0,0,9,0,0]


*/