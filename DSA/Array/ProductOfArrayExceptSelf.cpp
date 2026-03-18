#include <bits/stdc++.h>
using namespace std;

vector<int> productExpectedSelf(vector<int>& nums)
{
    int n = nums.size();
    vector<int> ans(n, 1);  //Create a vector of size n where every element is initialized to 1.

    // I Compute prefix (left) product and store it in ans vector.
    int leftProduct = 1;
    for(int i=0;i<n;i++){
        ans[i]=leftProduct;
        leftProduct *= nums[i];
    }

    // I traverse from the right and maintain a suffix (right) product, multiplying it with the corresponding prefix product in the ans vector to get the final product for each index.
    int rightProduct =1;
    for (int i = n-1; i >= 0; i--)
    {
        ans[i] *= rightProduct;
        rightProduct *= nums[i];
    }
    return ans;
    
    // Time Complexity: O(n) - We traverse the input array twice, once for calculating the prefix product and once for calculating the suffix product.
    // Space Complexity: O(1) - We are using the ans vector to store the final result, and we are not using any additional data structures that grow with the input size. The space used by the ans vector is not considered extra space since it is required for the output.
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