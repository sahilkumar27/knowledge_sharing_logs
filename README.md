# knowledge_sharing_logs
Day wise notes
## DSA Solutions

### 1. Next Permutation

**Problem:** Rearrange numbers into the lexicographically next greater permutation of numbers. If such arrangement is not possible, it must rearrange it as the lowest possible order (i.e., sorted in ascending order).

**Approach:**
1. Find the rightmost element (pivot) which is smaller than its next element.
2. If no such element exists, reverse the whole array (it's the last permutation).
3. Otherwise, find the rightmost element greater than the pivot and swap them.
4. Reverse the subarray to the right of the pivot.

**Code:**
```cpp
void nextPermutation(vector<int>& nums) {
	int pivot = -1, n = nums.size();
	for (int i = n - 2; i >= 0; i--) {
		if (nums[i] < nums[i + 1]) {
			pivot = i;
			break;
		}
	}
	if (pivot == -1) {
		reverse(nums.begin(), nums.end());
	} else {
		for (int i = n - 1; i > pivot; i--) {
			if (nums[i] > nums[pivot]) {
				swap(nums[pivot], nums[i]);
				break;
			}
		}
		reverse(nums.begin() + pivot + 1, nums.end());
	}
}
```
**Complexity:**
- Time: $O(n)$
- Space: $O(1)$

---

### 2. Buy & Sell Stock (Best Time)

**Problem:** Given an array of prices, where prices[i] is the price of a given stock on day i, find the maximum profit you can achieve by buying and selling once.

**Approach:**
1. Track the minimum price so far.
2. For each price, calculate the profit if sold today (current price - min price so far).
3. Update the maximum profit if this profit is higher.
4. Update the minimum price if the current price is lower.

**Code:**
```cpp
int maxProfit(vector<int>& prices) {
	int minBuy = prices[0], profit = 0;
	for (int i = 1; i < prices.size(); i++) {
		profit = max(profit, prices[i] - minBuy);
		minBuy = min(minBuy, prices[i]);
	}
	return profit;
}
```
**Complexity:**
- Time: $O(n)$
- Space: $O(1)$

### 3. Product of Array Except Self

**Problem:** Given an integer array nums, return an array answer such that answer[i] is equal to the product of all the elements of nums except nums[i]. The product of any prefix or suffix of nums is guaranteed to fit in a 32-bit integer.

**Approach**
1. Create an output array ans initialized with 1.
2. Traverse from left → store prefix product (product of elements before index).
3. Traverse from right → maintain suffix product (product of elements after index).
4. Multiply prefix and suffix to get final answer.

**Code**
```cpp
vector<int> productExceptSelf(vector<int>& nums) {
    int n = nums.size();
    vector<int> ans(n, 1);

    int leftProduct = 1;
    for(int i = 0; i < n; i++){
        ans[i] = leftProduct;
        leftProduct *= nums[i];
    }

    int rightProduct = 1;
    for(int i = n - 1; i >= 0; i--){
        ans[i] *= rightProduct;
        rightProduct *= nums[i];
    }

    return ans;
}
```
**Complexity:**
- Time: $O(n²)$
- Space: $O(n)$
