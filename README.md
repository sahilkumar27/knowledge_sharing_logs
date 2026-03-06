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

**Problem:** Given an array `nums`, return an array `ans` such that: 
ans[i] = product of all elements of nums except nums[i]

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
- Time: $O(n)$
- Space: $O(n)$ for output array (not counted), $O(1)$ extra space

---

### 4. Set Matrix Zeros

**Problem:** Given an `m x n` matrix, if an element is 0, set its entire row and column to 0. Do it in-place.

**Approach:**
1. **Create marker arrays:** Initialize two arrays - `row[m]` and `col[n]` - both filled with 1s initially.
2. **First pass (mark zeros):** Traverse the entire matrix. When you find a zero at position `[i][j]`:
   - Set `row[i] = 0` to mark that row i needs to be zeroed
   - Set `col[j] = 0` to mark that column j needs to be zeroed
3. **Second pass (set zeros):** Traverse the matrix again. For each position `[i][j]`:
   - If `row[i] == 0` OR `col[j] == 0`, set `matrix[i][j] = 0`

**Why this works:**
- By using separate marker arrays, we avoid the problem of overwriting values we still need to check
- We only need to check each cell once in each pass
- The marker arrays remember the original positions of zeros

**Code:**
```cpp
void setZeroes(vector<vector<int>>& matrix) {
    int rowSize = matrix.size(), colSize = matrix[0].size();
    
    // Marker arrays to track which rows and columns need to be zeroed
    vector<int> row(rowSize, 1);
    vector<int> col(colSize, 1);
    
    // First pass: identify all zeros and mark their rows/columns
    for(int i = 0; i < rowSize; i++) {
        for(int j = 0; j < colSize; j++) {
            if(matrix[i][j] == 0) {
                row[i] = 0;  // Mark this row
                col[j] = 0;  // Mark this column
            }
        }
    }
    
    // Second pass: set zeros based on markers
    for(int i = 0; i < rowSize; i++) {
        for(int j = 0; j < colSize; j++) {
            if(row[i] == 0 || col[j] == 0) {
                matrix[i][j] = 0;
            }
        }
    }
}
```
**Complexity:**
- Time: $O(m \times n)$ - we traverse the matrix twice
- Space: $O(m + n)$ - for the row and column marker arrays

**Example:**
```
Input:                 Output:
[[1, 1, 1],            [[1, 0, 1],
 [1, 0, 1],    -->      [0, 0, 0],
 [1, 1, 1]]             [1, 0, 1]]
```
**Complexity:**
- Time: $O(n)$
- Space: $O(n)$

---

### 5. Count Number of Subsequence With Sum K

**Problem:** Given an array of integers `nums` and a target sum `K`, count the number of subsequences whose elements sum up to exactly K.

**Approach:**
1. Use recursive backtracking to explore all possible subsequences.
2. At each index, we have two choices: include the current element or exclude it.
3. **Base Cases:**
   - If target becomes negative, no valid subsequence exists (return 0).
   - If target becomes 0, we found a valid subsequence (return 1).
   - If we reach the end of array, directly return 0.
4. **Recursive Cases:**
   - Take the element: recursively count with target reduced by current element.
   - Don't take: recursively count with same target.
5. Return the sum of both possibilities.

**Code:**
```cpp
int countSubSequence(int ind, vector<int>& nums, int target){
    // base case
    if(target < 0){      
        return 0;
    }
    if(target == 0){
        return 1;
    }
    if(ind == nums.size()){
        return 0;
    }
    // take the element
    int take = countSubSequence(ind + 1, nums, target - nums[ind]);

    // not take the element
    int notTake = countSubSequence(ind + 1, nums, target);

    // return the count of subsequence
    return take + notTake;
}
    
int numSubseq(vector<int>& nums, int target) {
    int ind = 0;
    return countSubSequence(ind, nums, target);
}
```

**Complexity:**
- Time: $O(2^n)$ - exploring all subsequences
- Space: $O(n)$ - recursion stack depth
