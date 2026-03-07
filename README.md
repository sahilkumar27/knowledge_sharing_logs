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

---

### 6. Maximum Subarray (Kadane's Algorithm)

**Problem:** Given an integer array `nums`, find the contiguous subarray (containing at least one number) which has the largest sum and return its sum.

**Example:**
```
Input: nums = [-2, 1, -3, 4, -1, 2, 1, -5, 4]
Output: 6
Explanation: The subarray [4, -1, 2, 1] has the largest sum = 6
```

**Approach (Kadane's Algorithm):**

The key insight is: at each position, we have two choices:
1. **Extend** the previous subarray by including the current element
2. **Start fresh** from the current element

We choose whichever gives us a larger sum!

**Step-by-step walkthrough:**
```
Array: [-2, 1, -3, 4, -1, 2, 1, -5, 4]

i=0: currentMax = -2, maxSum = -2
     (Starting with first element)

i=1: currentMax = max(1, -2+1) = max(1, -1) = 1
     maxSum = max(-2, 1) = 1
     (Better to start fresh from 1 than extend -2)

i=2: currentMax = max(-3, 1-3) = max(-3, -2) = -2
     maxSum = 1
     (Extending is less bad than starting from -3)

i=3: currentMax = max(4, -2+4) = max(4, 2) = 4
     maxSum = max(1, 4) = 4
     (Better to start fresh from 4)

i=4: currentMax = max(-1, 4-1) = max(-1, 3) = 3
     maxSum = 4
     (Extending keeps sum positive)

i=5: currentMax = max(2, 3+2) = 5
     maxSum = max(4, 5) = 5

i=6: currentMax = max(1, 5+1) = 6
     maxSum = max(5, 6) = 6

i=7: currentMax = max(-5, 6-5) = 1
     maxSum = 6
     (Even though we hit -5, extending keeps sum positive)

i=8: currentMax = max(4, 1+4) = 5
     maxSum = 6
     (Final answer is 6)
```

**Why this works:**
- `currentMax` tracks the best sum we can get ending at current position
- `maxSum` tracks the overall best sum we've seen
- If `currentMax` becomes negative, it's better to start fresh
- This avoids checking all possible subarrays (which would be $O(n^2)$ or $O(n^3)$)

**Code:**
```cpp
int maxSubArray(vector<int>& nums) {
    int maxSum = nums[0];
    int currentMax = nums[0];
    
    for(int i = 1; i < nums.size(); i++) {
        // Either extend the previous subarray or start fresh
        currentMax = max(nums[i], currentMax + nums[i]);
        
        // Update the overall maximum
        maxSum = max(maxSum, currentMax);
    }
    
    return maxSum;
}
```

**Complexity:**
- Time: $O(n)$ - single pass through the array
- Space: $O(1)$ - only using two variables

**Key Takeaway:** Kadane's algorithm is elegant because it makes a locally optimal choice at each step (greedy approach), which happens to give us the globally optimal solution!

---

### 7. Pascal's Triangle

**Problem:** Given an integer `numRows`, return the first `numRows` rows of Pascal's Triangle.

In Pascal's Triangle:
- The first and last element of every row is `1`.
- Every other element is the **sum of the two elements directly above it** (from the previous row).

**Example:**
```
Input: numRows = 5
Output:
[
  [1],
  [1, 1],
  [1, 2, 1],
  [1, 3, 3, 1],
  [1, 4, 6, 4, 1]
]
```

**Visual Explanation:**
```
Row 0:        [1]
Row 1:       [1, 1]
Row 2:      [1, 2, 1]          ← 2 = 1 + 1 (sum of the two above)
Row 3:     [1, 3, 3, 1]        ← 3 = 1 + 2, 3 = 2 + 1
Row 4:    [1, 4, 6, 4, 1]      ← 4 = 1 + 3, 6 = 3 + 3, 4 = 3 + 1
```

**Approach:**
1. Start with an empty result array `ans`.
2. For each row `i` (0-indexed), create a row vector of size `i + 1` initialized with `0`.
3. **Base case (row 0):** Set `row[0] = 1`.
4. **All other rows:** For each position `j` in the current row:
   - Look at the element directly above-left: `ans[i-1][j-1]` (use 0 if `j-1 < 0`)
   - Look at the element directly above: `ans[i-1][j]` (use 0 if `j` is out of bounds of previous row)
   - Set `row[j] = prevLeft + prevUp`
5. Push the completed row into `ans`.

**How each element is computed:**

For position `j` in row `i`, we look at row `i-1`:
```
prevLeft = ans[i-1][j-1]   → element to the upper-left  (0 if j == 0)
prevUp   = ans[i-1][j]     → element directly above      (0 if j == previous row's size)
row[j]   = prevLeft + prevUp
```

This naturally handles the boundary: the first and last elements of each row will always be `1` because one of the two lookups falls out of bounds (returns 0) and the other returns `1`.

**Step-by-step walkthrough for numRows = 4:**
```
i=0: row = [1]                        (base case)
     ans = [[1]]

i=1: j=0: prevLeft = 0 (j-1 < 0), prevUp = ans[0][0] = 1  → row[0] = 1
     j=1: prevLeft = ans[0][0] = 1,  prevUp = 0 (out of bounds) → row[1] = 1
     ans = [[1], [1,1]]

i=2: j=0: prevLeft = 0, prevUp = ans[1][0] = 1  → row[0] = 1
     j=1: prevLeft = ans[1][0] = 1, prevUp = ans[1][1] = 1 → row[1] = 2
     j=2: prevLeft = ans[1][1] = 1, prevUp = 0 (out of bounds) → row[2] = 1
     ans = [[1], [1,1], [1,2,1]]

i=3: j=0: 0 + 1 = 1
     j=1: 1 + 2 = 3
     j=2: 2 + 1 = 3
     j=3: 1 + 0 = 1
     ans = [[1], [1,1], [1,2,1], [1,3,3,1]]
```

**Code:**
```cpp
vector<vector<int>> generate(int numRows) {
    vector<vector<int>> ans;
    int i = 0;
    while (i < numRows) {
        vector<int> row(i + 1, 0);  // row i has i+1 elements, all init to 0
        if (i == 0) {
            row[0] = 1;             // base case: first row is just [1]
        } else {
            for (int j = 0; j < row.size(); j++) {
                // upper-left neighbor: 0 if j is at the left boundary
                int prevLeft = (j - 1 >= 0) ? ans[i - 1][j - 1] : 0;
                // directly above neighbor: 0 if j is at the right boundary
                int prevUp = (j == (int)ans[i - 1].size()) ? 0 : ans[i - 1][j];
                row[j] = prevLeft + prevUp;
            }
        }
        ans.push_back(row);
        i++;
    }
    return ans;
}
```

**Complexity:**
- Time: $O(n^2)$ — we fill every cell of the triangle; row `i` has `i+1` elements, so total cells = $1 + 2 + ... + n = \frac{n(n+1)}{2}$
- Space: $O(n^2)$ — we store all rows in the result (output space)

**Key Takeaway:** Pascal's Triangle is a great example of building a solution **row by row using previously computed results**. Each new row only depends on the immediately preceding row, making this an intuitive introduction to dynamic programming thinking.