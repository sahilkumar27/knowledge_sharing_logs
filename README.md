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
- Space: $O(1)$ (excluding output array)

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

---

### 8. Letter Combinations of a Phone Number

**Problem:** Given a string containing digits from `2-9`, return all possible letter combinations that the number could represent — just like the letters on a telephone keypad.

**Phone Keypad Mapping:**
```
2 → abc     3 → def
4 → ghi     5 → jkl     6 → mno
7 → pqrs    8 → tuv     9 → wxyz
```

**Example:**
```
Input:  digits = "23"
Output: ["ad", "ae", "af", "bd", "be", "bf", "cd", "ce", "cf"]
```

---

**Approach (Recursion / Backtracking):**

The idea is to process one digit at a time. For the current digit, try appending **each of its mapped letters** to the string built so far, and then recurse for the next digit.

Think of it like a tree where:
- Each **level** of the tree corresponds to one digit
- Each **branch** from a node corresponds to one possible letter for that digit
- A **leaf node** (when we've processed all digits) gives us one complete combination

**Step-by-step Approach:**
1. Create a `map` array where index `i` stores the letters for digit `i` (indices 0 and 1 are empty since `0` and `1` have no letters).
2. Call the recursive helper starting at index `0` with an empty `letter` string.
3. **Base case:** If `ind == digits.length()`, we've used every digit — push `letter` into `ans` and return.
4. **Recursive case:** Get the letters for `digits[ind]`. Loop through each letter, append it to `letter`, and recurse with `ind + 1`.

---

**Code:**
```cpp
void helper(int ind, string &digits, string letter, vector<string> &map, vector<string> &ans) {
    // Base case: all digits have been processed → valid combination found
    if (ind == digits.length()) {
        ans.push_back(letter);
        return;
    }

    // Get the letters mapped to the current digit
    string temp = map[digits[ind] - '0'];

    // Try each letter for the current digit
    for (int i = 0; i < temp.length(); i++) {
        helper(ind + 1, digits, letter + temp[i], map, ans);
    }
}

vector<string> letterCombinations(string digits) {
    // Map index → letters (indices 0 and 1 are unused)
    vector<string> map = {"", "", "abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz"};
    string letter = "";
    vector<string> ans;
    helper(0, digits, letter, map, ans);
    return ans;
}
```

---

**Understanding the Code — Line by Line:**

| Part | What it does |
|------|-------------|
| `digits[ind] - '0'` | Converts char digit (e.g. `'2'`) to integer index `2` to look up the map |
| `map[digits[ind]-'0']` | Gets the letters for the current digit e.g. `"abc"` for digit `2` |
| `letter + temp[i]` | Builds the combination string character by character (does NOT modify original, passes a copy) |
| `helper(ind+1, ...)` | Moves to the next digit after fixing the current character |
| Base case `ind == digits.length()` | All digits are consumed → one full combination is ready |

---

**Recursion Tree for Input `"23"`:**

```
                        helper(ind=0, letter="")
                        digits[0]='2' → "abc"
               /                  |                  \
     letter+='a'             letter+='b'           letter+='c'
  helper(ind=1,"a")       helper(ind=1,"b")      helper(ind=1,"c")
  digits[1]='3'→"def"    digits[1]='3'→"def"   digits[1]='3'→"def"
    /     |     \           /     |     \          /     |     \
  "ad"  "ae"  "af"       "bd"  "be"  "bf"      "cd"  "ce"  "cf"
  ✅    ✅    ✅          ✅    ✅    ✅         ✅    ✅    ✅
```

- **Level 0 → Level 1:** We fix the letter for digit `2` (`a`, `b`, or `c`)
- **Level 1 → Level 2 (leaf):** We fix the letter for digit `3` (`d`, `e`, or `f`)
- At every leaf, `ind == digits.length()` → combination is complete and pushed to `ans`

**Result:** `["ad", "ae", "af", "bd", "be", "bf", "cd", "ce", "cf"]`

---

**Dry Run for `digits = "23"`:**

```
map[2] = "abc",  map[3] = "def"

Call: helper(0, "23", "")
  └─ temp = "abc"
  ├─ i=0 → append 'a' → helper(1, "23", "a")
  │         └─ temp = "def"
  │         ├─ i=0 → append 'd' → helper(2, "23", "ad")
  │         │         └─ ind==2 == length → push "ad" ✅
  │         ├─ i=1 → append 'e' → helper(2, "23", "ae")
  │         │         └─ ind==2 == length → push "ae" ✅
  │         └─ i=2 → append 'f' → helper(2, "23", "af")
  │                   └─ ind==2 == length → push "af" ✅
  │
  ├─ i=1 → append 'b' → helper(1, "23", "b")
  │         └─ temp = "def"
  │         ├─ i=0 → append 'd' → helper(2, "23", "bd") → push "bd" ✅
  │         ├─ i=1 → append 'e' → helper(2, "23", "be") → push "be" ✅
  │         └─ i=2 → append 'f' → helper(2, "23", "bf") → push "bf" ✅
  │
  └─ i=2 → append 'c' → helper(1, "23", "c")
            └─ temp = "def"
            ├─ i=0 → append 'd' → helper(2, "23", "cd") → push "cd" ✅
            ├─ i=1 → append 'e' → helper(2, "23", "ce") → push "ce" ✅
            └─ i=2 → append 'f' → helper(2, "23", "cf") → push "cf" ✅

Final ans = ["ad", "ae", "af", "bd", "be", "bf", "cd", "ce", "cf"]
```

---

**Complexity:**
- Time: $O(n \times 4^n)$ — in the worst case (digits like `7` or `9` with 4 letters), each digit branches into 4 calls. With `n` digits, we get up to $4^n$ leaf nodes, and each combination takes $O(n)$ to build.
- Space: $O(n)$ — recursion stack goes `n` levels deep (one per digit)

**Key Takeaway:**
- This is a classic **recursive backtracking** problem. The trick is to think of each digit as a level in the recursion tree. At each level, we try all possible letters for that digit and recurse deeper. The base case naturally collects all complete combinations at the leaves of the tree.
---

### 9. Subset Sums

**Problem:** Given an array `arr`, find the sum of all possible subsets and return them in sorted order.

**Example:**
```
Input:  arr = [2, 3, 1]
Output: [0, 1, 2, 3, 3, 4, 5, 6]

Explanation:
Subset []        → sum = 0
Subset [1]       → sum = 1
Subset [2]       → sum = 2
Subset [2,1]     → sum = 3
Subset [3]       → sum = 3
Subset [3,1]     → sum = 4
Subset [2,3]     → sum = 5
Subset [2,3,1]   → sum = 6
```

---

**Approach (Recursion — Take / Not Take):**

At every index, we face a binary choice:
- **Take** the current element → add it to the running sum and move to the next index
- **Not Take** the current element → keep the sum as-is and move to the next index

By exploring both choices at every index, we cover every possible subset. When we reach the end of the array (base case), the accumulated `sum` represents one complete subset sum — we store it.

**Steps:**
1. Start with `ind = 0` and `sum = 0`.
2. At each index, make two recursive calls — one adding `arr[ind]` to sum, one not adding.
3. When `ind == arr.size()`, push the current `sum` into `ans`.
4. After all calls return, sort `ans` and return it.

---

**Code:**
```cpp
void helper(int ind, int sum, vector<int> &arr, vector<int> &ans) {
    // Base case: processed all elements → store the accumulated sum
    if (ind == arr.size()) {
        ans.push_back(sum);
        return;
    }

    // Take: include arr[ind] in the current subset
    helper(ind + 1, sum + arr[ind], arr, ans);

    // Not Take: exclude arr[ind] from the current subset
    helper(ind + 1, sum, arr, ans);
}

vector<int> subsetSums(vector<int>& arr) {
    int sum = 0;
    vector<int> ans;
    helper(0, sum, arr, ans);
    sort(ans.begin(), ans.end());
    return ans;
}
```

---

**Understanding the Code — Key Points:**

| Part | What it does |
|------|-------------|
| `ind` | Tracks which element we're currently deciding to take or skip |
| `sum` | Running total of the current subset being built |
| `ind == arr.size()` | All elements decided → one complete subset sum is ready |
| `sum + arr[ind]` | Passes an updated sum to the "take" branch without modifying the original |
| `sum` (unchanged) | Passes the same sum to the "not take" branch |
| `sort(ans...)` | Final sort since subsets are explored in no particular order |

---

**Recursion Tree for `arr = [2, 3, 1]`:**

Each node shows `(ind, sum)`. Left branch = **Take**, Right branch = **Not Take**.

```
                              (0, sum=0)
                           /              \
               Take arr[0]=2            Not Take arr[0]=2
                   /                           \
           (1, sum=2)                       (1, sum=0)
           /        \                       /         \
    Take arr[1]=3  Not Take           Take arr[1]=3  Not Take
         /               \                /                \
  (2, sum=5)        (2, sum=2)      (2, sum=3)         (2, sum=0)
   /       \          /     \        /       \           /       \
Take      Skip     Take    Skip   Take      Skip      Take      Skip
arr[2]=1  arr[2]  arr[2]=1 arr[2] arr[2]=1  arr[2]  arr[2]=1   arr[2]
   |         |       |       |       |          |       |           |
(3,sum=6) (3,sum=5)(3,sum=3)(3,sum=2)(3,sum=4)(3,sum=3)(3,sum=1)(3,sum=0)
   ✅        ✅      ✅       ✅       ✅         ✅       ✅         ✅
push 6    push 5  push 3  push 2  push 4    push 3  push 1    push 0
```

**All values collected (unsorted):** `[6, 5, 3, 2, 4, 3, 1, 0]`  
**After sort:** `[0, 1, 2, 3, 3, 4, 5, 6]` ✅

---

**Dry Run for `arr = [2, 3, 1]`:**

```
helper(0, sum=0)
├── TAKE arr[0]=2 → helper(1, sum=2)
│   ├── TAKE arr[1]=3 → helper(2, sum=5)
│   │   ├── TAKE arr[2]=1 → helper(3, sum=6)
│   │   │   └── ind==3 → push 6 ✅
│   │   └── SKIP arr[2]   → helper(3, sum=5)
│   │       └── ind==3 → push 5 ✅
│   └── SKIP arr[1]   → helper(2, sum=2)
│       ├── TAKE arr[2]=1 → helper(3, sum=3)
│       │   └── ind==3 → push 3 ✅
│       └── SKIP arr[2]   → helper(3, sum=2)
│           └── ind==3 → push 2 ✅
│
└── SKIP arr[0]   → helper(1, sum=0)
    ├── TAKE arr[1]=3 → helper(2, sum=3)
    │   ├── TAKE arr[2]=1 → helper(3, sum=4)
    │   │   └── ind==3 → push 4 ✅
    │   └── SKIP arr[2]   → helper(3, sum=3)
    │       └── ind==3 → push 3 ✅
    └── SKIP arr[1]   → helper(2, sum=0)
        ├── TAKE arr[2]=1 → helper(3, sum=1)
        │   └── ind==3 → push 1 ✅
        └── SKIP arr[2]   → helper(3, sum=0)
            └── ind==3 → push 0 ✅

Collected: [6, 5, 3, 2, 4, 3, 1, 0]
Sorted:    [0, 1, 2, 3, 3, 4, 5, 6]
```

---

**Complexity:**
- Time: $O(2^n)$ — there are $2^n$ subsets for an array of size `n`, and we visit each exactly once. Sorting the result adds $O(2^n \log 2^n)$ which simplifies to $O(n \cdot 2^n)$.
- Space: $O(n)$ — the recursion stack goes at most `n` levels deep (one per element)

**Key Takeaway:**
- The **Take / Not Take** pattern is the fundamental building block of subset-based recursion. Every element gets two chances at each recursive call — be part of the subset or not. This cleanly generates all $2^n$ possible subsets without any overlap or missed case.
---

### 10. Rat in a Maze

**Problem:** Given an `n x n` binary maze where `1` means the cell is open and `0` means it is blocked, find all paths a rat can take from the **top-left corner `(0,0)`** to the **bottom-right corner `(n-1, n-1)`**. The rat can move in four directions: **Right (R), Left (L), Up (U), Down (D)**. Return all valid paths in lexicographic order.

**Example:**
```
Input:
maze = [[1, 0, 0, 0],
        [1, 1, 0, 1],
        [1, 1, 0, 0],
        [0, 1, 1, 1]]

Output: ["DDRDRR", "DRDDRR"]
```

---

**Approach (Recursion + Backtracking):**

At every cell, the rat tries all 4 directions. If a move is valid (in bounds, not blocked, not already visited), the rat steps into that cell and keeps exploring. If a path leads to a dead end, the rat **backtracks** — it unmarks the cell as visited and tries a different direction.

**Key ideas:**
- A `visited` matrix ensures the rat doesn't revisit a cell in the same path (avoids infinite loops).
- After returning from a recursive call, we **unmark** the cell (`visited[row][col] = 0`) so other paths can use it.
- The path string is built character by character as we move — no need to undo it since strings are passed by value.

**Steps:**
1. Start at `(0, 0)` with an empty path string.
2. At each cell, check all 4 directions in order: R → L → U → D.
3. For each direction, recurse into the neighboring cell with the direction character appended to path.
4. **Base cases:**
   - Out of bounds → return
   - Cell is `0` (blocked) or already visited → return
   - Reached `(n-1, n-1)` → push path to `ans` and return
5. Mark cell visited before recursing, unmark after (backtracking).

---

**Code:**
```cpp
void storePath(int row, int col, string path, vector<vector<int>> &maze,
               vector<vector<int>> &visited, vector<string> &ans, int n) {

    // Base case: out of bounds
    if (row < 0 || col < 0 || row >= n || col >= n) return;

    // Base case: cell is blocked or already visited in this path
    if (maze[row][col] == 0 || visited[row][col]) return;

    // Base case: reached destination → valid path found
    if (row == n - 1 && col == n - 1) {
        ans.push_back(path);
        return;
    }

    // Mark current cell as visited
    visited[row][col] = 1;

    storePath(row, col + 1, path + 'R', maze, visited, ans, n);  // Move Right
    storePath(row, col - 1, path + 'L', maze, visited, ans, n);  // Move Left
    storePath(row - 1, col, path + 'U', maze, visited, ans, n);  // Move Up
    storePath(row + 1, col, path + 'D', maze, visited, ans, n);  // Move Down

    // Unmark current cell (backtrack) so other paths can use it
    visited[row][col] = 0;
}

vector<string> ratInMaze(vector<vector<int>>& maze) {
    int n = maze.size();
    vector<vector<int>> visited(n, vector<int>(n, 0));
    vector<string> ans;
    string path = "";
    storePath(0, 0, path, maze, visited, ans, n);
    return ans;
}
```

---

**Understanding the Code — Key Points:**

| Part | What it does |
|------|-------------|
| `visited[row][col] = 1` | Marks the cell before diving deeper — prevents revisiting in same path |
| `visited[row][col] = 0` | **Backtracking step** — unmarks after returning so other paths can use this cell |
| `path + 'R'` | Passes a new string copy down — no need to undo since original `path` is unchanged |
| Order: R → L → U → D | This fixed order ensures results come out in lexicographic order |
| `maze[row][col] == 0` | Cell is a wall — dead end, don't proceed |
| `row == n-1 && col == n-1` | Destination reached — store the path |

---

**Maze Visualization for the Example:**

```
     Col: 0   1   2   3
Row 0: [  1   0   0   0  ]   ← Start at (0,0)
Row 1: [  1   1   0   1  ]
Row 2: [  1   1   0   0  ]
Row 3: [  0   1   1   1  ]   ← End at (3,3)

1 = open cell   0 = blocked cell
```

**Path 1: "DDRDRR"**
```
(0,0) →D (1,0) →D (2,0) →R (2,1) →D (3,1) →R (3,2) →R (3,3) ✅
```

**Path 2: "DRDDRR"**
```
(0,0) →D (1,0) →R (1,1) →D (2,1) →D (3,1) →R (3,2) →R (3,3) ✅
```

---

**Recursion Tree (simplified for key branches):**

Only open cells shown. Pruned branches are marked with ✗.

```
storePath(0,0, "")
│
├── R → (0,1) ✗  [maze=0, blocked]
├── L → (0,-1) ✗ [out of bounds]
├── U → (-1,0) ✗ [out of bounds]
└── D → (1,0, "D")
    │
    ├── R → (1,1, "DR")
    │   ├── R → (1,2) ✗ [maze=0]
    │   ├── L → (1,0) ✗ [visited]
    │   ├── U → (0,1) ✗ [maze=0]
    │   └── D → (2,1, "DRD")
    │       ├── R → (2,2) ✗ [maze=0]
    │       ├── L → (2,0, "DRDL") → dead end (all neighbors blocked/visited)
    │       ├── U → (1,1) ✗ [visited]
    │       └── D → (3,1, "DRDD")
    │           ├── R → (3,2, "DRDDR")
    │           │   ├── R → (3,3, "DRDDRR") ✅ push "DRDDRR"
    │           │   └── ... other directions pruned
    │           ├── L → (3,0) ✗ [maze=0]
    │           ├── U → (2,1) ✗ [visited]
    │           └── D → (4,1) ✗ [out of bounds]
    │
    ├── L → (1,-1) ✗ [out of bounds]
    ├── U → (0,0) ✗  [visited]
    └── D → (2,0, "DD")
        ├── R → (2,1, "DDR")
        │   ├── R → (2,2) ✗ [maze=0]
        │   ├── L → (2,0) ✗ [visited]
        │   ├── U → (1,1) ... → dead end
        │   └── D → (3,1, "DDRD")
        │       ├── R → (3,2, "DDRDR")
        │       │   ├── R → (3,3, "DDRDRR") ✅ push "DDRDRR"
        │       │   └── ... other directions pruned
        │       └── ...
        ├── L → (2,-1) ✗ [out of bounds]
        ├── U → (1,0) ✗  [visited]
        └── D → (3,0) ✗  [maze=0]
```

**Paths found in order of discovery:** `["DRDDRR", "DDRDRR"]`  
**After sort (lexicographic):** `["DDRDRR", "DRDDRR"]` ✅

---

**Dry Run (tracing the first successful path "DDRDRR"):**

```
storePath(0,0, "")
  visited[0][0] = 1
  → Try R: storePath(0,1,"R")   → maze[0][1]=0 ✗ return
  → Try L: storePath(0,-1,"L") → out of bounds ✗ return
  → Try U: storePath(-1,0,"U") → out of bounds ✗ return
  → Try D: storePath(1,0,"D")
      visited[1][0] = 1
      → Try R: storePath(1,1,"DR")
          visited[1][1] = 1
          → Try D: storePath(2,1,"DRD")
              visited[2][1] = 1
              → Try D: storePath(3,1,"DRDD")
                  visited[3][1] = 1
                  → Try R: storePath(3,2,"DRDDR")
                      visited[3][2] = 1
                      → Try R: storePath(3,3,"DRDDRR")
                          row==n-1 && col==n-1 → push "DRDDRR" ✅ return
                      visited[3][2] = 0  ← backtrack
                  visited[3][1] = 0  ← backtrack
              visited[2][1] = 0  ← backtrack
          visited[1][1] = 0  ← backtrack
      → Try D: storePath(2,0,"DD")
          visited[2][0] = 1
          → Try R: storePath(2,1,"DDR")
              visited[2][1] = 1
              → Try D: storePath(3,1,"DDRD")
                  visited[3][1] = 1
                  → Try R: storePath(3,2,"DDRDR")
                      visited[3][2] = 1
                      → Try R: storePath(3,3,"DDRDRR")
                          row==n-1 && col==n-1 → push "DDRDRR" ✅ return
                      visited[3][2] = 0  ← backtrack
                  visited[3][1] = 0  ← backtrack
              visited[2][1] = 0  ← backtrack
          visited[2][0] = 0  ← backtrack
      visited[1][0] = 0  ← backtrack
  visited[0][0] = 0  ← backtrack

Final ans (sorted) = ["DDRDRR", "DRDDRR"]
```

---

**Complexity:**
- Time: $O(4^{n^2})$ — at each of the $n^2$ cells, we can try up to 4 directions. In the worst case (fully open maze), this leads to $4^{n^2}$ recursive calls.
- Space: $O(n^2)$ — the `visited` matrix takes $O(n^2)$ space, and the recursion stack can go at most $n^2$ levels deep in the worst case.

**Key Takeaway:**
- Rat in a Maze is the classic example of **backtracking** — try a path, and if it doesn't work, undo your last step and try something else. The `visited` matrix is the heart of this: mark before you go in, unmark when you come out. This ensures every path is explored independently without interference.
---



### 11. Print All Subsequences with Sum = K

## Problem Statement

Given an array of integers `nums` and a target sum `k`, print **all subsequences** whose elements add up to exactly `k`.

**Example:**
```
Input:  nums = {1, 2, 1}, k = 2
Output:
1 1
2
```

---

## What is a Subsequence?

A subsequence is a subset of elements that **maintain their relative order** from the original array. Elements do not need to be contiguous.

For `{1, 2, 1}`:
- All subsequences: `{}`, `{1}`, `{2}`, `{1}`, `{1,2}`, `{1,1}`, `{2,1}`, `{1,2,1}`
- Subsequences with sum = 2: `{1,1}`, `{2}` ✅

---

## Approach — Recursion + Backtracking

### Core Idea

At **every index**, we make a binary choice:
1. **Take** the current element → subtract it from remaining sum `k`
2. **Don't take** the current element → move forward with same `k`

We explore all possible combinations via recursion and **backtrack** after each choice.

### Recursion Tree (for `{1, 2, 1}`, k = 2)

```
printSubsequence(k=2, ind=0, ans=[])
├── TAKE nums[0]=1 → printSubsequence(k=1, ind=1, ans=[1])
│   ├── TAKE nums[1]=2 → printSubsequence(k=-1, ind=2, ans=[1,2])
│   │   └── ❌ k < 0 → return
│   └── SKIP nums[1] → printSubsequence(k=1, ind=2, ans=[1])
│       ├── TAKE nums[2]=1 → printSubsequence(k=0, ind=3, ans=[1,1])
│       │   └── ✅ k==0 → print "1 1"
│       └── SKIP nums[2] → printSubsequence(k=1, ind=3, ans=[1])
│           └── ❌ ind==size → return
└── SKIP nums[0]=1 → printSubsequence(k=2, ind=1, ans=[])
    ├── TAKE nums[1]=2 → printSubsequence(k=0, ind=2, ans=[2])
    │   └── ✅ k==0 → print "2"
    └── SKIP nums[1] → printSubsequence(k=2, ind=2, ans=[])
        ├── TAKE nums[2]=1 → printSubsequence(k=1, ind=3, ans=[1])
        │   └── ❌ ind==size → return
        └── SKIP nums[2] → printSubsequence(k=2, ind=3, ans=[])
            └── ❌ ind==size → return
```

---

## Code

```cpp
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
    vector<int> nums = {1, 2, 1};
    int k = 2;

    vector<int> ans;

    printSubsequence(nums, k, 0, ans);

    return 0;
}
```

---

## Step-by-Step Explanation

| Step | Action | `ind` | `k` (remaining) | `ans` |
|------|--------|-------|-----------------|-------|
| 1 | Start | 0 | 2 | `[]` |
| 2 | Take 1 | 1 | 1 | `[1]` |
| 3 | Skip 2 | 2 | 1 | `[1]` |
| 4 | Take 1 | 3 | 0 | `[1,1]` |
| 5 | **k==0 → PRINT** | - | - | `1 1` |
| 6 | Backtrack to ind=1 | 1 | 2 | `[]` |
| 7 | Take 2 | 2 | 0 | `[2]` |
| 8 | **k==0 → PRINT** | - | - | `2` |

---

## Base Cases — Why They Matter

```cpp
if (k == 0)          // ✅ Found valid subsequence → print it
if (ind == nums.size() || k < 0)  // ❌ Exhausted array OR overshot sum → stop
```

| Condition | Meaning | Action |
|-----------|---------|--------|
| `k == 0` | Remaining sum hit zero | Print current `ans` |
| `ind == nums.size()` | Traversed entire array | Stop exploring |
| `k < 0` | Sum exceeded target | Prune this branch |

> ⚠️ The `k < 0` check **only works for non-negative arrays**. If the array has negatives, remove this check.

---

## Complexity Analysis

| | Value |
|--|--|
| **Time** | O(2ⁿ) — every element has 2 choices (take/skip) |
| **Space** | O(n) — recursion stack depth + `ans` vector |

---

## Key Concepts to Remember

```
✅ Take element  → push to ans, reduce k, move to ind+1
✅ Skip element  → keep ans same, keep k same, move to ind+1
✅ Backtrack     → pop_back() after the "take" recursive call
✅ Pruning       → k < 0 cuts unnecessary branches early
```

---

## Common Variations

| Variant | Change Needed |
|---------|--------------|
| **Count** subsequences with sum k | Return `int`, add `1` instead of printing |
| **Any one** subsequence with sum k | Return `bool`, stop after first found |
| **Array has negatives** | Remove `k < 0` base case |
| **With duplicates (unique subsets)** | Sort array + skip duplicate branches |

---

## Quick Revision Cheatsheet

```
Problem   : Print all subsequences with sum = k
Pattern   : Recursion + Backtracking (Pick/Not-Pick)
At each step:
  ├─ PICK   → ans.push_back(), recurse with k-nums[ind], ind+1
  └─ NO PICK → recurse with k, ind+1
  (after PICK branch) → ans.pop_back()  ← BACKTRACK

Base Cases:
  k == 0             → print ans ✅
  ind == n || k < 0  → return ❌

Time: O(2ⁿ)  |  Space: O(n)
```
---

### 12. Check If Any Subsequence with Sum = K Exists

## Problem Statement

Given an array of integers `arr` of size `n` and a target integer `k`, determine whether **any subsequence** of the array exists whose elements sum to exactly `k`. Return `true` if such a subsequence exists, otherwise return `false`.

**Example:**
```
Input:  arr = {1, 2, 3}, n = 3, k = 5
Output: true
Explanation: The subsequence {2, 3} has sum = 5 ✅

Input:  arr = {1, 2, 3}, n = 3, k = 7
Output: false
Explanation: No subsequence sums to 7 ❌
```

---

## What is a Subsequence?

A subsequence is a subset of elements that **maintain their relative order** from the original array. Elements do not need to be contiguous.

For `{1, 2, 3}`:
- All subsequences: `{}`, `{1}`, `{2}`, `{3}`, `{1,2}`, `{1,3}`, `{2,3}`, `{1,2,3}`
- Subsequences with sum = 5: `{2, 3}` ✅

---

## Approach — Recursion (Pick / Not-Pick)

### Core Idea

At **every index**, we make a binary choice:
1. **Take** the current element → add it to the running `sum`
2. **Don't take** the current element → keep `sum` unchanged

We recurse through all combinations and check if any of them hit exactly `k` by the time we've processed every element.

### Base Case

When `index == n` (we've gone past the last element), we check: is `sum == k`?
- **Yes** → a valid subsequence was found → return `true`
- **No**  → this path failed → return `false`

### Short-circuit Evaluation

Because we use `take || notTake`, as soon as one branch returns `true`, the other branch is **not evaluated** — giving us an early exit.

---

## Recursion Tree (for `arr = {1, 2, 3}`, k = 5)

```
checkIfExists(index=0, sum=0)
├── TAKE 1 → checkIfExists(index=1, sum=1)
│   ├── TAKE 2 → checkIfExists(index=2, sum=3)
│   │   ├── TAKE 3 → checkIfExists(index=3, sum=6)
│   │   │   └── sum(6) != k(5) → ❌ false
│   │   └── SKIP 3 → checkIfExists(index=3, sum=3)
│   │       └── sum(3) != k(5) → ❌ false
│   └── SKIP 2 → checkIfExists(index=2, sum=1)
│       ├── TAKE 3 → checkIfExists(index=3, sum=4)
│       │   └── sum(4) != k(5) → ❌ false
│       └── SKIP 3 → checkIfExists(index=3, sum=1)
│           └── sum(1) != k(5) → ❌ false
└── SKIP 1 → checkIfExists(index=1, sum=0)
    ├── TAKE 2 → checkIfExists(index=2, sum=2)
    │   ├── TAKE 3 → checkIfExists(index=3, sum=5)
    │   │   └── sum(5) == k(5) → ✅ true  ← propagates up immediately
    │   └── ...short-circuited
    └── ...short-circuited
```

---

## Code

```cpp
bool checkIfExists(int index, int n, vector<int>& arr, int k, int sum) {
    // Base case: processed all elements → did we hit the target?
    if (index == n) {
        return sum == k;
    }

    // Take the current element: add arr[index] to running sum
    bool take = checkIfExists(index + 1, n, arr, k, sum + arr[index]);

    // Don't take the current element: sum stays the same
    bool notTake = checkIfExists(index + 1, n, arr, k, sum);

    // Return true if either choice leads to a valid subsequence
    return take || notTake;
}

bool checkSubsequenceSum(int n, vector<int>& arr, int k) {
    int sum = 0;
    return checkIfExists(0, n, arr, k, sum);  // Start from index 0, sum = 0
}
```

---

## Step-by-Step Walkthrough

| Step | `index` | `sum` | Action | Result |
|------|---------|-------|--------|--------|
| 1 | 0 | 0 | Start | — |
| 2 | 1 | 0 | Skip `arr[0]=1` | — |
| 3 | 2 | 2 | Take `arr[1]=2` | — |
| 4 | 3 | 5 | Take `arr[2]=3` | — |
| 5 | 3 | 5 | `index==n`, `sum==k` | ✅ `true` |

---

## How It Differs from "Count" and "Print" Variants

| Problem Variant | Return Type | What Changes |
|----------------|-------------|--------------|
| **Check if exists** (this problem) | `bool` | Return `true` on first valid path found |
| **Count** subsequences with sum k | `int` | Return `1` instead of `true`, sum both branches |
| **Print all** subsequences with sum k | `void` | Maintain a current path vector, print when base case hits |

---

## Base Case — Why It Works

```cpp
if (index == n) {
    return sum == k;
}
```

We only check the sum **after** deciding on every element — this is cleaner and avoids early termination issues with negative numbers.

> ✅ **This approach works even if the array contains negative numbers**, because we don't prune early based on whether `sum > k`.

---

## Complexity Analysis

| | Value |
|--|--|
| **Time** | O(2ⁿ) — each element has 2 choices (take / skip) |
| **Space** | O(n) — maximum recursion stack depth |

> In practice, the `||` short-circuit means we often exit **much earlier** than the worst case once a valid subsequence is found.

---

## Quick Revision Cheatsheet

```
Problem   : Check if any subsequence sums to k
Pattern   : Recursion (Pick / Not-Pick)

At each index:
  ├─ TAKE   → recurse with sum + arr[index], index + 1
  └─ NO TAKE → recurse with sum, index + 1

Base Case:
  index == n → return (sum == k)

Short-circuit:
  return take || notTake   ← stops as soon as true is found

Time: O(2ⁿ)  |  Space: O(n)
```
---


### 13 Rotate Matrix 90° Clockwise


### **Problem Statement:**
Rotate an **N × N matrix** by **90° clockwise**.

&nbsp;

**Input**
```
1 2 3
4 5 6
7 8 9
```

**Output**
```
7 4 1
8 5 2
9 6 3
```

---

## **Approach 1 — Brute Force (Extra Matrix)**

&nbsp;

> 🔑 **Key Idea:** Create a new matrix and place each element at its rotated position using a formula.

&nbsp;

**Mapping Rule**
```
matrix[i][j]  →  result[j][n-1-i]
```

**Steps**
- Create a new matrix `result[n][n]`
- Traverse original matrix
- Place elements using mapping rule

&nbsp;

| Complexity | Value  |
|------------|--------|
| Time       | O(N²)  |
| Space      | O(N²)  |

&nbsp;

### **Brute Force Code (C++)**

```cpp
#include <iostream>
#include <vector>
using namespace std;

int main() {

    vector<vector<int>> matrix = {
        {1,2,3},
        {4,5,6},
        {7,8,9}
    };

    int n = matrix.size();
    vector<vector<int>> result(n, vector<int>(n));   // here the space complexity becomes n^2

    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++)
            result[j][n-1-i] = matrix[i][j];

    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++)
            cout << result[i][j] << " ";
        cout << endl;
    }
}
```

---

## **Formula Deep Dive — `result[j][n-1-i] = matrix[i][j]`**

&nbsp;

> 📌 This is the **core line** of the brute force approach. Understanding this is key.

&nbsp;

**What it means:**
- Take element from position `(i, j)` in original matrix
- Place it at position `(j, n-1-i)` in result matrix

```
Original Position  →  New Position
    (i , j)        →   (j , n-1-i)
```

&nbsp;

**Why `n-1-i`?**
- Matrix index starts from `0`, so last index = `n-1`
- When rotating clockwise → row becomes **reversed column**
- That reversal is captured by `n-1-i`

&nbsp;

### **How to Derive the Formula (Interview Trick)**

Track where elements go after rotation:

```
Original → Rotated
(0,0)    → (0,2)
(0,1)    → (1,2)
(0,2)    → (2,2)
(1,0)    → (0,1)
(2,0)    → (0,0)
```

**Pattern observed:**
```
new row = j
new col = n-1-i
```

> ✅ **Memory Trick:** Column becomes row. Row becomes reverse column.

---

## **Dry Run — Every Iteration (n=3)**

&nbsp;

> 🔍 Matrix used: `{{1,2,3},{4,5,6},{7,8,9}}`, n = 3

&nbsp;

| Iteration | i | j | Element | Formula Applied | New Position | Result Matrix State |
|-----------|---|---|---------|-----------------|--------------|---------------------|
| 1 | 0 | 0 | 1 | result[0][3-1-0] | result[0][2] = 1 | `_ _ 1 / _ _ _ / _ _ _` |
| 2 | 0 | 1 | 2 | result[1][3-1-0] | result[1][2] = 2 | `_ _ 1 / _ _ 2 / _ _ _` |
| 3 | 0 | 2 | 3 | result[2][3-1-0] | result[2][2] = 3 | `_ _ 1 / _ _ 2 / _ _ 3` |
| 4 | 1 | 0 | 4 | result[0][3-1-1] | result[0][1] = 4 | `_ 4 1 / _ _ 2 / _ _ 3` |
| 5 | 1 | 1 | 5 | result[1][3-1-1] | result[1][1] = 5 | `_ 4 1 / _ 5 2 / _ _ 3` |
| 6 | 1 | 2 | 6 | result[2][3-1-1] | result[2][1] = 6 | `_ 4 1 / _ 5 2 / _ 6 3` |
| 7 | 2 | 0 | 7 | result[0][3-1-2] | result[0][0] = 7 | `7 4 1 / _ 5 2 / _ 6 3` |
| 8 | 2 | 1 | 8 | result[1][3-1-2] | result[1][0] = 8 | `7 4 1 / 8 5 2 / _ 6 3` |
| 9 | 2 | 2 | 9 | result[2][3-1-2] | result[2][0] = 9 | `7 4 1 / 8 5 2 / 9 6 3` |

&nbsp;

**Final Rotated Matrix:**
```
7 4 1
8 5 2
9 6 3
```

---

## **Approach 2 — Optimal (In-place, O(1) Space)**

&nbsp;

> 🔑 **Key Idea:** No extra matrix needed. Do it in **2 simple steps**.

&nbsp;

**Step 1 — Transpose the matrix**
```
Swap matrix[i][j] ↔ matrix[j][i]

1 2 3         1 4 7
4 5 6   →     2 5 8
7 8 9         3 6 9
```

**Step 2 — Reverse each row**
```
1 4 7   →   7 4 1
2 5 8   →   8 5 2
3 6 9   →   9 6 3
```

&nbsp;

### **Optimal Code (C++)**

```cpp
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {

    vector<vector<int>> matrix = {
        {1,2,3},
        {4,5,6},
        {7,8,9}
    };

    int n = matrix.size();

    // Step 1: Transpose (Interchange)
    for(int i = 0; i < n; i++)
        for(int j = i+1; j < n; j++)
            swap(matrix[i][j], matrix[j][i]);

    // Step 2: Reverse each row
    for(int i = 0; i < n; i++)
        reverse(matrix[i].begin(), matrix[i].end());

    // Print
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++)
            cout << matrix[i][j] << " ";
        cout << endl;
    }
}
```

---

## **Complexity Comparison**

&nbsp;

| Approach    | Time  | Space |
|-------------|-------|-------|
| Brute Force | O(N²) | O(N²) |
| Optimal     | O(N²) | O(1)  |

---

## **All Rotation Types — Cheatsheet**

&nbsp;

| Rotation           | Formula / Steps                          |
|--------------------|------------------------------------------|
| 90° Clockwise      | `(i,j) → (j, n-1-i)` OR Transpose + Reverse rows |
| 90° Anti-clockwise | `(i,j) → (n-1-j, i)` OR Transpose + Reverse columns |
| 180°               | Reverse rows + Reverse columns           |

---

## **Quick Revision Cheatsheet**

```
Problem   : Rotate N×N matrix 90° clockwise

Brute Force:
  result[j][n-1-i] = matrix[i][j]
  Time: O(N²)  |  Space: O(N²)

Optimal (In-place):
  Step 1 → Transpose  (swap i,j with j,i)
  Step 2 → Reverse each row
  Time: O(N²)  |  Space: O(1)

Formula Memory Trick:
  column  →  becomes new row
  row     →  becomes reversed column
  (i, j)  →  (j, n-1-i)
```
---

### 14. Reverse a Linked List

**Problem:** Given the `head` of a singly linked list, reverse the list and return the new head.

**Example:**
```
Input:  1 → 2 → 3 → 4 → 5 → NULL
Output: 5 → 4 → 3 → 2 → 1 → NULL
```

---

## **Approach 1 — Iterative (O(1) Space)**

> 🔑 **Key Idea:** Use three pointers — `prev`, `curr`, and `temp` — to reverse each link one step at a time as you walk through the list.

**How it works:**
- `prev` starts as `NULL` (the new tail's next will be NULL).
- `curr` starts at `head` and moves forward each iteration.
- Before reversing a link, save `curr->next` in `temp` so we don't lose the rest of the list.
- Then point `curr->next` backwards to `prev`, advance `prev` to `curr`, and advance `curr` to `temp`.
- Once `curr` is NULL, `prev` is the new head.

**Step-by-step dry run:**
```
Initial:   prev=NULL   curr=1→2→3→NULL

Step 1:  temp=2,    1→NULL,  prev=1,  curr=2
Step 2:  temp=3,    2→1,     prev=2,  curr=3
Step 3:  temp=NULL, 3→2,     prev=3,  curr=NULL

Loop ends. Return prev = 3→2→1→NULL  ✅
```

**Code:**
```cpp
// Iterative approach: Time complexity=O(n), Space complexity=O(1)
ListNode* reverseList(ListNode* head) {
    ListNode *curr = head, *temp = curr, *prev = NULL;
    while (curr) {
        temp = curr->next;   // save next node
        curr->next = prev;   // reverse the link
        prev = curr;         // move prev forward
        curr = temp;         // move curr forward
    }
    return prev;             // prev is the new head
}
```

**Complexity:**
- Time: $O(n)$ — single pass through the list
- Space: $O(1)$ — only three pointers used

---

## **Approach 2 — Recursive (O(n) Space)**

> 🔑 **Key Idea:** Recursively reverse the tail of the list, then fix the link between the current node and its successor.

**How it works:**
1. Recurse all the way to the last node — that becomes `revHead` (the new head).
2. On the way back, for each node:
   - `head->next->next = head` makes the next node point back to the current node.
   - `head->next = NULL` removes the original forward link (to avoid a cycle).
3. Bubble `revHead` up unchanged until it's returned as the final result.

**Step-by-step dry run:**
```
List: 1 → 2 → 3 → NULL

recurse(1) calls recurse(2) calls recurse(3)
  → Base case: 3->next == NULL, return 3  (revHead = 3)

Back at node 2:
  2->next->next = 2   →   3→2
  2->next = NULL      →   2→NULL
  Return revHead = 3

Back at node 1:
  1->next->next = 1   →   2→1
  1->next = NULL      →   1→NULL
  Return revHead = 3

Final list: 3 → 2 → 1 → NULL  ✅
```

**Code:**
```cpp
// Recursive approach: Time complexity=O(n), Space complexity=O(n)
ListNode* reverseList(ListNode* head) {
    if (head == NULL || head->next == NULL) {
        return head;                           // base case: empty or single node
    }
    ListNode* revHead = reverseList(head->next);  // reverse the rest
    head->next->next = head;                   // make next node point back to current
    head->next = NULL;                         // remove original forward link
    return revHead;                            // new head bubbles up unchanged
}
```

**Complexity:**
- Time: $O(n)$ — visits every node once
- Space: $O(n)$ — recursion call stack grows to depth n

---

## **Comparison**

| Approach   | Time  | Space | Notes                                               |
|------------|-------|-------|-----------------------------------------------------|
| Iterative  | O(n)  | O(1)  | Preferred — no extra stack memory                   |
| Recursive  | O(n)  | O(n)  | Elegant but risks stack overflow on very long lists |

---

## **Quick Revision Cheatsheet**

```
Problem  : Reverse a singly linked list
Pattern  : Pointer manipulation

Iterative (3 pointers):
  prev=NULL, curr=head
  while curr:
    temp       = curr->next
    curr->next = prev
    prev       = curr
    curr       = temp
  return prev
  Time: O(n)  |  Space: O(1)  ← preferred

Recursive:
  base case: head==NULL || head->next==NULL → return head
  revHead          = reverse(head->next)
  head->next->next = head    ← reverse the link
  head->next       = NULL    ← cut old forward link
  return revHead
  Time: O(n)  |  Space: O(n)

```
---

### 15. Detect Cycle in a Linked List (Floyd's Algorithm)

**Problem:** Given the `head` of a linked list, return the **node where the cycle begins**. If there is no cycle, return `NULL`.

**Example:**
```
List:  1 → 2 → 3 → 4 → 5
                ↑           |
                └───────────┘
                  cycle start = node 3

Output: node with value 3
```

---

## **Algorithm — Floyd's Cycle Detection (Two-Pointer)**

This problem is solved in **two phases** using two pointers, `slow` and `fast`.

&nbsp;

### **Phase 1 — Detect if a cycle exists**

> 🔑 **Key Idea:** Move `slow` one step and `fast` two steps at a time. If they ever meet, a cycle exists.

- If `fast` reaches `NULL`, the list has no cycle → return `NULL`.
- If `slow == fast` at any point inside the loop, a cycle is confirmed → `break`.

**Why do they always meet inside the cycle?**
Once both pointers enter the cycle, `fast` gains one step on `slow` per iteration. The gap between them shrinks by 1 each time, so they are guaranteed to collide — never skip past each other — within at most `cycle_length` steps.

&nbsp;

### **Phase 2 — Find the cycle start node**

> 🔑 **Key Idea:** Reset `slow` to `head`. Move both pointers one step at a time. They will meet exactly at the cycle's entry node.

**Why does this work? (The Math)**

Let:
```
F = distance from head to cycle start
C = distance from cycle start to meeting point (inside cycle)
L = total cycle length
```

At the meeting point in Phase 1:
```
slow traveled : F + C
fast traveled : F + C + L  (fast did one extra full loop)

Since fast moves 2× as fast:
  2(F + C) = F + C + L
  F + C    = L
  F        = L - C
```

`L - C` is exactly the distance from the meeting point back to the cycle start.
So if `slow` restarts from `head` (distance `F` away from start) and `fast` continues from the meeting point (also `F` steps away from start going around the cycle), they meet at the **cycle entry node**.

---

## **Step-by-step Dry Run**

```
List:  1 → 2 → 3 → 4 → 5 → (back to 3)
idx:   0   1   2   3   4

F = 2 (head → node 3)
L = 3 (cycle: 3→4→5→3)
```

**Phase 1 — Detect:**
```
Start:  slow=1, fast=1

Step 1: slow=2, fast=3
Step 2: slow=3, fast=5
Step 3: slow=4, fast=4  ← MEET (C=2 steps from cycle start)
→ Cycle detected! Break.
```

**Phase 2 — Find entry:**
```
Reset slow=1 (head), fast stays at node 4

Step 1: slow=2, fast=5
Step 2: slow=3, fast=3  ← MEET

→ Return node 3 ✅  (the cycle start)
```

Verification: `F = 2`, `L - C = 3 - 2 = 1`... wait, let me re-check with actual steps — both pointers took 2 steps to meet at node 3. ✅

---

## **Code (with inline explanation):**

```cpp
ListNode* detectCycle(ListNode* head) {
    if (head == NULL) {
        return NULL;           // empty list — no cycle possible
    }

    ListNode *slow = head, *fast = head;

    // ── Phase 1: Detect if a cycle exists ──────────────────────────
    while (fast != NULL && fast->next != NULL) {
        slow = slow->next;         // slow moves 1 step
        fast = fast->next->next;   // fast moves 2 steps

        if (slow == fast) {        // pointers met → cycle confirmed
            break;                 // must break, or loop runs forever (TLE)
        }
    }

    // If fast hit the end, there is no cycle
    if (fast == NULL || fast->next == NULL) {
        return NULL;
    }

    // ── Phase 2: Find the cycle entry node ─────────────────────────
    slow = head;                   // reset slow to head
    while (slow != fast) {
        slow = slow->next;         // both move 1 step at a time
        fast = fast->next;
    }

    return slow;                   // meeting point = cycle start
}
```

> ⚠️ **Why the `break` is critical:**
> Without `break`, once `slow == fast` inside the cycle the loop condition `fast != NULL && fast->next != NULL` stays true forever, causing an infinite loop (TLE). Breaking out immediately is essential.

---

## **Complexity**

| Phase   | Time   | Space  |
|---------|--------|--------|
| Phase 1 | O(n)   | O(1)   |
| Phase 2 | O(n)   | O(1)   |
| **Total**  | **O(n)** | **O(1)** |

No extra data structures (like a HashSet) are needed — pure pointer math.

---

## **Quick Revision Cheatsheet**

```
Problem  : Detect cycle start in a linked list
Pattern  : Floyd's Cycle Detection (Tortoise & Hare)

Phase 1 — Detect cycle:
  slow = head, fast = head
  while fast && fast->next:
    slow = slow->next
    fast = fast->next->next
    if slow == fast → break   ← MUST break to avoid TLE

  if fast == NULL || fast->next == NULL → return NULL (no cycle)

Phase 2 — Find entry:
  slow = head               ← reset to head
  while slow != fast:
    slow = slow->next
    fast = fast->next       ← both move 1 step now
  return slow               ← cycle start node

The Math:
  F = head → cycle start
  At meeting point: F = L - C
  → Both pointers are equidistant from cycle start

Time: O(n)  |  Space: O(1)
```
---

### 16. Middle of a Linked List

**Problem:** Given the `head` of a singly linked list, return the **middle node**. If there are two middle nodes, return the **second** one.

**Example:**
```
Odd length:   1 → 2 → [3] → 4 → 5       Middle = node 3
Even length:  1 → 2 → 3 → [4] → 5 → 6   Middle = node 4  (second middle)
```

**Intuition:**
- `fast` moves twice as fast as `slow`.
- By the time `fast` reaches the end of the list, `slow` has covered exactly half the distance — landing it right at the middle.

**Why does `fast != NULL && fast->next != NULL` handle both odd and even lists?**
```
Odd  (n=5): fast exits when fast == NULL        → slow is at index 2  (node 3) ✅
Even (n=6): fast exits when fast->next == NULL  → slow is at index 3  (node 4) ✅
```

**Step-by-step dry run:**
```
Odd list:  1 → 2 → 3 → 4 → 5

Start: slow=1, fast=1
Step 1: slow=2, fast=3
Step 2: slow=3, fast=5
        fast->next == NULL → exit loop
Return slow = node 3  ✅

Even list:  1 → 2 → 3 → 4 → 5 → 6

Start: slow=1, fast=1
Step 1: slow=2, fast=3
Step 2: slow=3, fast=5
Step 3: slow=4, fast=NULL → exit loop
Return slow = node 4  ✅
```

**Code:**
```cpp
ListNode* middleNode(ListNode* head) {
    ListNode *slow = head, *fast = head;

    while (fast != NULL && fast->next != NULL) {
        slow = slow->next;         // slow moves 1 step
        fast = fast->next->next;   // fast moves 2 steps
    }

    return slow;   // slow is exactly at the middle
}
```

**Complexity:**
- Time: $O(n)$ — single pass
- Space: $O(1)$ — two pointers only

---

### 17. Detect if a Cycle Exists

**Problem:** Given the `head` of a linked list, return `true` if it contains a cycle, `false` otherwise.

> 📌 This is a simpler variant of Problem 15 — instead of *finding* the cycle start node, we just need to *confirm* whether a cycle exists at all.

**Intuition:**
- On a cycle-free list, `fast` eventually falls off the end (`NULL`) → no cycle.
- On a list with a cycle, `fast` loops around and laps `slow` — they are guaranteed to collide.

Think of it like two runners on a circular track: the faster one always catches the slower one.

**Step-by-step dry run:**
```
No cycle:  1 → 2 → 3 → NULL

Start: slow=1, fast=1
Step 1: slow=2, fast=3
Step 2: slow=3, fast=NULL → exit loop
→ return false  ✅

With cycle:  1 → 2 → 3 → 4 → (back to 2)

Start: slow=1, fast=1
Step 1: slow=2, fast=3
Step 2: slow=3, fast=2   (fast looped around)
Step 3: slow=4, fast=4   ← slow == fast!
→ return true  ✅
```

**Code:**
```cpp
bool hasCycle(ListNode* head) {
    if (head == NULL) {
        return false;              // empty list can't have a cycle
    }

    ListNode *slow = head, *fast = head;

    while (fast != NULL && fast->next != NULL) {
        slow = slow->next;         // slow moves 1 step
        fast = fast->next->next;   // fast moves 2 steps

        if (slow == fast) {        // pointers met → cycle confirmed
            return true;
        }
    }

    return false;                  // fast hit NULL → no cycle
}
```

**Complexity:**
- Time: $O(n)$
- Space: $O(1)$

---

## **The Two-Pointer Pattern — How Problems 16, 17 & 15 Connect**

All three problems share the exact same loop. The only difference is what we do with the result:

| Problem               | Loop | Extra logic              | Return                |
|-----------------------|:----:|--------------------------|-----------------------|
| 16. Middle of List    | ✅   | None — just let it run   | `slow` at loop exit   |
| 17. Has Cycle?        | ✅   | Check `slow==fast` inside | `true` / `false`     |
| 15. Find Cycle Start  | ✅   | Break + Phase 2 reset    | Cycle entry node      |

> ✅ **Master the two-pointer loop once — apply it to all three problems.**

---

## **Quick Revision Cheatsheet**

```
Pattern: slow moves 1 step, fast moves 2 steps
Loop guard: while (fast != NULL && fast->next != NULL)

──────────────────────────────────────────────────────────
16. MIDDLE NODE
  No extra logic — just run the loop to completion
  Return slow at exit
  Odd list  → fast == NULL        (slow = exact middle)
  Even list → fast->next == NULL  (slow = second middle)
  Time: O(n)  |  Space: O(1)

──────────────────────────────────────────────────────────
17. HAS CYCLE (boolean)
  Inside loop: if slow == fast → return true
  After loop:  return false
  Time: O(n)  |  Space: O(1)

──────────────────────────────────────────────────────────
15. FIND CYCLE START (see previous entry)
  Phase 1: same loop + break on slow == fast
  Phase 2: reset slow = head, walk both 1 step until they meet
  Return slow = cycle entry node
  Time: O(n)  |  Space: O(1)
```
---
### 18. Palindrome Linked List

**Problem:** Given the `head` of a singly linked list, return `true` if it is a palindrome, `false` otherwise.

**Example:**
```
Input:  1 → 2 → 2 → 1   →  true
Input:  1 → 2 → 3 → 2   →  false

Odd length:
Input:  1 → 2 → 3 → 2 → 1  →  true
```

**Approach:**
1. Use **slow & fast pointers** to find the middle of the list.
2. **Split** the list into two halves by cutting the link at the middle.
3. **Reverse** the second half.
4. **Compare** both halves node by node — if all values match, it's a palindrome.

**Why split and reverse?**
- We can't traverse a singly linked list backwards.
- Reversing the second half lets us compare it forward against the first half.

**Handling odd vs even lengths:**
```
Even (n=4):  1 → 2 | 2 → 1
  fast == NULL when loop ends → second half starts at slow

Odd (n=5):   1 → 2 → [3] → 2 → 1
  fast->next == NULL when loop ends → middle node is slow
  second half starts at slow->next (skip the middle node)
```

**Step-by-step dry run:**
```
List: 1 → 2 → 2 → 1

slow/fast start at node 1

Step 1: prev=1, slow=2, fast=3
Step 2: prev=2, slow=3, fast=NULL  → loop exits (fast==NULL, even list)

Split:  first = [1 → 2]    second = [2 → 1]
        prev->next = NULL cuts the link

Reverse second half:  [1 → 2]

Compare:
  revHead=1  first=1  ✅
  revHead=2  first=2  ✅
  revHead=NULL → loop ends

Return true ✅
```

**Code:**
```cpp
ListNode* reverseNode(ListNode* currHead) {
    ListNode *curr = currHead, *temp = currHead, *prev = NULL;
    while (curr) {
        temp = curr->next;   // save next node
        curr->next = prev;   // reverse the link
        prev = curr;         // advance prev
        curr = temp;         // advance curr
    }
    return prev;             // prev is the new head after full reversal
}

bool isPalindrome(ListNode* head) {
    // Edge case: 0 or 1 node is always a palindrome
    if (!head || !head->next) return true;

    ListNode *slow = head, *fast = head, *prev = NULL;

    // Step 1: Find the middle using slow & fast pointers
    while (fast != NULL && fast->next != NULL) {
        prev = slow;
        slow = slow->next;
        fast = fast->next->next;
    }

    ListNode *first = head, *second = NULL;

    // Step 2: Determine where the second half starts
    if (fast == NULL) {
        // Even length: slow is exactly the start of second half
        second = slow;
    } else {
        // Odd length: slow is the middle node, skip it
        second = slow->next;
    }

    // Step 3: Cut the list — first half ends here
    prev->next = NULL;

    // Step 4: Reverse the second half
    ListNode* revHead = reverseNode(second);

    // Step 5: Compare both halves
    while (revHead != NULL) {
        if (revHead->val != first->val) return false;
        revHead = revHead->next;
        first = first->next;
    }

    return true;
}
```

**Complexity:**
- Time: $O(n)$ — one pass to find middle + one pass to reverse + one pass to compare
- Space: $O(1)$ — only pointer variables, no extra data structures

**Key pointer roles:**
| Pointer | Role |
|---------|------|
| `slow` | Finds the middle (moves 1 step) |
| `fast` | Drives the loop (moves 2 steps) |
| `prev` | Tracks the node just before `slow` — used to cut the list |
| `first` | Walks the first half during comparison |
| `revHead` | Walks the reversed second half during comparison |

---

### 19. Rotate Linked List to the Right by K Places

**Problem:** Given the `head` of a linked list and an integer `k`, rotate the list to the right by `k` places.

**Example:**
```
Input:  1 → 2 → 3 → 4 → 5,  k = 2
Output: 4 → 5 → 1 → 2 → 3

Input:  1 → 2 → 3,  k = 4
Output: 3 → 1 → 2   (k % 3 = 1, same as rotating once)
```

**Intuition:**
Rotating right by `k` means the last `k` nodes move to the front.
Equivalently, the new head is the node at position `(length - k)` from the start (1-indexed).

**Key insight — reduce k:**
If `k >= length`, full rotations bring the list back to its original state. So `k = k % length` eliminates redundant rotations.

**Approach:**
1. Compute the length of the list.
2. Reduce `k` with `k = k % length`. If `k == 0`, return the list unchanged.
3. Convert to an equivalent **left rotation** count: `k = length - k`. Now walk `k` steps to find the new tail.
4. The node at step `k` is the **new tail**; its next is the **new head**.
5. Connect the old tail back to the old head to complete the rotation.

**Step-by-step dry run:**
```
List: 1 → 2 → 3 → 4 → 5,  k = 2
length = 5
k = 2 % 5 = 2
k = 5 - 2 = 3   (walk 3 steps to find new tail)

Walk 3 steps:
  prev=NULL, temp=1
  Step 1: prev=1, temp=2
  Step 2: prev=2, temp=3
  Step 3: prev=3, temp=4

New tail = node 3  →  prev->next = NULL  →  list is cut: [1→2→3]  [4→5]
New head = node 4  (ans = temp)

Walk to end of second part: temp=4 → temp=5 → temp->next==NULL
Connect: 5->next = 1 (old head)

Result: 4 → 5 → 1 → 2 → 3  ✅
```

**Code:**
```cpp
int lengthOfLL(ListNode* curr) {
    int count = 0;
    while (curr) {
        count++;
        curr = curr->next;
    }
    return count;
}

ListNode* rotateRight(ListNode* head, int k) {
    // Edge case: empty list or single node — nothing to rotate
    if (!head || !head->next) return head;

    int length = lengthOfLL(head);

    // Reduce k: full rotations cancel out
    k = k % length;
    if (k == 0) return head;   // already in original order

    // Convert right rotation to equivalent left rotation steps
    k = length - k;

    // Walk k steps to find the new tail
    ListNode *prev = NULL, *temp = head;
    while (k--) {
        prev = temp;
        temp = temp->next;
    }

    // Cut the list: prev is new tail, temp is new head
    prev->next = NULL;
    ListNode* ans = temp;

    // Walk to the end of the rotated segment
    while (temp->next != NULL) {
        temp = temp->next;
    }

    // Connect old tail to old head — completes the rotation
    temp->next = head;

    return ans;
}
```

**Complexity:**
- Time: $O(n)$ — one pass for length + one pass to find split point + one pass to find old tail
- Space: $O(1)$ — only pointer variables

**Key pointer roles:**
| Pointer | Role |
|---------|------|
| `temp` | Walks the list; becomes new head after the cut |
| `prev` | Trails one step behind `temp`; becomes new tail after the cut |
| `ans` | Saves the new head (`temp` at split point) to return |

**Edge cases handled:**
```
k = 0 or k = multiple of length  →  return head unchanged (no-op rotation)
Single node list                  →  return head unchanged
```

---

### 20. Add Two Numbers

**Problem:** You are given two non-empty linked lists representing two non-negative integers. The digits are stored in **reverse order**, and each node contains a single digit. Add the two numbers and return the sum as a linked list (also in reverse order).

**Example:**
```
Input:  l1 = 2 → 4 → 3   (represents 342)
        l2 = 5 → 6 → 4   (represents 465)
Output: 7 → 0 → 8         (represents 807)

Input:  l1 = 9 → 9 → 9 → 9 → 9 → 9 → 9
        l2 = 9 → 9 → 9 → 9
Output: 8 → 9 → 9 → 9 → 0 → 0 → 0 → 1
```

**Approach:**
1. Handle edge cases: if either list is empty, return the other.
2. Create a **dummy head node** to simplify result list construction.
3. Walk both lists simultaneously, summing digits and carrying over:
   - `sum = carry + (l1->val if l1 exists) + (l2->val if l2 exists)`
   - New digit = `sum % 10`, new carry = `sum / 10`
4. Append each computed digit as a new node.
5. Continue until **both lists are exhausted AND carry is 0**.
6. Return `dummyNode->next` (the actual head of the result).

**Why a dummy node?**
- It eliminates the special case of initializing the head of the result list — we always append to `dummyNode->next` and return that.

**Step-by-step dry run:**
```
l1: 2 → 4 → 3   l2: 5 → 6 → 4   carry = 0

Step 1: sum = 0 + 2 + 5 = 7   → digit=7, carry=0   result: 7
Step 2: sum = 0 + 4 + 6 = 10  → digit=0, carry=1   result: 7 → 0
Step 3: sum = 1 + 3 + 4 = 8   → digit=8, carry=0   result: 7 → 0 → 8
Both lists exhausted, carry=0 → done

Output: 7 → 0 → 8  ✅  (represents 807 = 342 + 465)
```

**Code:**
```cpp
ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
    if (!l1) return l2;
    if (!l2) return l1;

    ListNode* dummyNode = new ListNode(0);
    ListNode* temp = dummyNode;
    int carry = 0;

    while (l1 || l2 || carry) {
        int sum = carry;

        if (l1) {
            sum += l1->val;
            l1 = l1->next;
        }
        if (l2) {
            sum += l2->val;
            l2 = l2->next;
        }

        carry = sum / 10;
        sum %= 10;

        ListNode* newNode = new ListNode(sum);
        temp->next = newNode;
        temp = newNode;
    }

    return dummyNode->next;
}
```

**Complexity:**
- Time: $O(\max(m, n))$ — traverse both lists once, where m and n are their lengths
- Space: $O(\max(m, n))$ — result list has at most $\max(m, n) + 1$ nodes (due to a possible final carry)

**Key roles:**
| Variable | Role |
|----------|------|
| `dummyNode` | Anchor for the result list; avoids special-casing the head |
| `temp` | Tail pointer — always points to the last node appended |
| `carry` | Holds the overflow digit (0 or 1) from the previous addition |
| `sum` | Accumulates digit sum including carry, then splits into digit + new carry |

**Edge cases handled:**
```
One list shorter than the other  →  missing digits treated as 0
Final carry remaining             →  loop condition (|| carry) appends an extra node
Either list is NULL               →  early return of the other list
```

---

### 21. Reverse Linked List in Groups of Size K

**Problem:** Given a linked list, reverse the nodes of the list k at a time and return the modified list. If the number of nodes is not a multiple of k, the remaining nodes should stay as they are.

**Approach:**
1. First check if we have at least k nodes remaining - if not, return head unchanged.
2. Reverse the first k nodes using standard linked list reversal.
3. Recursively call the function for the remaining list.
4. Connect the reversed first k nodes with the result from the recursive call.
5. Return the new head (which is the kth node from the original list).

**Code:**
```cpp
ListNode* reverseKGroup(ListNode* head, int k) {
    ListNode *curr = head;
    for(int i = 0; i < k; i++){
        if(!curr){
            return head;
        }
        curr = curr->next;
    }
    curr = head;
    ListNode *temp = NULL, *prev = NULL;
    for(int i = 0; i < k; i++){
        temp = curr->next;
        curr->next = prev;
        prev = curr;
        curr = temp;
    }
    head->next = reverseKGroup(curr, k);
    return prev;
}
```
**Complexity:**
- Time: $O(n)$ where n is the number of nodes
- Space: $O(n/k)$ due to recursion stack

---

### 22. Delete a Node in a Linked List (Without Head Reference)

**Problem:** Given only a pointer to the node to be deleted (not the head of the list), delete that node. The node to delete is guaranteed not to be the last node.

**Example:**
```
Input:  1 → 2 → 3 → 4 → 5,  del_node points to node(3)
Output: 1 → 2 → 4 → 5
```

**Intuition:**
Since we don't have access to the previous node (no head pointer), we can't do a traditional deletion. Instead, we **copy data forward** — shift each node's value one step back — then delete the last node.

**Approach:**
1. Walk forward from `del_node`, copying the next node's data into the current node.
2. Keep tracking `prev` (the node just before the current position).
3. Once we reach the last node, set `prev->next = NULL` and delete the last node.

**Step-by-step dry run:**
```
List: 1 → 2 → 3 → 4 → 5,  del_node = node(3)

Iteration 1: node(3).data = node(4).data → list: 1 → 2 → 4 → 4 → 5,  prev=node(3), del_node=node(4)
Iteration 2: node(4).data = node(5).data → list: 1 → 2 → 4 → 5 → 5,  prev=node(4), del_node=node(5)
node(5)->next == NULL → exit loop

prev->next = NULL  →  list: 1 → 2 → 4 → 5
delete node(5)  ✅
```

**Code:**
```cpp
void deleteNode(Node* del_node) {
    Node *prev = NULL;
    while (del_node->next != NULL) {
        prev = del_node;
        del_node->data = del_node->next->data;
        del_node = del_node->next;
    }
    prev->next = NULL;
    delete(del_node);
}
```

**Complexity:**
- Time: $O(n)$ — walks from the target node to the end of the list
- Space: $O(1)$ — only pointer variables

**Key pointer roles:**
| Pointer | Role |
|---------|------|
| `del_node` | Walks forward; carries the data-copy operation |
| `prev` | Trails one step behind; used to cut the last node off the list |

**Edge cases:**
```
del_node is the second-to-last node  →  one iteration, then prev->next = NULL, last node deleted
del_node is guaranteed non-last      →  prev will always be set before the delete
```

---
### 23. N-Queens

**Problem:** Place `n` queens on an `n × n` chessboard such that no two queens attack each other (no two queens share the same row, column, or diagonal). Return all distinct solutions.

**Example:**
```
Input: n = 4
Output:
[".Q..",    ["..Q.",
 "...Q",     "Q...",
 "Q...",     "...Q",
 "..Q."]     ".Q.."]
```

**Approach (Backtracking):**
1. Place queens **row by row** — since only one queen can exist per row, we try each column in the current row.
2. Before placing, check if the position is **safe** using `isSafePlace()`.
3. If safe, place the queen (`'Q'`) and recurse to the next row.
4. After returning, **backtrack** by removing the queen (`'.'`) to explore other options.
5. **Base case:** when `row == n`, all queens are placed — add the board to the result.

**Safety Check (`isSafePlace`):**
Only need to check **upward directions** since we fill row by row (no queen below yet):
- **Vertical (↑):** scan the same column in all rows above
- **Left upper diagonal (↖):** scan diagonally up-left
- **Right upper diagonal (↗):** scan diagonally up-right

**Step-by-step dry run (n = 4):**
```
Row 0: Try col 0 → safe → place Q
  Row 1: Try col 0 → blocked (same col) | col 1 → blocked (diagonal) | col 2 → safe → place Q
    Row 2: All columns blocked → backtrack
  Row 1: Try col 3 → safe → place Q
    Row 2: Try col 1 → safe → place Q
      Row 3: Try col 2 → blocked | col 3 → blocked | col 0 → blocked | col ... → all blocked → backtrack
    Row 2: Backtrack
  Row 1: Backtrack
Row 0: Try col 1 → safe → place Q
  ... (finds first valid solution)
```

**Code:**
```cpp
bool isSafePlace(int row, int col, vector<string>& board) {
    int i, j, n = board.size();

    // Check vertical (same column, rows above)
    for (i = row - 1; i >= 0; i--) {
        if (board[i][col] == 'Q') {
            return false;
        }
    }

    // Check left upper diagonal (↖)
    for (i = row - 1, j = col - 1; i >= 0 && j >= 0; i--, j--) {
        if (board[i][j] == 'Q') {
            return false;
        }
    }

    // Check right upper diagonal (↗)
    for (i = row - 1, j = col + 1; i >= 0 && j < n; i--, j++) {
        if (board[i][j] == 'Q') {
            return false;
        }
    }
    return true;
}

void placeNQueens(int row, int n, vector<vector<string>>& ans, vector<string>& board) {
    // Base case: all rows filled → valid solution found
    if (row == n) {
        ans.push_back(board);
        return;
    }

    for (int j = 0; j < n; j++) {
        if (isSafePlace(row, j, board)) {
            board[row][j] = 'Q';           // Place queen
            placeNQueens(row + 1, n, ans, board);  // Recurse
            board[row][j] = '.';           // Backtrack
        }
    }
}

vector<vector<string>> solveNQueens(int n) {
    vector<vector<string>> ans;
    vector<string> board(n, string(n, '.'));   // n×n board, all dots
    placeNQueens(0, n, ans, board);
    return ans;
}
```

**Complexity:**
- Time: $O(n!)$ — at most $n$ choices in row 0, $n-1$ in row 1, and so on
- Space: $O(n^2)$ — board storage + $O(n)$ recursion stack depth

**Key roles:**
| Component | Role |
|-----------|------|
| `isSafePlace` | Validates a cell by checking column and both diagonals upward |
| `placeNQueens` | Backtracking engine — places, recurses, and undoes |
| `board[row][j] = '.'` | The backtrack step — restores board state after exploring a branch |

**Why only check upward?**
We process rows top-to-bottom, so all queens placed so far are in rows **above** the current row. Rows below are still empty — no need to check them.

**Edge cases:**
```
n = 1  →  single cell, one solution: ["Q"]
n = 2  →  no valid placement exists, returns []
n = 3  →  no valid placement exists, returns []
```

---
### 24. Permutations

**Problem:** Given an array `nums` of distinct integers, return all possible permutations in any order.

**Example:**
```
Input:  nums = [1, 2, 3]
Output: [[1,2,3], [1,3,2], [2,1,3], [2,3,1], [3,1,2], [3,2,1]]
```

**Approach (Backtracking with Swapping):**
1. Fix elements one position at a time using an `index` pointer.
2. For each position `index`, swap it with every element at position `i` (where `i >= index`) — effectively choosing which element goes at `index`.
3. Recurse on `index + 1` to fix the next position.
4. **Backtrack** by swapping back, restoring the array to its original order before trying the next choice.
5. **Base case:** when `index == nums.size()`, all positions are fixed — record the current permutation.

**Key Insight:**
The swap selects which element occupies position `index`. After the recursive call, undoing the swap ensures we explore all other possible selections for that position cleanly.

**Step-by-step dry run (`[1, 2, 3]`):**
```
index=0: swap(0,0)→[1,2,3] → index=1: swap(1,1)→[1,2,3] → index=2: swap(2,2)→[1,2,3] → ✅ record [1,2,3]
                                                             backtrack swap(2,2)→[1,2,3]
                              swap(1,2)→[1,3,2] → index=2: swap(2,2)→[1,3,2] → ✅ record [1,3,2]
                                                             backtrack swap(2,2)→[1,3,2]
                              backtrack swap(1,2)→[1,2,3]
         backtrack swap(0,0)→[1,2,3]

index=0: swap(0,1)→[2,1,3] → index=1: swap(1,1)→[2,1,3] → ✅ record [2,1,3]
                              swap(1,2)→[2,3,1] → ✅ record [2,3,1]
                              backtrack → [2,1,3]
         backtrack swap(0,1)→[1,2,3]

index=0: swap(0,2)→[3,2,1] → index=1: swap(1,1)→[3,2,1] → ✅ record [3,2,1]
                              swap(1,2)→[3,1,2] → ✅ record [3,1,2]
                              backtrack → [3,2,1]
         backtrack swap(0,2)→[1,2,3]
```

**Code:**
```cpp
void permutations(int index, vector<int>& nums, vector<vector<int>>& ans) {
    // Base case: all positions fixed → record this permutation
    if (index == nums.size()) {
        ans.push_back(nums);
        return;
    }

    // Try placing each remaining element at position 'index'
    for (int i = index; i < nums.size(); i++) {
        swap(nums[index], nums[i]);          // Choose: put nums[i] at position index
        permutations(index + 1, nums, ans);  // Recurse: fix the next position
        swap(nums[index], nums[i]);          // Backtrack: undo swap, restore array
    }
}

vector<vector<int>> permute(vector<int>& nums) {
    vector<vector<int>> ans;
    permutations(0, nums, ans);
    return ans;
}
```

**Complexity:**
- Time: $O(n \times n!)$ — there are $n!$ permutations, each taking $O(n)$ to copy into the result
- Space: $O(n)$ — recursion stack depth (in-place swapping, no extra array needed)

**Key roles:**
| Component | Role |
|-----------|------|
| `index` | The position currently being filled; elements to its left are already fixed |
| `swap(nums[index], nums[i])` | Selects which element occupies position `index` |
| Second `swap(nums[index], nums[i])` | Backtrack — restores the array for the next iteration |
| Base case `index == nums.size()` | All positions filled; snapshot the current arrangement |

**Why start the loop at `i = index` (not 0)?**
Elements before `index` are already placed in earlier recursive calls. Starting at `index` ensures we only consider elements that haven't been fixed yet.

**Edge cases:**
```
nums = []   →  one empty permutation: [[]]
nums = [1]  →  one permutation: [[1]]
```

---
### 25. Find the Duplicate Number

**Problem:** Given an array `nums` of `n + 1` integers where each integer is in the range `[1, n]`, find the one repeated number. You must solve it without modifying the array and using only O(1) extra space.

**Example:**
```
Input:  nums = [1, 3, 4, 2, 2]
Output: 2

Input:  nums = [3, 1, 3, 4, 2]
Output: 3
```

**Approach (Floyd's Tortoise and Hare — Cycle Detection):**

The key insight is to treat the array as a **linked list** where index `i` points to `nums[i]`. Since a duplicate exists, two indices point to the same value, forming a cycle.

**Phase 1 — Detect the cycle:**
1. Start both `slow` and `fast` at `nums[0]`.
2. Move `slow` one step: `slow = nums[slow]`
3. Move `fast` two steps: `fast = nums[nums[fast]]`
4. Repeat until `slow == fast` — they meet inside the cycle.

**Phase 2 — Find the cycle entrance (= duplicate):**
1. Reset `slow` to `nums[0]`, keep `fast` where it is.
2. Move both one step at a time.
3. Where they meet is the duplicate number.

**Step-by-step dry run (`[1, 3, 4, 2, 2]`):**
```
Array as implicit linked list:
  index: 0 → 1 → 3 → 4 → 2 → 2 (cycle back to index 2)

Phase 1 (detect cycle):
  Start: slow=nums[0]=1, fast=nums[0]=1
  Step 1: slow=nums[1]=3, fast=nums[nums[1]]=nums[3]=2
  Step 2: slow=nums[3]=2, fast=nums[nums[2]]=nums[4]=2
  slow == fast == 2  ✅ cycle detected

Phase 2 (find entrance):
  Reset slow=nums[0]=1, fast stays at 2
  Step 1: slow=nums[1]=3, fast=nums[2]=4
  Step 2: slow=nums[3]=2, fast=nums[4]=2
  slow == fast == 2  ✅ duplicate found → return 2
```

**Code:**
```cpp
int findDuplicate(vector<int>& nums) {
    int slow = nums[0], fast = nums[0];
    // Floyd's Tortoise and Hare (Cycle Detection) algorithm
    // loop detection
    do {
        slow = nums[slow];
        fast = nums[nums[fast]];
    } while (slow != fast);
    slow = nums[0];
    // finding the duplicate number
    while (slow != fast) {
        slow = nums[slow];
        fast = nums[fast];
    }
    return slow;
}
```

**Complexity:**
- Time: $O(n)$
- Space: $O(1)$

**Key roles:**
| Pointer | Phase 1 Role | Phase 2 Role |
|---------|-------------|-------------|
| `slow` | Moves 1 step at a time | Reset to start; moves 1 step |
| `fast` | Moves 2 steps at a time | Stays in cycle; moves 1 step |

**Why does Phase 2 find the duplicate?**
A standard result from Floyd's algorithm: after Phase 1, the distance from the start of the list to the cycle entrance equals the distance from the meeting point to the cycle entrance (travelling forward). So both pointers, moving at speed 1, converge at the entrance — which is the duplicate index.

**Edge cases:**
```
All duplicates at start of cycle  →  algorithm still converges correctly
Duplicate appears more than twice →  still one cycle entrance, same answer
```

---

### 26. Majority Element

**Problem:** Given an array `nums` of size `n`, return the element that appears **more than ⌊n/2⌋ times**. You may assume the majority element always exists.

**Example:**
```
Input:  nums = [3, 2, 3]
Output: 3

Input:  nums = [2, 2, 1, 1, 1, 2, 2]
Output: 2
```

**Approach (Boyer-Moore Voting Algorithm):**

The key insight: if we cancel out every occurrence of the majority element with a different element, the majority element still survives because it appears more than all others combined.

1. Maintain a `candidate` and a `count`.
2. When `count` drops to 0, pick the current element as the new `candidate`.
3. If the current element matches `candidate`, increment `count`; otherwise decrement it.
4. The surviving `candidate` at the end is the majority element.

**Step-by-step dry run (`[2, 2, 1, 1, 1, 2, 2]`):**
```
num=2: count=0 → candidate=2, count becomes 1
num=2: matches candidate → count = 2
num=1: no match         → count = 1
num=1: no match         → count = 0
num=1: count=0 → candidate=1, count becomes 1
num=2: no match         → count = 0
num=2: count=0 → candidate=2, count becomes 1

Result: candidate = 2  ✅
```

**Code:**
```cpp
int findMajorityElement(vector<int>& nums) {
    int count = 0, candidate = 0;
    for (int num : nums) {
        // Boyer-Moore Voting Algorithm
        if (count == 0) {
            candidate = num;
        }
        count += (num == candidate) ? 1 : -1;
    }
    return candidate;
}
```

**Complexity:**
- Time: $O(n)$
- Space: $O(1)$

**Key roles:**
| Variable | Role |
|----------|------|
| `candidate` | The current "surviving" element being tracked |
| `count` | Net votes for the candidate; drops to 0 when cancelled out |

**Why does this work?**
The majority element appears more than `n/2` times, so even after pairing every one of its occurrences against a different element, it still has leftover votes. No other element can accumulate enough to outlast it.

**Edge cases:**
```
nums = [1]          →  single element, returned immediately
All same elements   →  count only ever increments, candidate never changes
```

---
### 27. Merge Sorted Arrays

**Problem:** Given two sorted arrays `nums1` and `nums2` of sizes `m` and `n`, merge `nums2` into `nums1` in-place so that `nums1` becomes fully sorted. `nums1` has enough extra space at the end to hold `nums2`'s elements.

**Example:**
```
Input:  nums1 = [1, 2, 3, 0, 0, 0], m = 3
        nums2 = [2, 5, 6],           n = 3
Output: nums1 = [1, 2, 2, 3, 5, 6]

Input:  nums1 = [1], m = 1
        nums2 = [],  n = 0
Output: nums1 = [1]
```

**Approach (Three-Pointer — Fill from the Back):**

The key insight: merging from the **front** would overwrite elements in `nums1` we still need. Instead, fill from the **back** — the largest merged element always goes into the last available slot, which is already empty (or used space we've already processed).

1. Set `i = m-1` (last valid element in `nums1`), `j = n-1` (last element in `nums2`), `k = m+n-1` (last slot in `nums1`).
2. Compare `nums1[i]` and `nums2[j]`; place the larger one at `nums1[k]` and move the corresponding pointer left.
3. Decrement `k` each time.
4. If `nums2` still has remaining elements after the main loop, copy them into the front of `nums1` — `nums1`'s leftover elements are already in place.

**Step-by-step dry run:**
```
nums1 = [1, 2, 3, _, _, _]   nums2 = [2, 5, 6]
         i=2              k=5          j=2

Step 1: nums1[2]=3 < nums2[2]=6  →  nums1[5]=6,  j=1, k=4
        [1, 2, 3, _, _, 6]

Step 2: nums1[2]=3 < nums2[1]=5  →  nums1[4]=5,  j=0, k=3
        [1, 2, 3, _, 5, 6]

Step 3: nums1[2]=3 >= nums2[0]=2  →  nums1[3]=3, i=1, k=2
        [1, 2, 3, 3, 5, 6]

Step 4: nums1[1]=2 >= nums2[0]=2  →  nums1[2]=2, i=0, k=1
        [1, 2, 2, 3, 5, 6]

Step 5: nums1[0]=1 < nums2[0]=2 ... wait, j=0 and num2[0]=2
        nums1[1]=2 was already placed; i=0, j=0 still
        nums1[0]=1 < nums2[0]=2  → nums1[1]=2... 

Clean trace:
i=2,j=2,k=5: 3 vs 6  → place 6  → [1,2,3,_,_,6],  j=1,k=4
i=2,j=1,k=4: 3 vs 5  → place 5  → [1,2,3,_,5,6],  j=0,k=3
i=2,j=0,k=3: 3 vs 2  → place 3  → [1,2,3,3,5,6],  i=1,k=2
i=1,j=0,k=2: 2 vs 2  → place 2  → [1,2,2,3,5,6],  i=0,k=1
i=0,j=-1: j loop ends (nums2 exhausted)
nums1[0]=1 already in correct position ✅

Result: [1, 2, 2, 3, 5, 6]
```

**Code:**
```cpp
void mergeSortedArrays(vector<int>& nums1, vector<int>& nums2, int m, int n) {
    int i = m - 1, j = n - 1, k = m + n - 1;
    while (i >= 0 && j >= 0) {
        if (nums1[i] >= nums2[j]) {
            nums1[k] = nums1[i];
            i--;
            k--;
        } else {
            nums1[k] = nums2[j];
            j--;
            k--;
        }
    }
    // Copy any remaining elements from nums2
    while (j >= 0) {
        nums1[k] = nums2[j];
        j--;
        k--;
    }
}
```

**Complexity:**
- Time: $O(m + n)$ — each element is visited exactly once
- Space: $O(1)$ — merging is done in-place within `nums1`

**Key roles:**
| Pointer | Role |
|---------|------|
| `i` | Scans `nums1`'s valid elements from right to left |
| `j` | Scans `nums2` from right to left |
| `k` | Write position in `nums1`; always moves left after each placement |

**Why fill from the back?**
Filling from the front would overwrite elements in `nums1` before we've compared them. Starting at the back guarantees every write goes into a slot that's either empty padding or already been placed — no data is ever lost.

**Why only handle leftover `nums2` elements?**
If `j < 0`, all of `nums2` has been placed. Any remaining `nums1` elements (`i >= 0`) are already sitting in their correct positions at the front of `nums1` — no extra work needed.

**Edge cases:**
```
nums2 is empty (n=0)    →  nothing to do, nums1 unchanged
nums1 is empty (m=0)    →  second while loop copies all of nums2
All nums2 > all nums1   →  nums2 fills the back; second while never runs
All nums2 < all nums1   →  second while copies remaining nums2 to front
```

---
## 28. Search a 2D Matrix

> **Algorithm:** Binary Search on rows + Binary Search inside that row
> **Time Complexity:** O(log M + log N)  where M = rows, N = columns
> **Space Complexity:** O(1)
 
---
 
## The Problem
 
Given a **row-wise sorted** 2D matrix (each row sorted independently), find if a `target` value exists.
 
```
Input matrix (3 x 4):
      col0  col1  col2  col3
row0 [  1    3    5    7  ]
row1 [ 10   11   16   20  ]
row2 [ 23   30   34   60  ]
 
target = 3
Output: true
```
 
---
 
##  Intuition: How the Algorithm Works
 
```
TWO-PHASE BINARY SEARCH
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
 
PHASE 1 — searchMatrix()
Binary search across ROWS to find which row could hold the target.
 
For each mid row, check:
  mat[mid][0] <= target <= mat[mid][n-1]
               |
    YES → target could be in this row → go to Phase 2
    NO  →
         target > mat[mid][n-1]  → go DOWN (startRow = mid+1)
         target < mat[mid][0]    → go UP   (endRow   = mid-1)
 
PHASE 2 — SearchInRow()
Standard binary search INSIDE the identified row.
 
  target == mat[row][mid]  → FOUND   → return true
  target >  mat[row][mid]  → go right (start = mid+1)
  target <  mat[row][mid]  → go left  (end   = mid-1)
 
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
```
 
---
 
## Code:
 
```cpp
class Solution {
public:
 
    // Binary search inside a specific row
    bool SearchInRow(vector<vector<int>> &mat, int target, int row)
    {
        int n = mat[0].size();       // number of columns
 
        int start = 0, end = n - 1;
 
        while (start <= end)
        {
            int mid = start + (end - start) / 2;  // safe mid — avoids overflow
 
            // target found
            if (target == mat[row][mid])
            {
                return true;
            }
            // move right
            else if (target > mat[row][mid])
            {
                start = mid + 1;
            }
            // move left
            else
            {
                end = mid - 1;
            }
        }
 
        // target not found in this row
        return false;
    }
 
 
    // Main function: binary search on rows first
    bool searchMatrix(vector<vector<int>> &mat, int target)
    {
        int n        = mat[0].size();        // number of columns
        int startRow = 0;
        int endRow   = mat.size() - 1;      // number of rows - 1
 
        while (startRow <= endRow)
        {
            int mid = startRow + (endRow - startRow) / 2;
 
            // Check if target lies within this row's range
            if (target >= mat[mid][0] && target <= mat[mid][n - 1])
            {
                // apply binary search inside this row
                return SearchInRow(mat, target, mid);
            }
            // target is in a lower row (larger values)
            else if (target > mat[mid][n - 1])
            {
                startRow = mid + 1;
            }
            // target is in an upper row (smaller values)
            else
            {
                endRow = mid - 1;
            }
        }
 
        // target not found in any row
        return false;
    }
};
``` 
---

### Full Dry Run
 
### Input
 
```
mat = [
  [ 1,  3,  5,  7],    <- row 0
  [10, 11, 16, 20],    <- row 1
  [23, 30, 34, 60]     <- row 2
]
target = 3
```
 
---
 
### Matrix at start (all rows in play)
 
```
      c0    c1    c2    c3
r0  [  1  ][ 3  ][ 5  ][ 7  ]
r1  [ 10  ][11  ][16  ][20  ]
r2  [ 23  ][30  ][34  ][60  ]
```
 
---
 
### PHASE 1 — searchMatrix() — finding the right row
 
**Initial variables:**
```
n        = mat[0].size() = 4
startRow = 0
endRow   = mat.size() - 1 = 2
```
 
---
 
#### searchMatrix — Iteration 1
 
```
startRow = 0,   endRow = 2
while (0 <= 2) -> TRUE  -> enter loop
 
mid = 0 + (2 - 0) / 2  =  1
  -> examining ROW 1: [ 10  11  16  20 ]
     mat[1][0]  = 10   (first element)
     mat[1][3]  = 20   (last  element)
 
if (target >= mat[1][0] && target <= mat[1][3])
   3 >= 10  ->  FALSE  <- short-circuit, AND stops here
 
else if (target > mat[1][n-1])
   3 > 20  ->  FALSE
 
else   <- this branch executes
   endRow = mid - 1 = 1 - 1 = 0
 
After iteration 1:
  startRow = 0,   endRow = 0
 
Matrix state — rows 1 and 2 eliminated:
      c0    c1    c2    c3
r0  [  1  ][ 3  ][ 5  ][ 7  ]   <- only row remaining
r1  [ 10  ][11  ][16  ][20  ]   X eliminated
r2  [ 23  ][30  ][34  ][60  ]   X eliminated
```
 
---
 
#### searchMatrix — Iteration 2
 
```
startRow = 0,   endRow = 0
while (0 <= 0) -> TRUE  -> enter loop
 
mid = 0 + (0 - 0) / 2  =  0
  -> examining ROW 0: [  1   3   5   7 ]
     mat[0][0]  = 1    (first element)
     mat[0][3]  = 7    (last  element)
 
if (target >= mat[0][0] && target <= mat[0][3])
   3 >= 1  ->  TRUE
   3 <= 7  ->  TRUE
   Overall -> TRUE  (both conditions pass)
 
-> Call SearchInRow(mat, target=3, row=0)
```
 
---
 
### PHASE 2 — SearchInRow() — binary search inside row 0
 
**Row 0:** `[ 1   3   5   7 ]`
 
**Initial variables:**
```
n     = 4
start = 0
end   = n - 1 = 3
```
 
```
      c0    c1    c2    c3
r0  [  1  ][ 3  ][ 5  ][ 7  ]
      ^s                 ^e
```
 
---
 
#### SearchInRow — Iteration 1
 
```
start = 0,   end = 3
while (0 <= 3) -> TRUE  -> enter loop
 
mid = 0 + (3 - 0) / 2  =  1
  -> mat[0][1] = 3
 
if (target == mat[row][mid])
   3 == 3  ->  TRUE!
 
-> return true   <- FOUND!
 
      c0    c1    c2    c3
r0  [  1  ][ 3* ][ 5  ][ 7  ]
             ^^^
          mid=1  FOUND HERE at [row=0][col=1]
```
 
---
 
### Why only 3 steps?
 
```
Brute force approach:
  Scan every cell -> up to 3 x 4 = 12 comparisons
 
This algorithm:
  Phase 1: 2 comparisons to find the row
  Phase 2: 1 comparison to find the element
  Total  : 3 comparisons only!
 
That is O(log 3 + log 4) = approximately 3 steps
 
Scaling comparison:
  1000 x 1000 matrix -> brute force : 1,000,000 steps
                     -> this method : log(1000) + log(1000) = ~20 steps
```
 
---
 
## Call Stack Trace
 
```
searchMatrix(mat, target=3)
    |
    | Iter 1: mid=1, row1=[10..20], 3 < 10 -> endRow = 0
    | Iter 2: mid=0, row0=[1..7],   3 in range -> call SearchInRow
    |
    +-- SearchInRow(mat, target=3, row=0)
            |
            | Iter 1: mid=1, mat[0][1]=3, 3==3 -> return true
            |
            +-- return true
    |
    +-- return true  (searchMatrix returns this value up)
 
Output: true
```
 
---
 
## Complexity Analysis
 
```
Function          Operation                       Complexity
──────────────────────────────────────────────────────────────
searchMatrix()    Binary search over M rows       O(log M)
SearchInRow()     Binary search over N columns    O(log N)
──────────────────────────────────────────────────────────────
TOTAL                                             O(log M + log N)
Space                                             O(1)  <- no extra memory
```
 
---
 
## Key Lines to Remember
 
```cpp
// KEY LINE 1 — safe mid (avoids integer overflow for large values)
int mid = start + (end - start) / 2;
// NOT: (start + end) / 2  <- can overflow
 
// KEY LINE 2 — row range check (both conditions must pass)
if (target >= mat[mid][0] && target <= mat[mid][n - 1])
 
// KEY LINE 3 — go down (target is larger than this entire row)
startRow = mid + 1;
 
// KEY LINE 4 — go up (target is smaller than this entire row)
endRow = mid - 1;
 
// KEY LINE 5 — declare n in BOTH functions
int n = mat[0].size();  // needed in searchMatrix AND SearchInRow
```
 
---

# 29. Remove Nth Node From End of Linked List

> **Algorithm:** Two-pass approach — calculate length, then delete target node
> **Time Complexity:** O(L) where L = length of linked list
> **Space Complexity:** O(1) — only constant extra space used

---

## The Problem

Given the head of a linked list, remove the **Nth node from the end** and return the updated head.

```
Input:   1 -> 2 -> 3 -> 4 -> 5 -> NULL     N = 2
                              ^
                         2nd from end

Output:  1 -> 2 -> 3 -> 5 -> NULL
```

---

### Intuition

```
The key formula:

  position from END   = N
  position from START = length - N + 1   <- this is "target"

Example: list of length 5,  N = 2
  target = 5 - 2 + 1 = 4
  So we need to delete node at position 4 (1-indexed from start)

  pos:  1    2    3    4    5
        1 -> 2 -> 3 -> 4 -> 5 -> NULL
                        ^
                   delete this (4th from start = 2nd from end)

To delete node at position 4:
  - Move curr to position 3  (one before target)
  - curr->next = curr->next->next  (skip over node 4)
  - delete the skipped node
```

---


### Code:

```cpp
Node* removeNthFromEnd(Node* head, int N) {

    // STEP 1: calculate length of linked list
    int length = 0;
    Node* curr = head;

    while (curr != nullptr) {
        length++;
        curr = curr->next;
    }

    // STEP 2: find position from the START (1-indexed)
    int target = length - N + 1;

    // STEP 3: special case — if head itself needs to be removed
    if (target == 1) {
        Node* newHead = head->next;
        delete head;
        return newHead;
    }

    // STEP 4: move to node just BEFORE the target
    curr = head;
    for (int i = 1; i < target - 1; i++) {
        curr = curr->next;
    }

    // STEP 5: unlink and delete the target node
    Node* nodeToDelete = curr->next;
    curr->next = curr->next->next;
    delete nodeToDelete;

    return head;
}
```

---

## Dry Run

### Input

```
head = [1, 2, 3, 4, 5]     N = 2
```

### Linked list at start

```
[1] -> [2] -> [3] -> [4] -> [5] -> NULL
 ^
head
```

---

### STEP 1 — Calculate Length

**Initial state:** `length = 0`, `curr = head (node 1)`

---

#### Length loop — Iteration 1

```
curr = [1]   (not nullptr)
  -> length++   ->   length = 1
  -> curr = curr->next = [2]

State: length=1,  curr->[2]
```

#### Length loop — Iteration 2

```
curr = [2]   (not nullptr)
  -> length++   ->   length = 2
  -> curr = curr->next = [3]

State: length=2,  curr->[3]
```

#### Length loop — Iteration 3

```
curr = [3]   (not nullptr)
  -> length++   ->   length = 3
  -> curr = curr->next = [4]

State: length=3,  curr->[4]
```

#### Length loop — Iteration 4

```
curr = [4]   (not nullptr)
  -> length++   ->   length = 4
  -> curr = curr->next = [5]

State: length=4,  curr->[5]
```

#### Length loop — Iteration 5

```
curr = [5]   (not nullptr)
  -> length++   ->   length = 5
  -> curr = curr->next = nullptr

State: length=5,  curr->nullptr
```

#### Length loop — Check condition

```
curr = nullptr   -> while condition FALSE -> exit loop

Final: length = 5
```

---

### STEP 2 — Calculate Target Position

```
target = length - N + 1
       = 5      - 2 + 1
       = 4

So we must delete node at position 4 from the start.

Verify:
  pos:  1    2    3    4    5
        1 -> 2 -> 3 -> 4 -> 5 -> NULL
                        ^
                  position 4 from start
                  = position 2 from end  <- matches N=2  CORRECT
```

---

### STEP 3 — Head Check

```
Is target == 1?
   4 == 1  -> FALSE

Head does NOT need to be removed. Continue normally.
```

---

### STEP 4 — Move to Node Before Target

**Goal:** reach position `target - 1 = 4 - 1 = 3`
**Loop:** `for (int i = 1; i < target - 1; i++)` = `for (i = 1; i < 3; i++)`

**Initial state:** `curr = head = node[1]`  (curr is at position 1)

```
[1] -> [2] -> [3] -> [4] -> [5] -> NULL
 ^
curr (position 1)
```

#### for loop — i = 1   (condition: 1 < 3  -> TRUE)

```
curr = curr->next = [2]   -> curr moves to position 2
i++  -> i = 2

[1] -> [2] -> [3] -> [4] -> [5] -> NULL
        ^
       curr (position 2)
```

#### for loop — i = 2   (condition: 2 < 3  -> TRUE)

```
curr = curr->next = [3]   -> curr moves to position 3
i++  -> i = 3

[1] -> [2] -> [3] -> [4] -> [5] -> NULL
               ^
              curr (position 3)
```

#### for loop — i = 3   (condition: 3 < 3  -> FALSE -> exit loop)

```
curr is now at position 3  <- one node BEFORE target (position 4)
```

---

### STEP 5 — Delete the Target Node

**curr is at node[3]. Target is curr->next = node[4].**

```
Before deletion:
[1] -> [2] -> [3] -> [4] -> [5] -> NULL
               ^      ^
              curr   nodeToDelete

Step 5a: nodeToDelete = curr->next = node[4]
Step 5b: curr->next   = curr->next->next = node[5]
Step 5c: delete nodeToDelete  (free node[4] from memory)

After deletion:
[1] -> [2] -> [3] -> [5] -> NULL
               ^      ^
              curr   curr->next (now points to node[5])
```

**Pointer change in detail:**

```
BEFORE:
  node[3]->next  =  node[4]
  node[4]->next  =  node[5]

AFTER:
  node[3]->next  =  node[5]   <- skip over node[4]
  node[4] deleted from memory
```

---

### STEP 6 — Return Head

```
return head   (head still points to node[1], unchanged)

Final list:
[1] -> [2] -> [3] -> [5] -> NULL
```

---

## Special Case — When N = Length (Remove Head)

```
Input: [1, 2, 3, 4, 5],  N = 5

target = 5 - 5 + 1 = 1

if (target == 1) <- TRUE
  newHead = head->next = node[2]
  delete head          (free node[1])
  return newHead       (return node[2])

Output: [2, 3, 4, 5]
```

---

## Special Case — When N = 1 (Remove Tail)

```
Input: [1, 2, 3, 4, 5],  N = 1

target = 5 - 1 + 1 = 5

for loop: move curr to position 4 (node[4])
  curr->next = curr->next->next = nullptr
  delete node[5]

Output: [1, 2, 3, 4]
```

---

## Special Case — Single Node List

```
Input: [7],  N = 1

length = 1
target = 1 - 1 + 1 = 1

if (target == 1) <- TRUE
  newHead = head->next = nullptr
  delete head
  return nullptr

Output: [] (empty list)
```

---

## Complexity Analysis

```
STEP 1 — Length calculation loop
  Visits every node once  ->  O(L)

STEP 2 — Compute target
  Single arithmetic operation  ->  O(1)

STEP 3 — Head check
  Single comparison  ->  O(1)

STEP 4 — Move to target-1 position
  At most L-1 steps  ->  O(L)

STEP 5 — Delete node
  Pointer reassignment  ->  O(1)

Total Time : O(L) + O(L) = O(L)
Total Space: O(1)  — only curr, length, target, nodeToDelete used
```

---

## Formula to Remember

```
  +-----------------------------------------------+
  |                                               |
  |   target (from start) = length - N + 1       |
  |                                               |
  |   N = 1  ->  target = length   (last node)   |
  |   N = L  ->  target = 1        (head node)   |
  |                                               |
  +-----------------------------------------------+

  To delete node at position P:
    - Move curr to position P-1
    - curr->next = curr->next->next
    - delete old curr->next
```

---

## Why `i < target - 1` in the for loop?

```
for (int i = 1; i < target - 1; i++)

curr starts at position 1.
We want curr to stop at position (target - 1).
Number of steps needed = (target - 1) - 1 = target - 2

When i starts at 1 and increments until i < (target-1):
  i goes: 1, 2, 3, ..., target-2   <- that is (target-2) iterations
  curr advances (target-2) times
  curr ends at position 1 + (target-2) = target - 1  CORRECT

Example: target = 4
  i goes: 1, 2   (stops when i reaches 3, since 3 < 3 is false)
  curr moves 2 times: pos 1 -> pos 2 -> pos 3 = position 3 = target-1  CORRECT
```

---

---

# 30. Count Inversions in an Array

**Problem:** Given an array of integers, count the number of inversions. An inversion is a pair `(i, j)` such that `i < j` but `arr[i] > arr[j]` — i.e., a larger element appears before a smaller one.

**Example:**
```
Input:  arr = [2, 4, 1, 3, 5]
Output: 3

Explanation:
  Inversion pairs: (2,1), (4,1), (4,3)
  Indices:         (0,2), (1,2), (1,3)
```

**Approach (Merge Sort):**

The brute force approach checks every pair — O(n²). Instead, we piggyback on Merge Sort to count inversions in O(n log n).

**Key Insight:** During the merge step, when we pick an element from the **right** subarray over an element from the **left** subarray, every remaining element in the left subarray forms an inversion with it. Since both halves are sorted, all `mid - left + 1` remaining elements on the left are greater than the current right element.

**Step-by-step:**
1. Recursively split the array into two halves.
2. Count inversions in the left half.
3. Count inversions in the right half.
4. Merge the two sorted halves and count **cross inversions** (right element picked before left elements).
5. Return the total count.

**Visual walkthrough:**
```
arr = [2, 4, 1, 3, 5]

Split:   [2, 4, 1]         [3, 5]
Split:   [2, 4] [1]        [3] [5]
Split:   [2] [4]

Merge [2][4]  → sorted: [2, 4],  inversions: 0
Merge [2,4][1]:
  left=2, right=1  → pick 1, count += (mid - left + 1) = 2  (both 2 and 4 > 1)
  pick 2, pick 4
  sorted: [1, 2, 4],  inversions: 2

Merge [3][5]  → sorted: [3, 5],  inversions: 0

Merge [1,2,4][3,5]:
  1<3 → pick 1
  2<3 → pick 2
  4>3 → pick 3, count += (mid - left + 1) = 1  (only 4 remains on left)
  pick 4, pick 5
  sorted: [1, 2, 3, 4, 5],  inversions: 1

Total = 0 + 2 + 0 + 1 = 3  ✓
```

**Why `count += mid - left + 1`?**
```
left subarray (sorted):  [... arr[left], arr[left+1], ..., arr[mid]]
                                  ^  all of these > arr[right]
right element picked:    arr[right]

Since the left half is sorted, if arr[left] > arr[right],
then arr[left+1], arr[left+2], ..., arr[mid] are ALL > arr[right].
That's (mid - left + 1) inversions in one shot.
```

**Code:**
```cpp
int merge(vector<int> &arr, int low, int high, int mid) {
    int left = low, right = mid + 1, count = 0;
    vector<int> temp;

    while (left <= mid && right <= high) {
        if (arr[left] <= arr[right]) {
            temp.push_back(arr[left]);
            left++;
        } else {
            // arr[right] < arr[left], and since left half is sorted,
            // all elements from left..mid are > arr[right]
            count += mid - left + 1;
            temp.push_back(arr[right]);
            right++;
        }
    }

    while (left <= mid) {
        temp.push_back(arr[left]);
        left++;
    }

    while (right <= high) {
        temp.push_back(arr[right]);
        right++;
    }

    // Copy sorted temp back to original array
    for (int i = low; i <= high; i++) {
        arr[i] = temp[i - low];
    }
    return count;
}

int countInversion(vector<int> &arr, int low, int high) {
    if (low >= high) return 0;   // base case: single element

    int count = 0, mid = low + (high - low) / 2;
    count += countInversion(arr, low, mid);       // left half
    count += countInversion(arr, mid + 1, high);  // right half
    count += merge(arr, low, high, mid);           // cross inversions
    return count;
}

int inversionCount(vector<int> &arr) {
    return countInversion(arr, 0, arr.size() - 1);
}
```

**Complexity:**
- Time: $O(n \log n)$ — same recurrence as Merge Sort: $T(n) = 2T(n/2) + O(n)$
- Space: $O(n)$ — temporary array used during the merge step

**Comparison with Brute Force:**
| Approach | Time | Space |
|---|---|---|
| Brute Force (nested loops) | $O(n^2)$ | $O(1)$ |
| Merge Sort | $O(n \log n)$ | $O(n)$ |

**Key Takeaway:** Whenever you need to count pairs across two sorted halves, Merge Sort gives you the count for free during the merge step — without any extra comparisons.

---
# 31. Merge Two Sorted Linked Lists

**Problem:** Given the heads of two sorted linked lists, merge them into one sorted linked list and return its head.

**Example:**
```
Input:  list1 = [1, 2, 4],  list2 = [1, 3, 4]
Output: [1, 1, 2, 3, 4, 4]
```

**Approach:**
1. Use a **dummy head node** to avoid edge-case handling for the result list's head.
2. Maintain a `tail` pointer that always points to the last node of the merged list.
3. Compare the front nodes of both lists — attach the smaller one to `tail` and advance that list's pointer.
4. Once either list is exhausted, attach the remaining nodes of the other list directly (they're already sorted).
5. Return `dummyNode->next` as the merged list head.

**Why a dummy node?** It eliminates the need to special-case the very first node — `tail` always has somewhere to attach.

**Visual Walkthrough:**
```
list1: [1] -> [2] -> [4]
list2: [1] -> [3] -> [4]

dummy -> ?
tail = dummy

Step 1: 1 == 1, pick list1's 1  →  dummy -> [1],  list1 = [2]->[4]
Step 2: 2 > 1,  pick list2's 1  →  ... -> [1],    list2 = [3]->[4]
Step 3: 2 < 3,  pick list1's 2  →  ... -> [2],    list1 = [4]
Step 4: 4 > 3,  pick list2's 3  →  ... -> [3],    list2 = [4]
Step 5: 4 == 4, pick list1's 4  →  ... -> [4],    list1 = NULL
Step 6: list1 exhausted → attach remaining list2:  ... -> [4]

Result: [1] -> [1] -> [2] -> [3] -> [4] -> [4]
```

**Code:**
```cpp
ListNode* mergeTwoLists(ListNode* list1, ListNode* list2) {
    if(!list1) return list2;
    if(!list2) return list1;   
    ListNode* dummyNode = new ListNode(-1);
    ListNode* tail = dummyNode;
    while(list1 && list2){
        if(list1->val < list2->val){
            tail->next = list1;
            list1 = list1->next;
        } else {
            tail->next = list2;
            list2 = list2->next;
        }
        tail = tail->next;
    }
    if(list1){
        tail->next = list1;
    } else {
        tail->next = list2;
    }
    return dummyNode->next;
}
```

**Complexity:**
- Time: $O(m + n)$ — each node is visited exactly once
- Space: $O(1)$ — only the dummy node is allocated; no extra list is created

---

### 32. Intersection of Two Linked Lists

**Problem:** Given the heads of two singly linked lists, return the node at which the two lists intersect. If the two lists have no intersection, return `NULL`.

**Example:**
```
listA:       [4] -> [1] \
                         [8] -> [4] -> [5] -> NULL
listB: [5] -> [6] -> [1] /

Output: node with value 8
```

**Approach (Length Difference):**
1. Compute the length of both lists.
2. Identify the longer list. Advance its pointer by `|lenA - lenB|` steps so both pointers are equidistant from the end.
3. Walk both pointers forward together — the first node where they're equal (same address, not just same value) is the intersection.
4. If they both reach `NULL` without meeting, there's no intersection.

**Why this works:** If an intersection exists, both lists share a common suffix. By aligning their starts relative to the tail, both pointers reach the intersection node at the same step.

**Visual Walkthrough:**
```
listA (len=5): [4] -> [1] -> [8] -> [4] -> [5]
listB (len=6): [5] -> [6] -> [1] -> [8] -> [4] -> [5]
                                     ^--- intersection

diff = 6 - 5 = 1
Advance tempA (longer) by 1:  tempA = listB's [6] node? 

Wait — tempA is assigned to the LONGER list:
  lenB(6) > lenA(5)  →  tempA = headB,  tempB = headA
  diff = 1  →  advance tempA by 1

tempA: [6] -> [1] -> [8] -> [4] -> [5]
tempB: [4] -> [1] -> [8] -> [4] -> [5]
              ^--- now equidistant from tail (4 steps each)

Walk together:
  [6] vs [4]  → not equal, advance
  [1] vs [1]  → not equal (different nodes!), advance
  [8] vs [8]  → SAME NODE (address match)  →  return this node ✓
```

**Code:**
```cpp
int lengthofLL(ListNode *head){
    int count = 0;
    while(head){
        head = head->next;
        count++;
    }
    return count;
}

ListNode* getIntersection(ListNode* headA, ListNode* headB) {
    if(!headA || !headB) return NULL;
    int lenA = lengthofLL(headA);
    int lenB = lengthofLL(headB);
    ListNode *tempA = NULL, *tempB = NULL;
    if(lenA > lenB){
        tempA = headA;
        tempB = headB;
    } else {
        tempA = headB;
        tempB = headA;
    }
    int diff = abs(lenA - lenB);
    while(diff--){
        tempA = tempA->next;
    }
    while(tempA && tempB){
        if(tempA == tempB){
            return tempA;
        }
        tempA = tempA->next;
        tempB = tempB->next;
    }
    return NULL;
}
```

**Complexity:**
- Time: $O(m + n)$ — two length passes + one alignment pass, all linear
- Space: $O(1)$ — only pointer variables used

**Alternative — Two Pointer trick (no length needed):**
> Switch each pointer to the other list's head once it hits `NULL`. Both pointers then travel `m + n` total steps and meet at the intersection (or both reach `NULL` if no intersection exists). Same time complexity, slightly simpler code.

---
# 33. Power Function (x, n) — Fast Exponentiation (Binary Exponentiation)

> **Algorithm:** Divide and Conquer — halve the exponent at every step
> **Time Complexity:** O(log n) — exponent halves each recursive call
> **Space Complexity:** O(log n) — recursion call stack depth

---

## The Problem

Compute `x` raised to the power `n` (i.e., `x^n`) efficiently.

```
Naive approach:  multiply x by itself n times  ->  O(n)
This approach:   halve n at every step          ->  O(log n)

Example: x=2.0, n=10
  Naive: 2*2*2*2*2*2*2*2*2*2  ->  10 multiplications
  Fast:  2^10 -> 2^5 -> 2^2 -> 2^1 -> 2^0  ->  4 multiplications only
```

---

## The Code

```cpp
double myPow(double x, long long n) {

    // handle negative exponent
    // x^(-n) = (1/x)^n
    if (n < 0) {
        x = 1.0 / x;
        n = -n;
    }

    return helper(x, n);
}

double helper(double num, long long n) {

    // base case: anything^0 = 1
    if (n == 0) {
        return 1;
    }

    // recursive call with HALF the exponent
    double half = helper(num, n / 2);

    // even exponent: num^n = (num^(n/2))^2
    if (n % 2 == 0) {
        return half * half;
    }
    // odd exponent: num^n = (num^(n/2))^2 * num
    else {
        return half * half * num;
    }
}
```

---

## Core Insight — Why Halving Works

```
EVEN exponent:
  num^n  =  num^(n/2)  *  num^(n/2)
  2^10   =  2^5  *  2^5
  just compute 2^5 ONCE, square the result

ODD exponent:
  num^n  =  num^(n/2)  *  num^(n/2)  *  num
  2^11   =  2^5  *  2^5  *  2
  (integer division: 11/2 = 5, remainder 1)

NEGATIVE exponent:
  x^(-n) =  (1/x)^n
  2^(-3) =  (0.5)^3  =  0.125

So we flip x to 1/x and make n positive, then call helper normally.
```

---

## Recursion Tree Pattern

```
helper(x, n)
    |
    +-- helper(x, n/2)
            |
            +-- helper(x, n/4)
                    |
                    +-- helper(x, n/8)
                            |
                            ...
                            |
                            +-- helper(x, 0) = 1  <- base case

Depth of tree = log2(n)
Each level does ONE multiplication (or two for odd)
Total multiplications = O(log n)
```

---

## Dry Run 1 — Positive Exponent: `x = 2.0, n = 10`

### myPow entry

```
n = 10  -> not < 0  -> no change
x = 2.0,  n = 10
Call helper(2.0, 10)
```

---

### Call stack going DOWN (splitting n in half)

```
helper(2.0, 10)
  n=10, n%2==0
  calls helper(2.0, 10/2) = helper(2.0, 5)
  |
  +-- helper(2.0, 5)
        n=5, n%2==1 (odd)
        calls helper(2.0, 5/2) = helper(2.0, 2)
        |
        +-- helper(2.0, 2)
              n=2, n%2==0 (even)
              calls helper(2.0, 2/2) = helper(2.0, 1)
              |
              +-- helper(2.0, 1)
                    n=1, n%2==1 (odd)
                    calls helper(2.0, 1/2) = helper(2.0, 0)
                    |
                    +-- helper(2.0, 0)
                          n==0  -> BASE CASE -> return 1
```

---

### Call stack unwinding UP (computing results)

#### helper(2.0, 0)

```
n == 0  ->  return 1
```

#### helper(2.0, 1)

```
half = helper(2.0, 0) = 1
n=1, n%2 == 1  (ODD)
return half * half * num
     = 1    * 1    * 2.0
     = 2.0
```

#### helper(2.0, 2)

```
half = helper(2.0, 1) = 2.0
n=2, n%2 == 0  (EVEN)
return half * half
     = 2.0  * 2.0
     = 4.0
```

#### helper(2.0, 5)

```
half = helper(2.0, 2) = 4.0
n=5, n%2 == 1  (ODD)
return half * half * num
     = 4.0  * 4.0  * 2.0
     = 32.0
```

#### helper(2.0, 10)

```
half = helper(2.0, 5) = 32.0
n=10, n%2 == 0  (EVEN)
return half * half
     = 32.0 * 32.0
     = 1024.0
```

### Final answer

```
myPow(2.0, 10) = 1024.0    (= 2^10 = 1024   CORRECT)
```

---

### Dry Run 1 — Complete Summary Table

| Call | n | n/2 | n%2 | half (returned from below) | return value |
|------|---|-----|-----|----------------------------|--------------|
| helper(2.0, 10) | 10 | 5 | 0 (even) | 32.0 | 32.0 * 32.0 = **1024.0** |
| helper(2.0, 5) | 5 | 2 | 1 (odd) | 4.0 | 4.0 * 4.0 * 2.0 = **32.0** |
| helper(2.0, 2) | 2 | 1 | 0 (even) | 2.0 | 2.0 * 2.0 = **4.0** |
| helper(2.0, 1) | 1 | 0 | 1 (odd) | 1 | 1 * 1 * 2.0 = **2.0** |
| helper(2.0, 0) | 0 | — | — | — | **1** (base case) |

---

## Dry Run 2 — Negative Exponent: `x = 2.0, n = -3`

### myPow entry

```
n = -3  ->  n < 0  -> TRUE
  x = 1.0 / 2.0  =  0.5
  n = -(-3)       =  3

Now call helper(0.5, 3)
```

---

### Call stack going DOWN

```
helper(0.5, 3)
  n=3, n%2==1 (odd)
  calls helper(0.5, 3/2) = helper(0.5, 1)
  |
  +-- helper(0.5, 1)
        n=1, n%2==1 (odd)
        calls helper(0.5, 1/2) = helper(0.5, 0)
        |
        +-- helper(0.5, 0)
              n==0  ->  BASE CASE  ->  return 1
```

---

### Call stack unwinding UP

#### helper(0.5, 0)

```
n == 0  ->  return 1
```

#### helper(0.5, 1)

```
half = helper(0.5, 0) = 1
n=1, n%2 == 1  (ODD)
return half * half * num
     = 1    * 1    * 0.5
     = 0.5
```

#### helper(0.5, 3)

```
half = helper(0.5, 1) = 0.5
n=3, n%2 == 1  (ODD)
return half * half * num
     = 0.5  * 0.5  * 0.5
     = 0.125
```

### Final answer

```
myPow(2.0, -3) = 0.125    (= 1/(2^3) = 1/8 = 0.125   CORRECT)
```

---

### Dry Run 2 — Complete Summary Table

| Call | num | n | n%2 | half | return value |
|------|-----|---|-----|------|--------------|
| helper(0.5, 3) | 0.5 | 3 | 1 (odd) | 0.5 | 0.5 * 0.5 * 0.5 = **0.125** |
| helper(0.5, 1) | 0.5 | 1 | 1 (odd) | 1 | 1 * 1 * 0.5 = **0.5** |
| helper(0.5, 0) | 0.5 | 0 | — | — | **1** (base case) |

---

## Dry Run 3 — Power of 1: `x = 3.0, n = 1`

```
myPow: n=1, not negative, call helper(3.0, 1)

helper(3.0, 1)
  calls helper(3.0, 0) = 1   (base case)
  half = 1
  n=1, odd
  return 1 * 1 * 3.0 = 3.0

Answer: 3.0   CORRECT
```

---

## Dry Run 4 — Zero Exponent: `x = 5.0, n = 0`

```
myPow: n=0, not negative, call helper(5.0, 0)

helper(5.0, 0)
  n == 0  ->  return 1

Answer: 1.0   CORRECT  (any number to the power 0 = 1)
```

---

## Visual: Recursion Tree for x=2.0, n=10

```
                    helper(2.0, 10)
                          |
                   n=10, even
                   return 32*32 = 1024
                          |
                    helper(2.0, 5)
                          |
                   n=5, odd
                   return 4*4*2 = 32
                          |
                    helper(2.0, 2)
                          |
                   n=2, even
                   return 2*2 = 4
                          |
                    helper(2.0, 1)
                          |
                   n=1, odd
                   return 1*1*2 = 2
                          |
                    helper(2.0, 0)
                          |
                   n=0, BASE CASE
                   return 1

Reading bottom up:
  1  ->  2  ->  4  ->  32  ->  1024
  ^0    ^1     ^2      ^5      ^10
```

---

## Multiplication Count Comparison

```
Computing 2^10:

Naive (loop):
  2*2 = 4
  4*2 = 8
  8*2 = 16
  16*2 = 32
  32*2 = 64
  64*2 = 128
  128*2 = 256
  256*2 = 512
  512*2 = 1024
  9 multiplications

Fast exponentiation (this code):
  helper(2,0)=1
  helper(2,1): 1*1*2 = 2              [1 multiply]
  helper(2,2): 2*2   = 4              [1 multiply]
  helper(2,5): 4*4*2 = 32             [2 multiplies]
  helper(2,10): 32*32 = 1024          [1 multiply]
  Total: 5 multiplications only

For n=1000: naive=999, fast=log2(1000)~10 multiplications
```

---

## Why `long long` for n?

```
int  range: -2,147,483,648  to  2,147,483,647   (~2 * 10^9)
long long:  -9.2 * 10^18    to  9.2 * 10^18

When n is INT_MIN (-2147483648):
  -n would be 2147483648 which OVERFLOWS int
  With long long, -n is stored safely

That is why the parameter n is long long, not int.
```

---

## Edge Cases

| Case | Input | Expected | What code does |
|------|-------|----------|----------------|
| n = 0 | x=5.0, n=0 | 1.0 | base case returns 1 immediately |
| n = 1 | x=3.0, n=1 | 3.0 | one odd recursion: 1*1*3 |
| n negative | x=2.0, n=-3 | 0.125 | flip x to 1/x, negate n |
| x = 1.0 | x=1.0, n=100 | 1.0 | 1*1=1 at every level |
| x = 0.0 | x=0.0, n=5 | 0.0 | 0*0=0 at every level |
| n = INT_MIN | x=2.0, n=-2147483648 | tiny | long long prevents overflow |

---

## Complexity Analysis

```
TIME COMPLEXITY:
  Each recursive call halves n.
  n -> n/2 -> n/4 -> ... -> 1 -> 0
  Depth of recursion = log2(n)
  Each call does O(1) work (one or two multiplications)
  Total: O(log n)

SPACE COMPLEXITY:
  Recursion stack holds one frame per level.
  Stack depth = log2(n)
  Total: O(log n)

Compare with naive loop:
  Time: O(n)   Space: O(1)

For n = 10^9:
  Naive: 10^9 operations
  Fast:  log2(10^9) = ~30 operations
```

---

## Key Lines to Remember

```cpp
// KEY 1 — negative exponent handled BEFORE recursion
if (n < 0) {
    x = 1.0 / x;    // flip base
    n = -n;          // make exponent positive
}

// KEY 2 — base case
if (n == 0) return 1;

// KEY 3 — recurse with HALF the exponent (core of the algorithm)
double half = helper(num, n / 2);

// KEY 4 — even: square the half result
if (n % 2 == 0) return half * half;

// KEY 5 — odd: square the half result, multiply once more by num
else return half * half * num;
```

---

##### Notes: prepared for teaching — dry runs for n=10 (positive), n=-3 (negative), n=0 and n=1 (edge cases), with full recursion tree traced top to bottom and bottom to top.
---

# 34. Merge Intervals

**Problem:** Given an array of intervals where `intervals[i] = [start_i, end_i]`, merge all overlapping intervals and return an array of the non-overlapping intervals that cover all the intervals in the input.

**Example:**
```
Input:  [[1,3], [2,6], [8,10], [15,18]]
Output: [[1,6], [8,10], [15,18]]
Explanation: [1,3] and [2,6] overlap → merged to [1,6]

Input:  [[1,4], [4,5]]
Output: [[1,5]]
Explanation: [1,4] and [4,5] are considered overlapping (touching counts)
```

**Approach:**
1. **Sort** intervals by their start time — this ensures any overlapping interval must be adjacent after sorting.
2. Iterate through each interval:
   - If `merged` is empty **or** the current interval starts after the last merged interval ends → no overlap, just push it.
   - Otherwise → overlap detected; extend the end of the last merged interval to `max(current end, last merged end)`.
3. Return `merged`.

**Why sort first?** Without sorting, an interval far to the left could overlap with one already processed. Sorting guarantees we only ever need to compare with the last merged interval.

**Visual Walkthrough:**
```
Input (sorted): [[1,3], [2,6], [8,10], [15,18]]

Step 1: merged = []          → push [1,3]      merged = [[1,3]]
Step 2: 2 <= 3 (overlap!)   → extend end to max(6,3)=6   merged = [[1,6]]
Step 3: 8 > 6  (no overlap) → push [8,10]     merged = [[1,6],[8,10]]
Step 4: 15 > 10 (no overlap)→ push [15,18]    merged = [[1,6],[8,10],[15,18]]
```

**Edge case — interval fully contained:**
```
[[1,10], [2,4]]  →  2 <= 10 (overlap), max(4,10)=10  →  [[1,10]]  ✓
```

**Code:**
```cpp
vector<vector<int>> merge(vector<vector<int>>& intervals) {
    vector<vector<int>> merged;
    sort(intervals.begin(), intervals.end());   // sort by start time
    for(auto interval : intervals){
        // No overlap: current starts after last merged interval ends
        if(merged.empty() || interval[0] > merged.back()[1]){
            merged.push_back(interval);
        }
        else{
            // Overlap: extend the end of the last merged interval
            merged.back()[1] = max(interval[1], merged.back()[1]);
        }
    }
    return merged;
}
```

**Complexity:**
- Time: $O(n \log n)$ — dominated by the sort; the merge pass is $O(n)$
- Space: $O(n)$ — output array (or $O(\log n)$ if only counting auxiliary space for sorting)

**Key Takeaway:** Sorting transforms a potentially complex pairwise comparison problem into a single linear scan — you only ever need to look at the last interval you've added.

---
### 35. Combination Sum

**Problem:** Given an array of **distinct** integers `candidates` and a `target`, return all unique combinations of candidates that sum to `target`. The same number may be used **unlimited times**. The answer may be returned in any order.

**Example:**
```
Input:  candidates = [2, 3, 6, 7],  target = 7
Output: [[2,2,3], [7]]

Input:  candidates = [2, 3, 5],  target = 8
Output: [[2,2,2,2], [2,3,3], [3,5]]
```

**Approach (Backtracking):**

At every index we have two choices:
1. **Take** `candidates[ind]` — subtract it from target and stay at the same index (we can reuse it).
2. **Not take** — move to the next index with the target unchanged.

We prune early when:
- `target < 0` — current path already overshoots
- `ind >= size` — no more candidates to consider
- `target >= candidates[ind]` guard before taking — avoids a wasted recursive call that would immediately hit `target < 0`

**Recursion Tree for `[2,3,6,7]`, target = 7:**
```
                        (ind=0, target=7)
                       /                \
          take 2 (ind=0, t=5)     skip (ind=1, t=7)
           /           \                    \
  take 2 (0,t=3)  skip (1,t=5)        take 3 (1,t=4)  ...
   /        \                           /        \
(0,t=1)  (1,t=3)                   (1,t=1)    (2,t=4)
   |        / \                        |
(0,t=-1) (1,t=0)✓ (2,t=3)          skip→(2,t=1)→...
 prune   [2,2,3]
                                              ...eventually (3,t=0)✓ → [7]
```

**Why stay at the same index when taking?**
Because each candidate can be used multiple times. Moving to `ind+1` after taking would prevent reuse.

**Code:**
```cpp
void helper(int ind, vector<int>& candidates, int target,
            vector<vector<int>>& ans, vector<int>& current, int size) {
    // base case
    if (target < 0 || ind >= size) {
        return;
    }
    if (target == 0) {
        ans.push_back(current);
        return;
    }

    // take (only if current candidate doesn't overshoot)
    if (target >= candidates[ind]) {
        current.push_back(candidates[ind]);
        helper(ind, candidates, target - candidates[ind], ans, current, size);  // stay at same index
        current.pop_back();  // backtrack
    }

    // not take — move to next candidate
    helper(ind + 1, candidates, target, ans, current, size);
}

vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
    int ind = 0, n = candidates.size();
    vector<vector<int>> ans;
    vector<int> current;
    helper(ind, candidates, target, ans, current, n);
    return ans;
}
```

**Complexity:**
- Time: $O(2^{t/m})$ where $t$ = target and $m$ = smallest candidate — the recursion tree depth is at most $t/m$ and branches two ways at each node
- Space: $O(t/m)$ — maximum recursion depth (not counting output)

**Key Takeaway:** The trick of **not incrementing the index on "take"** is what enables unlimited reuse of a candidate — a subtle but important difference from standard subset/combination problems where you always move forward.

---

# 36. Find Missing and Repeating Numbers

> **Problem:** In an array of size N containing numbers from 1 to N, one number appears twice (repeating) and one number is missing. Find both.
> **Three Approaches:** Brute Force → Hashing → Math (each better than the last)

---

## The Problem

```
Input array of size N = 5, containing numbers that should be [1, 2, 3, 4, 5]
but one number appears TWICE and one number is MISSING.

Example:
  arr = [4, 3, 6, 2, 3, 5]   N = 6
  Expected range: 1 to 6
  3 appears twice  -> repeating = 3
  1 is missing     -> missing   = 1

For dry run we use:
  arr = [3, 1, 2, 5, 3, 4]   N = 6
  3 appears twice  -> repeating = 3
  6 is missing     -> missing   = 6
```

---

## Approach 1 — Brute Force

### Code

```cpp
vector<int> findMissingRepeatingNumbers(vector<int> &arr, int n) {
    int repeating = -1, missing = -1;

    for (int i = 1; i <= n; i++) {        // outer: try each number 1..n
        int count = 0;

        for (int j = 0; j < n; j++) {     // inner: scan whole array
            if (arr[j] == i) {
                count++;
            }
        }

        if (count > 1) {
            repeating = i;                 // seen more than once
        }

        if (count == 0) {
            missing = i;                   // never seen
        }

        if (repeating != -1 && missing != -1) {
            break;                         // both found — stop early
        }
    }

    return {repeating, missing};
}
// TC: O(n^2)   SC: O(1)
```

### Intuition

```
For every number i from 1 to n:
  Count how many times i appears in arr.
  count > 1  ->  i is the repeating number
  count == 0 ->  i is the missing number
```

---

### Brute Force — Full Dry Run

**Input:** `arr = [3, 1, 2, 5, 3, 4]`,  `n = 6`
**Expected output:** `repeating = 3`,  `missing = 6`

---

#### Outer loop i = 1

```
i = 1,  count = 0
  j=0: arr[0]=3, 3==1? NO
  j=1: arr[1]=1, 1==1? YES  -> count=1
  j=2: arr[2]=2, 2==1? NO
  j=3: arr[3]=5, 5==1? NO
  j=4: arr[4]=3, 3==1? NO
  j=5: arr[5]=4, 4==1? NO

count = 1
  count > 1?  NO  -> repeating stays -1
  count == 0? NO  -> missing stays -1

repeating=-1, missing=-1  -> continue
```

#### Outer loop i = 2

```
i = 2,  count = 0
  j=0: arr[0]=3, 3==2? NO
  j=1: arr[1]=1, 1==2? NO
  j=2: arr[2]=2, 2==2? YES  -> count=1
  j=3: arr[3]=5, 5==2? NO
  j=4: arr[4]=3, 3==2? NO
  j=5: arr[5]=4, 4==2? NO

count = 1
  count > 1?  NO  -> repeating stays -1
  count == 0? NO  -> missing stays -1

repeating=-1, missing=-1  -> continue
```

#### Outer loop i = 3

```
i = 3,  count = 0
  j=0: arr[0]=3, 3==3? YES  -> count=1
  j=1: arr[1]=1, 1==3? NO
  j=2: arr[2]=2, 2==3? NO
  j=3: arr[3]=5, 5==3? NO
  j=4: arr[4]=3, 3==3? YES  -> count=2
  j=5: arr[5]=4, 4==3? NO

count = 2
  count > 1?  YES -> repeating = 3
  count == 0? NO  -> missing stays -1

repeating=3, missing=-1  -> both not found yet, continue
```

#### Outer loop i = 4

```
i = 4,  count = 0
  j=0: arr[0]=3, 3==4? NO
  j=1: arr[1]=1, 1==4? NO
  j=2: arr[2]=2, 2==4? NO
  j=3: arr[3]=5, 5==4? NO
  j=4: arr[4]=3, 3==4? NO
  j=5: arr[5]=4, 4==4? YES  -> count=1

count = 1
  count > 1?  NO
  count == 0? NO  -> missing stays -1

repeating=3, missing=-1  -> continue
```

#### Outer loop i = 5

```
i = 5,  count = 0
  j=0: arr[0]=3, 3==5? NO
  j=1: arr[1]=1, 1==5? NO
  j=2: arr[2]=2, 2==5? NO
  j=3: arr[3]=5, 5==5? YES  -> count=1
  j=4: arr[4]=3, 3==5? NO
  j=5: arr[5]=4, 4==5? NO

count = 1
  count > 1?  NO
  count == 0? NO  -> missing stays -1

repeating=3, missing=-1  -> continue
```

#### Outer loop i = 6

```
i = 6,  count = 0
  j=0: arr[0]=3, 3==6? NO
  j=1: arr[1]=1, 1==6? NO
  j=2: arr[2]=2, 2==6? NO
  j=3: arr[3]=5, 5==6? NO
  j=4: arr[4]=3, 3==6? NO
  j=5: arr[5]=4, 4==6? NO

count = 0
  count > 1?  NO
  count == 0? YES -> missing = 6

repeating=3, missing=6
  both != -1  -> BREAK early!
```

#### Brute Force Result

```
return {repeating, missing} = {3, 6}

Repeating = 3   (appeared 2 times)
Missing   = 6   (appeared 0 times)
```

#### Brute Force Iteration Summary Table

| i | j loop counts | count | repeating | missing | action |
|---|---------------|-------|-----------|---------|--------|
| 1 | scanned all 6 | 1 | -1 | -1 | continue |
| 2 | scanned all 6 | 1 | -1 | -1 | continue |
| 3 | scanned all 6 | 2 | 3 | -1 | repeating found |
| 4 | scanned all 6 | 1 | 3 | -1 | continue |
| 5 | scanned all 6 | 1 | 3 | -1 | continue |
| 6 | scanned all 6 | 0 | 3 | 6 | missing found -> BREAK |

---

## Approach 2 — Hashing

### Code

```cpp
vector<int> findMissingRepeatingNo(vector<int>& nums) {
    int n = nums.size();
    int repeating = -1, missing = -1;

    vector<int> hash(n + 1, 0);      // hash[0..n] all initialised to 0

    // Pass 1: count frequency of each number
    for (int i = 0; i < n; i++) {
        hash[nums[i]]++;
    }

    // Pass 2: scan hash to find repeating and missing
    for (int i = 1; i <= n; i++) {
        if (hash[i] > 1) {
            repeating = i;
        }
        else if (hash[i] == 0) {
            missing = i;
        }

        if (repeating != -1 && missing != -1) {
            break;
        }
    }

    return {repeating, missing};
}
// TC: O(n)   SC: O(n)
```

### Intuition

```
Instead of scanning the whole array for each number (O(n^2)),
count all frequencies in ONE pass, then read the hash table.

hash[i] = 2  ->  i appeared twice  ->  repeating
hash[i] = 0  ->  i never appeared  ->  missing
```

---

### Hashing — Full Dry Run

**Input:** `nums = [3, 1, 2, 5, 3, 4]`,  `n = 6`

---

#### Pass 1 — Build frequency hash table

Initial hash: `[0, 0, 0, 0, 0, 0, 0]`  (indices 0 to 6)

```
i=0: nums[0]=3  -> hash[3]++
  hash: [0, 0, 0, 1, 0, 0, 0]

i=1: nums[1]=1  -> hash[1]++
  hash: [0, 1, 0, 1, 0, 0, 0]

i=2: nums[2]=2  -> hash[2]++
  hash: [0, 1, 1, 1, 0, 0, 0]

i=3: nums[3]=5  -> hash[5]++
  hash: [0, 1, 1, 1, 0, 1, 0]

i=4: nums[4]=3  -> hash[3]++
  hash: [0, 1, 1, 2, 0, 1, 0]
                  ^
              now 2! -> 3 appeared twice

i=5: nums[5]=4  -> hash[4]++
  hash: [0, 1, 1, 2, 1, 1, 0]

Final hash table:
  index:  0   1   2   3   4   5   6
  value: [0,  1,  1,  2,  1,  1,  0]
                      ^               ^
                 hash[3]=2        hash[6]=0
                 (repeating)      (missing)
```

---

#### Pass 2 — Scan hash to find answer

```
i=1: hash[1]=1  -> not >1, not ==0  -> skip
i=2: hash[2]=1  -> not >1, not ==0  -> skip
i=3: hash[3]=2  -> 2 > 1  -> repeating = 3
i=4: hash[4]=1  -> not >1, not ==0  -> skip
i=5: hash[5]=1  -> not >1, not ==0  -> skip
i=6: hash[6]=0  -> == 0   -> missing = 6

repeating=3, missing=6  -> both found -> BREAK
```

#### Hashing Result

```
return {repeating, missing} = {3, 6}

Repeating = 3
Missing   = 6
```

#### Hashing Pass 1 — Step by Step Table

| i | nums[i] | hash[1] | hash[2] | hash[3] | hash[4] | hash[5] | hash[6] |
|---|---------|---------|---------|---------|---------|---------|---------|
| start | — | 0 | 0 | 0 | 0 | 0 | 0 |
| 0 | 3 | 0 | 0 | 1 | 0 | 0 | 0 |
| 1 | 1 | 1 | 0 | 1 | 0 | 0 | 0 |
| 2 | 2 | 1 | 1 | 1 | 0 | 0 | 0 |
| 3 | 5 | 1 | 1 | 1 | 0 | 1 | 0 |
| 4 | 3 | 1 | 1 | **2** | 0 | 1 | 0 |
| 5 | 4 | 1 | 1 | 2 | 1 | 1 | 0 |

---

## Approach 3 — Mathematical Formula (Most Optimal)

### Code

```cpp
vector<int> findMissingRepeatingNo(vector<int>& nums) {
    long long n = nums.size();

    // Expected sum of 1..n
    long long SN  = (n * (n + 1)) / 2;

    // Expected sum of squares of 1..n
    long long S2N = (n * (n + 1) * (2 * n + 1)) / 6;

    // Actual sum and sum of squares from array
    long long S = 0, S2 = 0;
    for (int i = 0; i < n; i++) {
        S  += nums[i];
        S2 += (long long)nums[i] * nums[i];
    }

    long long val1 = S  - SN;    // val1 = x - y
    long long val2 = S2 - S2N;   // val2 = x^2 - y^2

    // x^2 - y^2 = (x+y)(x-y)  =>  x+y = val2 / val1
    val2 = val2 / val1;           // val2 = x + y

    int x = (val1 + val2) / 2;   // x = repeating
    int y = x - val1;             // y = missing

    return {x, y};
}
// TC: O(n)   SC: O(1)
```

### Math Derivation

```
Let:
  x = repeating number
  y = missing number

EQUATION 1:
  Actual sum S   = Expected sum SN + x - y
  S - SN         = x - y
  val1           = x - y          ... (1)

EQUATION 2:
  Actual sum of squares S2  = Expected S2N + x^2 - y^2
  S2 - S2N                  = x^2 - y^2
  val2                      = (x+y)(x-y)  [difference of squares]
  val2 / val1               = x + y       ... (2)

Solving (1) and (2):
  Add:      (x - y) + (x + y) = val1 + val2
            2x = val1 + val2
            x  = (val1 + val2) / 2         <- repeating

  Subtract: x - (x - y) = x - val1
            y = x - val1                   <- missing
```

---

### Math Approach — Full Dry Run

**Input:** `nums = [3, 1, 2, 5, 3, 4]`,  `n = 6`

---

#### Step 1 — Compute expected values

```
n = 6

SN  = n*(n+1)/2         = 6*7/2           = 21
S2N = n*(n+1)*(2n+1)/6  = 6*7*13/6        = 91
```

---

#### Step 2 — Compute actual values from array

```
arr = [3, 1, 2, 5, 3, 4]

i=0: S  += 3    -> S=3    S2 += 3*3=9   -> S2=9
i=1: S  += 1    -> S=4    S2 += 1*1=1   -> S2=10
i=2: S  += 2    -> S=6    S2 += 2*2=4   -> S2=14
i=3: S  += 5    -> S=11   S2 += 5*5=25  -> S2=39
i=4: S  += 3    -> S=14   S2 += 3*3=9   -> S2=48
i=5: S  += 4    -> S=18   S2 += 4*4=16  -> S2=64

Final: S = 18,   S2 = 64
```

---

#### Step 3 — Compute val1 and val2

```
val1 = S  - SN   = 18 - 21  = -3
val2 = S2 - S2N  = 64 - 91  = -27
```

---

#### Step 4 — Solve for x + y

```
val2 = val2 / val1  =  -27 / -3  =  9

So:
  val1 = x - y = -3
  val2 = x + y =  9
```

---

#### Step 5 — Solve for x (repeating) and y (missing)

```
x = (val1 + val2) / 2
  = (-3   +  9  ) / 2
  = 6 / 2
  = 3         <- repeating number

y = x - val1
  = 3 - (-3)
  = 3 + 3
  = 6         <- missing number
```

#### Math Approach Result

```
return {x, y} = {3, 6}

Repeating = 3
Missing   = 6
```

#### Math Approach — Iteration Table (Step 2)

| i | nums[i] | S (running) | nums[i]^2 | S2 (running) |
|---|---------|-------------|-----------|--------------|
| start | — | 0 | — | 0 |
| 0 | 3 | 3 | 9 | 9 |
| 1 | 1 | 4 | 1 | 10 |
| 2 | 2 | 6 | 4 | 14 |
| 3 | 5 | 11 | 25 | 39 |
| 4 | 3 | 14 | 9 | 48 |
| 5 | 4 | 18 | 16 | 64 |

#### Math Approach — Formula Chain

```
S=18   SN=21   ->   val1 = 18-21 = -3   (= x - y)
S2=64  S2N=91  ->   val2 = 64-91 = -27  (= x^2 - y^2)

val2 / val1  =  -27 / -3  =  9           (= x + y)

x = (-3 + 9) / 2  =  3   [repeating]
y =  3 - (-3)     =  6   [missing]
```

---

## All Three Results Verified

```
Input:  [3, 1, 2, 5, 3, 4]   n=6

Approach 1 (Brute Force):  {3, 6}  correct
Approach 2 (Hashing):      {3, 6}  correct
Approach 3 (Math):         {3, 6}  correct

Repeating = 3   (appears at index 0 and index 4)
Missing   = 6   (never appears in the array)
```

---

## Comparison of All Three Approaches

| Approach | Time Complexity | Space Complexity | Notes |
|----------|-----------------|------------------|-------|
| Brute Force | O(n^2) | O(1) | Two nested loops. Simplest to understand. |
| Hashing | O(n) | O(n) | Two passes, one hash array of size n+1. |
| Math (optimal) | O(n) | O(1) | One pass, no extra space. Uses algebra. |

---

## Why `long long` in the Math Approach?

```
n can be up to 10^5.
n^2 = 10^10  ->  exceeds int range (max ~2.1 * 10^9).

Sum of squares S2N = n*(n+1)*(2n+1)/6
For n = 10^5:
  10^5 * 10^5 * 2*10^5 = 2 * 10^15  -> needs long long (max ~9.2 * 10^18)

That is why:
  long long n = nums.size();
  S2 += (long long)nums[i] * nums[i];   <- cast before multiply!
```

---

## Edge Cases

| Case | What happens |
|------|-------------|
| Repeating is 1 | val1 will be negative, math still works correctly |
| Missing is n | hash[n] = 0 is found at last iteration of pass 2 |
| Array size = 2 (minimum) | e.g. [2,2] -> repeating=2, missing=1 |
| Repeating and missing are adjacent | e.g. [1,3,3,4,5] -> rep=3, miss=2; all approaches handle correctly |

---

## Key Formulas to Remember

```
Sum of 1 to n:            SN  = n*(n+1) / 2
Sum of squares of 1 to n: S2N = n*(n+1)*(2n+1) / 6

val1 = S  - SN   =  x - y
val2 = S2 - S2N  =  x^2 - y^2  =  (x+y)(x-y)
val2 / val1      =  x + y

x (repeating) = (val1 + val2) / 2
y (missing)   =  x - val1
```

---

*Notes prepared for teaching — all three approaches with complete dry runs for input [3,1,2,5,3,4], n=6.*

---

# 37. Majority Element II — Elements Appearing More Than n/3 Times

> **Algorithm:** HashMap frequency count
> **Time Complexity:** O(n) — single pass to build map + one pass over map
> **Space Complexity:** O(n) — hashmap stores at most n distinct elements

---

## The Problem

Find all elements in the array that appear **more than n/3 times**.

```
Key observation:
  At most 2 elements can appear more than n/3 times in any array.
  Proof: if 3 elements each appear > n/3 times,
         their total count > n/3 + n/3 + n/3 = n  (impossible)

So the answer vector always has 0, 1, or 2 elements.
```

---

## The Code

```cpp
vector<int> majorityElement(vector<int>& nums) {
    int n = nums.size();
    vector<int> ans;
    unordered_map<int, int> map;

    // threshold: element must appear MORE than this many times
    int majorityElement = n / 3;

    // PASS 1: count frequency of every element
    for (int i = 0; i < n; i++) {
        map[nums[i]]++;

        // --- COMMENTED OPTIMISATION (explained at bottom) ---
        // if (map[nums[i]] == majorityElement + 1) {
        //     ans.push_back(nums[i]);
        // }
        // if (ans.size() == 2)
        //     break;
    }

    // PASS 2: collect all elements whose frequency > n/3
    for (auto it : map) {
        if (it.second > majorityElement) {
            ans.push_back(it.first);
        }
    }

    return ans;
}

// Time Complexity: O(n) — one pass to build the map + one pass to iterate it.
// Space Complexity: O(n) — unordered_map can store up to n elements (ans is O(1)).
```

---

## Intuition

```
threshold = n / 3   (integer division)

An element qualifies if:  frequency > threshold
                      i.e. frequency >= threshold + 1
                      i.e. frequency >= floor(n/3) + 1
                      i.e. appears more than n/3 times

Example: n = 8
  threshold = 8/3 = 2  (integer division)
  element must appear > 2 times  (i.e. at least 3 times)

Example: n = 9
  threshold = 9/3 = 3
  element must appear > 3 times  (i.e. at least 4 times)
```

---

## Dry Run

### Input

```
nums = [1, 1, 1, 3, 3, 2, 2, 2]
n    = 8
majorityElement (threshold) = 8 / 3 = 2

An element qualifies if it appears > 2 times (i.e. 3 or more times)
```

---

### PASS 1 — Build Frequency Map

**Initial map:** `{}` (empty)

---

#### i = 0

```
nums[0] = 1
map[1]++   ->   map[1] = 1

map: { 1:1 }
```

#### i = 1

```
nums[1] = 1
map[1]++   ->   map[1] = 2

map: { 1:2 }
```

#### i = 2

```
nums[2] = 1
map[1]++   ->   map[1] = 3

map: { 1:3 }
```

#### i = 3

```
nums[3] = 3
map[3]++   ->   map[3] = 1   (new entry)

map: { 1:3, 3:1 }
```

#### i = 4

```
nums[4] = 3
map[3]++   ->   map[3] = 2

map: { 1:3, 3:2 }
```

#### i = 5

```
nums[5] = 2
map[2]++   ->   map[2] = 1   (new entry)

map: { 1:3, 3:2, 2:1 }
```

#### i = 6

```
nums[6] = 2
map[2]++   ->   map[2] = 2

map: { 1:3, 3:2, 2:2 }
```

#### i = 7

```
nums[7] = 2
map[2]++   ->   map[2] = 3

map: { 1:3, 3:2, 2:3 }
```

---

### Pass 1 — Step by Step Table

| i | nums[i] | map[1] | map[2] | map[3] |
|---|---------|--------|--------|--------|
| start | — | 0 | 0 | 0 |
| 0 | 1 | **1** | 0 | 0 |
| 1 | 1 | **2** | 0 | 0 |
| 2 | 1 | **3** | 0 | 0 |
| 3 | 3 | 3 | 0 | **1** |
| 4 | 3 | 3 | 0 | **2** |
| 5 | 2 | 3 | **1** | 2 |
| 6 | 2 | 3 | **2** | 2 |
| 7 | 2 | 3 | **3** | 2 |

**Final map:** `{ 1:3, 2:3, 3:2 }`

---

### PASS 2 — Find Elements Above Threshold

```
threshold = majorityElement = 2
Condition: it.second > 2   (i.e. frequency >= 3)

Iterate over map entries:

  entry {1, 3}:  3 > 2  ->  TRUE   ->  ans.push_back(1)
                 ans = [1]

  entry {2, 3}:  3 > 2  ->  TRUE   ->  ans.push_back(2)
                 ans = [1, 2]

  entry {3, 2}:  2 > 2  ->  FALSE  ->  skip
```

---

### Pass 2 — Decision Table

| Element | Frequency | Frequency > threshold(2)? | Added to ans? |
|---------|-----------|---------------------------|---------------|
| 1 | 3 | 3 > 2 → YES | YES |
| 2 | 3 | 3 > 2 → YES | YES |
| 3 | 2 | 2 > 2 → NO  | NO  |

---

### Final Answer

```
return ans = [1, 2]

Verification:
  nums = [1, 1, 1, 3, 3, 2, 2, 2],   n = 8
  n/3  = 2.66...

  1 appears 3 times  ->  3 > 2.66  ->  YES, majority element
  2 appears 3 times  ->  3 > 2.66  ->  YES, majority element
  3 appears 2 times  ->  2 > 2.66  ->  NO

Output: [1, 2]   CORRECT
```

---

## The Commented-Out Optimisation Explained

```cpp
// if (map[nums[i]] == majorityElement + 1) {
//     ans.push_back(nums[i]);
// }
// if (ans.size() == 2)
//     break;
```

### What it does

```
Instead of waiting for Pass 2, push an element into ans
the EXACT moment its count crosses the threshold.

majorityElement + 1  is the first count that qualifies.
  threshold     = 2   (for n=8)
  threshold + 1 = 3   <- add to ans the moment count hits 3

This avoids re-scanning the whole map in Pass 2.

Once ans has 2 elements we know we have found both majority elements
(at most 2 can exist), so we BREAK out of Pass 1 early.
```

### Dry run with optimisation ON (same input)

```
i=0: nums[0]=1, map[1]=1,  1 == 3? NO
i=1: nums[1]=1, map[1]=2,  2 == 3? NO
i=2: nums[2]=1, map[1]=3,  3 == 3? YES -> ans=[1]
     ans.size()==2? NO, continue
i=3: nums[3]=3, map[3]=1,  1 == 3? NO
i=4: nums[4]=3, map[3]=2,  2 == 3? NO
i=5: nums[5]=2, map[2]=1,  1 == 3? NO
i=6: nums[6]=2, map[2]=2,  2 == 3? NO
i=7: nums[7]=2, map[2]=3,  3 == 3? YES -> ans=[1, 2]
     ans.size()==2? YES -> BREAK

No Pass 2 needed. Return [1, 2] directly.
```

### Why is it commented out?

```
The optimisation works ONLY IF both majority elements
cross threshold + 1 during Pass 1.

If the input has only ONE majority element (or zero),
ans.size() never reaches 2 inside the loop,
and we still need Pass 2 to collect that one element.

The commented version works correctly only when exactly 2
majority elements exist and both appear by the end of the loop.
The current (uncommented) version handles ALL cases safely.
```

---

## More Examples

### Example 2: Only one majority element

```
nums = [1, 2, 1, 1, 3],   n = 5
threshold = 5/3 = 1

map after Pass 1: { 1:3, 2:1, 3:1 }

Pass 2:
  1: 3 > 1  -> YES  -> ans = [1]
  2: 1 > 1  -> NO
  3: 1 > 1  -> NO

Output: [1]
```

### Example 3: No majority element

```
nums = [1, 2, 3, 4, 5, 6],   n = 6
threshold = 6/3 = 2

map after Pass 1: { 1:1, 2:1, 3:1, 4:1, 5:1, 6:1 }

Pass 2:
  All frequencies = 1.  1 > 2? NO for all.

Output: []
```

### Example 4: All elements same

```
nums = [7, 7, 7, 7],   n = 4
threshold = 4/3 = 1

map after Pass 1: { 7:4 }

Pass 2:
  7: 4 > 1  -> YES  -> ans = [7]

Output: [7]
```

---

## Complexity Analysis

```
PASS 1 — build frequency map
  Visit each of n elements once  ->  O(n)
  unordered_map insertion/lookup  ->  O(1) average per operation
  Total: O(n)

PASS 2 — scan map entries
  Map has at most n distinct keys  ->  O(n) worst case
  In practice, far fewer distinct elements
  Total: O(n)

Overall Time:  O(n) + O(n) = O(n)

Space:
  map stores at most n distinct elements  ->  O(n)
  ans stores at most 2 elements           ->  O(1)
  Overall Space: O(n)
```

---

## Key Points to Remember

```
1. THRESHOLD formula:
      majorityElement = n / 3    (integer division)
      qualify if:  frequency > majorityElement

2. AT MOST 2 elements can qualify (mathematically proven).
      3 elements each > n/3  =>  total > n  (impossible)

3. unordered_map:
      map[key]++  creates the key with value 0 then increments to 1
      if the key does not exist yet.
      So no need to check if key exists before incrementing.

4. Iterating map with auto:
      for (auto it : map)
        it.first  = key   (the number)
        it.second = value (its frequency)

5. Integer division matters:
      n=8:  8/3 = 2  (not 2.66)  threshold is 2
      n=9:  9/3 = 3               threshold is 3
      This is correct because "more than n/3" with n=9
      means frequency > 3, which is what integer division gives.
```

---

*Notes prepared for teaching — full dry run for [1,1,1,3,3,2,2,2] traced iteration by iteration for both passes, with explanation of the commented optimisation.*

---
# Combination Sum II — Unique Combinations Without Reuse

> **Algorithm:** Backtracking with duplicate skipping
> **Time Complexity:** O(2^n) — each element is either taken or skipped
> **Space Complexity:** O(n) — recursion depth + current combination storage

---

## The Problem

Given a collection of candidates (may contain **duplicates**) and a target,
find all **unique** combinations that sum to target.
Each number may only be used **once**.

```
Rules:
  1. Each candidate can be used ONCE only
  2. No duplicate combinations in the answer
  3. All numbers are positive
```

---

## The Code

```cpp
// Example of why target < 0 check matters:
// candidates = {100, 2}, target = 1
// target - 100 = 1 - 100 = -99 < 0  ->  return immediately

void helper(vector<int>& candidates, int target,
            vector<int>& current, int ind,
            vector<vector<int>>& ans) {

    // overshot — this path is invalid
    if (target < 0) {
        return;
    }

    // exact match — store this combination
    if (target == 0) {
        ans.push_back(current);
        return;
    }

    int n = candidates.size();

    for (int i = ind; i < n; i++) {

        // DUPLICATE SKIP: if current element == previous element
        // AND we are not at the start index of this call (i > ind),
        // skip to avoid generating the same combination again
        if (i > ind && candidates[i] == candidates[i - 1]) {
            continue;
        }

        current.push_back(candidates[i]);               // TAKE this element
        helper(candidates, target - candidates[i],       // recurse with reduced target
               current, i + 1, ans);                    // i+1: cannot reuse same index
        current.pop_back();                              // NOT TAKE — backtrack
    }
}


vector<vector<int>> combinationSum2(vector<int>& candidates, int target) {
    vector<vector<int>> ans;

    sort(begin(candidates), end(candidates));  // MUST sort for duplicate skip to work

    vector<int> current;
    helper(candidates, target, current, 0, ans);

    return ans;
}
```

---

## Why Sorting is Mandatory

```
Without sort, duplicates are not adjacent, so the skip condition
candidates[i] == candidates[i-1] cannot catch them reliably.

candidates = [10, 1, 2, 7, 6, 1, 5]   target = 8

After sort:  [ 1,  1,  2,  5,  6,  7, 10]
               ^   ^
          duplicates now adjacent -> easy to skip
```

---

## The Duplicate Skip — Deep Explanation

```cpp
if (i > ind && candidates[i] == candidates[i - 1]) continue;
```

```
This condition has TWO parts — BOTH must be true to skip:

Part 1:  i > ind
  "We are NOT at the first position in the current loop."
  If i == ind, we must try this element (it's the first choice at this level).
  The duplicate skip only applies when we are choosing the 2nd, 3rd, ... element
  at the same recursion level.

Part 2:  candidates[i] == candidates[i-1]
  "Current element equals the previous element."
  Since array is sorted, duplicates are adjacent.

WHY we need both conditions together:
  candidates = [1, 1, 2, 5],  target = 3

  Call: helper(target=3, ind=0)
    i=0: candidates[0]=1  ->  i > ind? 0 > 0? NO  ->  TAKE it  (first 1)
    i=1: candidates[1]=1  ->  i > ind? 1 > 0? YES
                              candidates[1]==candidates[0]? 1==1? YES
                              -> SKIP  (would duplicate first 1's combinations)
    i=2: candidates[2]=2  ->  no skip, try

  But inside the call from i=0 (first 1 taken):
    helper(target=2, ind=1)
      i=1: candidates[1]=1  ->  i > ind? 1 > 1? NO  ->  TAKE (second 1)
      ...
  This correctly generates [1,1,1] attempts while avoiding duplicates.
```

---

## Full Dry Run

### Input

```
candidates = [10, 1, 2, 7, 6, 1, 5]
target     = 8
```

### Step 1 — Sort

```
Before sort: [10,  1,  2,  7,  6,  1,  5]
After sort:  [ 1,  1,  2,  5,  6,  7, 10]
indices:       0   1   2   3   4   5   6
```

### Expected output

```
[1,1,6]   ->  1+1+6 = 8
[1,2,5]   ->  1+2+5 = 8
[1,7]     ->  1+7   = 8
[2,6]     ->  2+6   = 8
```

---

### Recursion Trace

**Notation:**
```
helper(target, ind, current)
TAKE   = push element, recurse with i+1
SKIP   = duplicate skip via continue
BT     = pop_back (backtrack)
STORE  = target==0, push to ans
PRUNE  = target<0, return
```

---

```
candidates = [1, 1, 2, 5, 6, 7, 10]
              0  1  2  3  4  5   6
```

---

#### helper(target=8, ind=0, current=[])

```
i=0: candidates[0]=1
     i>ind? 0>0? NO -> no skip
     current=[1], call helper(target=7, ind=1, current=[1])
```

---

##### helper(target=7, ind=1, current=[1])

```
  i=1: candidates[1]=1
       i>ind? 1>1? NO -> no skip
       current=[1,1], call helper(target=6, ind=2, current=[1,1])
```

###### helper(target=6, ind=2, current=[1,1])

```
    i=2: candidates[2]=2
         i>ind? 2>2? NO -> no skip
         current=[1,1,2], call helper(target=4, ind=3, current=[1,1,2])
```

**helper(target=4, ind=3, current=[1,1,2])**

```
      i=3: candidates[3]=5
           target-5 = 4-5 = -1
           current=[1,1,2,5], call helper(target=-1 ...) -> PRUNE (target<0)
           BT: current=[1,1,2]

      i=4: candidates[4]=6
           target-6 = 4-6 = -2
           current=[1,1,2,6], call helper(target=-2 ...) -> PRUNE
           BT: current=[1,1,2]

      i=5,6: similarly all overshoot -> PRUNE each time

      return (no match found)
```

```
         BT: current=[1,1]

    i=3: candidates[3]=5
         current=[1,1,5], call helper(target=1, ind=4, current=[1,1,5])
```

**helper(target=1, ind=4, current=[1,1,5])**

```
      i=4: candidates[4]=6
           6 > 1  -> PRUNE
      i=5: 7 > 1  -> PRUNE
      i=6: 10 > 1 -> PRUNE
      return (no match)
```

```
         BT: current=[1,1]

    i=4: candidates[4]=6
         current=[1,1,6], call helper(target=0, ind=5, current=[1,1,6])
```

**helper(target=0, ind=5, current=[1,1,6])**

```
      target==0  ->  STORE  -> ans = [[1,1,6]]
      return
```

```
         BT: current=[1,1]

    i=5: candidates[5]=7
         current=[1,1,7], call helper(target=-1 ...) -> PRUNE
         BT: current=[1,1]

    i=6: candidates[6]=10
         current=[1,1,10], call helper(target=-4 ...) -> PRUNE
         BT: current=[1,1]

    return
```

```
  BT: current=[1]

  i=2: candidates[2]=2
       current=[1,2], call helper(target=5, ind=3, current=[1,2])
```

###### helper(target=5, ind=3, current=[1,2])

```
    i=3: candidates[3]=5
         current=[1,2,5], call helper(target=0, ind=4, current=[1,2,5])
```

**helper(target=0, ind=4, current=[1,2,5])**

```
      target==0  ->  STORE  -> ans = [[1,1,6],[1,2,5]]
      return
```

```
         BT: current=[1,2]

    i=4: candidates[4]=6
         target-6 = 5-6 = -1 -> PRUNE
         BT: current=[1,2]

    i=5,6: similarly PRUNE

    return
```

```
  BT: current=[1]

  i=3: candidates[3]=5
       current=[1,5], call helper(target=2, ind=4, current=[1,5])
```

###### helper(target=2, ind=4, current=[1,5])

```
    i=4: candidates[4]=6
         6 > 2 -> PRUNE
    i=5,6: PRUNE
    return (no match)
```

```
  BT: current=[1]

  i=4: candidates[4]=6
       current=[1,6], call helper(target=1, ind=5, current=[1,6])
```

###### helper(target=1, ind=5, current=[1,6])

```
    i=5: candidates[5]=7
         7 > 1 -> PRUNE
    i=6: PRUNE
    return
```

```
  BT: current=[1]

  i=5: candidates[5]=7
       current=[1,7], call helper(target=0, ind=6, current=[1,7])
```

**helper(target=0, ind=6, current=[1,7])**

```
      target==0  ->  STORE  -> ans = [[1,1,6],[1,2,5],[1,7]]
      return
```

```
  BT: current=[1]

  i=6: candidates[6]=10
       target-10 = 7-10 = -3 -> PRUNE
       BT: current=[1]

  return
```

---

```
Back in helper(target=8, ind=0):
BT: current=[]

i=1: candidates[1]=1
     i>ind? 1>0? YES
     candidates[1]==candidates[0]? 1==1? YES
     -> DUPLICATE SKIP (continue)
     (skipping prevents regenerating [1,1,6], [1,2,5], [1,7] again
      starting from the second 1)
```

---

```
i=2: candidates[2]=2
     current=[2], call helper(target=6, ind=3, current=[2])
```

##### helper(target=6, ind=3, current=[2])

```
  i=3: candidates[3]=5
       current=[2,5], call helper(target=1, ind=4, current=[2,5])
```

**helper(target=1, ind=4, current=[2,5])**

```
    i=4: 6 > 1 -> PRUNE
    i=5: 7 > 1 -> PRUNE
    i=6: 10 > 1 -> PRUNE
    return
```

```
  BT: current=[2]

  i=4: candidates[4]=6
       current=[2,6], call helper(target=0, ind=5, current=[2,6])
```

**helper(target=0, ind=5, current=[2,6])**

```
      target==0  ->  STORE  -> ans = [[1,1,6],[1,2,5],[1,7],[2,6]]
      return
```

```
  BT: current=[2]

  i=5: candidates[5]=7
       target-7 = 6-7 = -1 -> PRUNE
  i=6: PRUNE

  return
```

---

```
Back in helper(target=8, ind=0):
BT: current=[]

i=3: candidates[3]=5
     current=[5], call helper(target=3, ind=4, current=[5])
```

##### helper(target=3, ind=4, current=[5])

```
  i=4: candidates[4]=6
       6 > 3 -> PRUNE
  i=5,6: PRUNE
  return (no match)
```

```
BT: current=[]

i=4: candidates[4]=6
     current=[6], call helper(target=2, ind=5, current=[6])
```

##### helper(target=2, ind=5, current=[6])

```
  i=5: candidates[5]=7
       7 > 2 -> PRUNE
  i=6: PRUNE
  return
```

```
BT: current=[]

i=5: candidates[5]=7
     current=[7], call helper(target=1, ind=6, current=[7])
```

##### helper(target=1, ind=6, current=[7])

```
  i=6: candidates[6]=10
       10 > 1 -> PRUNE
  return
```

```
BT: current=[]

i=6: candidates[6]=10
     current=[10], call helper(target=-2 ...) -> PRUNE
BT: current=[]

Loop ends. Return.
```

---

## Final Answer

```
ans = [[1,1,6], [1,2,5], [1,7], [2,6]]

Verification:
  [1,1,6]  ->  1+1+6 = 8  CORRECT
  [1,2,5]  ->  1+2+5 = 8  CORRECT
  [1,7]    ->  1+7   = 8  CORRECT
  [2,6]    ->  2+6   = 8  CORRECT
  No duplicates, no reused indices.
```

---

## Dry Run Summary — All STORE Events

| Combination stored | target when stored | ans after store |
|--------------------|--------------------|-----------------|
| [1,1,6] | 0 | [[1,1,6]] |
| [1,2,5] | 0 | [[1,1,6],[1,2,5]] |
| [1,7] | 0 | [[1,1,6],[1,2,5],[1,7]] |
| [2,6] | 0 | [[1,1,6],[1,2,5],[1,7],[2,6]] |

---

## Dry Run Summary — All DUPLICATE SKIP Events

| At level | i | ind | candidates[i] | candidates[i-1] | Action |
|----------|---|-----|---------------|-----------------|--------|
| helper(8,0) | 1 | 0 | 1 | 1 | SKIP (prevents duplicate starting with 2nd '1') |

---

## Recursion Tree (Condensed)
######  candidates = [10, 1, 2, 7, 6, 1, 5]   target = 8

######  After sort:  [ 1,  1,  2,  5,  6,  7, 10]

```
helper(8, ind=0, [])
├── TAKE 1 -> helper(7, ind=1, [1])
│   ├── TAKE 1 -> helper(6, ind=2, [1,1])
│   │   ├── TAKE 2 -> helper(4, ind=3, [1,1,2]) -> all overshoot -> return
│   │   ├── TAKE 5 -> helper(1, ind=4, [1,1,5]) -> all overshoot -> return
│   │   ├── TAKE 6 -> helper(0, ind=5, [1,1,6]) -> STORE *** [1,1,6]
│   │   ├── TAKE 7 -> helper(-1 ...)             -> PRUNE
│   │   └── TAKE 10-> helper(-4 ...)             -> PRUNE
│   ├── TAKE 2 -> helper(5, ind=3, [1,2])
│   │   ├── TAKE 5 -> helper(0, ind=4, [1,2,5])  -> STORE *** [1,2,5]
│   │   ├── TAKE 6 -> helper(-1 ...)              -> PRUNE
│   │   └── ...
│   ├── TAKE 5 -> helper(2, ind=4, [1,5])  -> all overshoot -> return
│   ├── TAKE 6 -> helper(1, ind=5, [1,6])  -> all overshoot -> return
│   ├── TAKE 7 -> helper(0, ind=6, [1,7])  -> STORE *** [1,7]
│   └── TAKE 10-> helper(-3 ...)           -> PRUNE
│
├── SKIP 1 (i=1, ind=0, duplicate of candidates[0]) ***
│
├── TAKE 2 -> helper(6, ind=3, [2])
│   ├── TAKE 5 -> helper(1, ind=4, [2,5])  -> all overshoot -> return
│   ├── TAKE 6 -> helper(0, ind=5, [2,6])  -> STORE *** [2,6]
│   ├── TAKE 7 -> helper(-1 ...)            -> PRUNE
│   └── TAKE 10-> helper(-4 ...)            -> PRUNE
│
├── TAKE 5 -> helper(3, ind=4, [5])   -> all overshoot -> return
├── TAKE 6 -> helper(2, ind=5, [6])   -> all overshoot -> return
├── TAKE 7 -> helper(1, ind=6, [7])   -> all overshoot -> return
└── TAKE 10-> helper(-2 ...)          -> PRUNE
```

---

## Comparison With Combination Sum I

| Property | Combination Sum I | Combination Sum II |
|----------|-------------------|--------------------|
| Reuse element | YES (unlimited times) | NO (each used once) |
| Duplicates in input | No | Yes |
| Recurse with | same index `i` | next index `i+1` |
| Duplicate skip needed | No | Yes (`i > ind && arr[i]==arr[i-1]`) |
| Sort needed | Not required | MANDATORY |

---

## Edge Cases

| Input | Output | Reason |
|-------|--------|--------|
| candidates=[1,1,1], target=2 | [[1,1]] | two 1s combine, third 1 skipped as duplicate |
| candidates=[2], target=1 | [] | 2 > 1, immediately pruned |
| candidates=[1,2,3], target=6 | [[1,2,3]] | only one combination possible |
| candidates=[100,2], target=1 | [] | 100 > 1 pruned, 2 > 1 pruned |

---

## Key Lines to Remember

```cpp
// KEY 1 — sort first (duplicates must be adjacent)
sort(begin(candidates), end(candidates));

// KEY 2 — base cases (order matters: check < 0 first)
if (target < 0) return;         // overshot
if (target == 0) {              // exact match
    ans.push_back(current);
    return;
}

// KEY 3 — loop starts from ind (not 0) to avoid reusing previous elements
for (int i = ind; i < n; i++)

// KEY 4 — duplicate skip (both conditions required)
if (i > ind && candidates[i] == candidates[i-1]) continue;

// KEY 5 — recurse with i+1 (not i) — each element used at most once
helper(candidates, target - candidates[i], current, i+1, ans);

// KEY 6 — backtrack (undo the TAKE)
current.pop_back();
```

---

## Complexity Analysis

```
TIME COMPLEXITY: O(2^n * n)
  Each element has 2 choices: TAKE or SKIP
  Total subsets explored: O(2^n)
  Copying a valid combination to ans: O(n)
  Total: O(2^n * n)

SPACE COMPLEXITY: O(n)
  Recursion stack depth: at most n levels (one element taken per level)
  current vector: at most n elements
  ans: not counted as extra space (it is the output)
  Total extra space: O(n)
```

---
*Notes prepared for teaching — full recursion trace for candidates=[10,1,2,7,6,1,5] target=8, every TAKE, SKIP, PRUNE, STORE, and BACKTRACK shown explicitly.*

---

## Binary Tree Problems

### BT-1. Inorder Traversal

**Problem:** Return the inorder (Left → Root → Right) traversal of a binary tree.

**Approach:** Recursive DFS — traverse left subtree, visit node, traverse right subtree.

**Code:**
```cpp
void helper(TreeNode* root, vector<int>& ans) {
    if (!root) return;
    helper(root->left, ans);
    ans.push_back(root->val);
    helper(root->right, ans);
}

vector<int> inorderTraversal(TreeNode* root) {
    vector<int> ans;
    helper(root, ans);
    return ans;
}
```
**Complexity:**
- Time: $O(n)$
- Space: $O(h)$ — recursion stack, where h is tree height

---

### BT-2. Preorder Traversal

**Problem:** Return the preorder (Root → Left → Right) traversal of a binary tree.

**Approach:** Visit the node first, then recurse into left and right subtrees.

**Code:**
```cpp
void helper(TreeNode* root, vector<int>& ans) {
    if (!root) return;
    ans.push_back(root->val);
    helper(root->left, ans);
    helper(root->right, ans);
}

vector<int> preorderTraversal(TreeNode* root) {
    vector<int> ans;
    helper(root, ans);
    return ans;
}
```
**Complexity:**
- Time: $O(n)$
- Space: $O(h)$

---

### BT-3. Postorder Traversal

**Problem:** Return the postorder (Left → Right → Root) traversal of a binary tree.

**Approach:** Recurse into left and right subtrees first, then visit the node.

**Code:**
```cpp
void helper(TreeNode* root, vector<int>& ans) {
    if (!root) return;
    helper(root->left, ans);
    helper(root->right, ans);
    ans.push_back(root->val);
}

vector<int> postorderTraversal(TreeNode* root) {
    vector<int> ans;
    helper(root, ans);
    return ans;
}
```
**Complexity:**
- Time: $O(n)$
- Space: $O(h)$

---

### BT-4. Level Order Traversal

**Problem:** Return the level-by-level traversal of a binary tree as a 2D vector.

**Approach:** BFS using a queue. Process all nodes at the current level before moving to the next.

**Code:**
```cpp
vector<vector<int>> levelOrder(TreeNode* root) {
    if (!root) return {};
    vector<vector<int>> ans;
    queue<TreeNode*> bfs;
    bfs.push(root);
    while (!bfs.empty()) {
        int n = bfs.size();
        vector<int> row;
        for (int i = 0; i < n; i++) {
            TreeNode* node = bfs.front(); bfs.pop();
            row.push_back(node->val);
            if (node->left)  bfs.push(node->left);
            if (node->right) bfs.push(node->right);
        }
        ans.push_back(row);
    }
    return ans;
}
```
**Complexity:**
- Time: $O(n)$
- Space: $O(n)$ — queue holds at most one full level

---

### BT-5. Maximum Depth of Binary Tree

**Problem:** Find the height (maximum depth) of a binary tree.

**Approach:** Recursively compute left and right subtree heights, return the greater one plus 1.

**Code:**
```cpp
int helper(TreeNode* root) {
    if (!root) return 0;
    int lh = helper(root->left);
    int rh = helper(root->right);
    return max(lh, rh) + 1;
}

int maxDepth(TreeNode* root) {
    return helper(root);
}
```
**Complexity:**
- Time: $O(n)$
- Space: $O(h)$

---

### BT-6. Balanced Binary Tree

**Problem:** Determine if a binary tree is height-balanced (left and right subtrees of every node differ in height by at most 1).

**Approach:** Use a modified height function that returns `INT_MAX` as a sentinel value the moment any subtree is found to be unbalanced. This avoids a separate validity check and solves in a single DFS pass.

**Code:**
```cpp
int helper(TreeNode* root) {
    if (!root) return 0;
    int lh = helper(root->left);
    int rh = helper(root->right);
    if (lh == INT_MAX || rh == INT_MAX) return INT_MAX;
    if (abs(lh - rh) > 1) return INT_MAX;
    return max(lh, rh) + 1;
}

bool isBalanced(TreeNode* root) {
    if (!root) return true;
    return helper(root) != INT_MAX;
}
```
**Complexity:**
- Time: $O(n)$
- Space: $O(h)$

---

### BT-7. Diameter of Binary Tree

**Problem:** Find the length of the longest path between any two nodes in a binary tree (the path may or may not pass through the root).

**Approach:** For each node, the diameter through it is `left_height + right_height`. Track the global maximum across all nodes during a single DFS height computation.

**Code:**
```cpp
int helper(TreeNode* root, int& diameter) {
    if (!root) return 0;
    int lh = helper(root->left, diameter);
    int rh = helper(root->right, diameter);
    diameter = max(diameter, lh + rh);
    return max(lh, rh) + 1;
}

int diameterOfBinaryTree(TreeNode* root) {
    int diameter = 0;
    helper(root, diameter);
    return diameter;
}
```
**Complexity:**
- Time: $O(n)$
- Space: $O(h)$

---

### BT-8. Maximum Path Sum

**Problem:** Find the maximum sum of any path in a binary tree (a path is any sequence of nodes — not necessarily through the root).

**Approach:** At each node, compute the max gain from left and right children (floored at 0 so we never take a negative branch). Update the global max with `left + right + node->val`. Return only one side upward (a path can't branch going up).

**Code:**
```cpp
int helper(TreeNode* root, int& maxi) {
    if (!root) return 0;
    int left  = max(0, helper(root->left, maxi));
    int right = max(0, helper(root->right, maxi));
    maxi = max(maxi, left + right + root->val);
    return root->val + max(left, right);
}

int maxPathSum(TreeNode* root) {
    int maxi = INT_MIN;
    helper(root, maxi);
    return maxi;
}
```
**Complexity:**
- Time: $O(n)$
- Space: $O(h)$

---

### BT-9. Left View of Binary Tree

**Problem:** Return the first node visible from the left side at each level.

**Approach:** BFS level-order traversal; capture the first node of each level (`i == 0`).

**Code:**
```cpp
vector<int> leftSideView(TreeNode* root) {
    if (!root) return {};
    queue<TreeNode*> bfs;
    vector<int> ans;
    bfs.push(root);
    while (!bfs.empty()) {
        int n = bfs.size();
        for (int i = 0; i < n; i++) {
            TreeNode* node = bfs.front(); bfs.pop();
            if (node->left)  bfs.push(node->left);
            if (node->right) bfs.push(node->right);
            if (i == 0) ans.push_back(node->val);
        }
    }
    return ans;
}
```
**Complexity:**
- Time: $O(n)$
- Space: $O(n)$

---

### BT-10. Right Side View of Binary Tree

**Problem:** Return the last node visible from the right side at each level.

**Approach:** BFS level-order traversal; capture the last node of each level (`i == n-1`).

**Code:**
```cpp
vector<int> rightSideView(TreeNode* root) {
    if (!root) return {};
    queue<TreeNode*> bfs;
    vector<int> ans;
    bfs.push(root);
    while (!bfs.empty()) {
        int n = bfs.size();
        for (int i = 0; i < n; i++) {
            TreeNode* node = bfs.front(); bfs.pop();
            if (node->left)  bfs.push(node->left);
            if (node->right) bfs.push(node->right);
            if (i == n - 1) ans.push_back(node->val);
        }
    }
    return ans;
}
```
**Complexity:**
- Time: $O(n)$
- Space: $O(n)$

---

### BT-11. Bottom View of Binary Tree

**Problem:** Return the bottom-most node at each horizontal distance from the root.

**Approach:** BFS with horizontal distance (HD) tracking. Left child gets `HD - 1`, right child gets `HD + 1`. Use a map from HD → value — overwriting on every visit ensures the deepest node wins. Collect results from `minHD` to `maxHD`.

**Code:**
```cpp
vector<int> bottomView(Node* root) {
    if (!root) return {};
    vector<int> ans;
    int minHD = 0, maxHD = 0;
    queue<pair<Node*, int>> bfs;
    unordered_map<int, int> mp;
    bfs.push({root, 0});
    while (!bfs.empty()) {
        int n = bfs.size();
        for (int i = 0; i < n; i++) {
            Node* node = bfs.front().first;
            int dist   = bfs.front().second;
            bfs.pop();
            minHD = min(minHD, dist);
            maxHD = max(maxHD, dist);
            mp[dist] = node->data;   // overwrite → deepest node wins
            if (node->left)  bfs.push({node->left,  dist - 1});
            if (node->right) bfs.push({node->right, dist + 1});
        }
    }
    for (int i = minHD; i <= maxHD; i++) ans.push_back(mp[i]);
    return ans;
}
```
**Complexity:**
- Time: $O(n)$
- Space: $O(n)$

---

### BT-12. Boundary Traversal of Binary Tree

**Problem:** Return all boundary nodes in anti-clockwise order: root → left boundary (top-down, excluding leaves) → all leaves (left-to-right) → right boundary (bottom-up, excluding leaves).

**Approach:** Split into three helpers — `leftBoundary` (iterative, skips leaves), `collectLeaf` (recursive preorder), and `rightBoundary` (iterative, skips leaves, reverse before appending).

**Code:**
```cpp
bool isLeaf(Node* root) {
    return root->left == NULL && root->right == NULL;
}

void leftBoundary(Node* root, vector<int>& ans) {
    if (!root) return;
    while (!isLeaf(root)) {
        ans.push_back(root->data);
        root = root->left ? root->left : root->right;
    }
}

void rightBoundary(Node* root, vector<int>& ans) {
    if (!root) return;
    vector<int> temp;
    while (!isLeaf(root)) {
        temp.push_back(root->data);
        root = root->right ? root->right : root->left;
    }
    for (int i = temp.size() - 1; i >= 0; i--) ans.push_back(temp[i]);
}

void collectLeaf(Node* root, vector<int>& ans) {
    if (!root) return;
    if (isLeaf(root)) { ans.push_back(root->data); return; }
    collectLeaf(root->left, ans);
    collectLeaf(root->right, ans);
}

vector<int> boundaryTraversal(Node* root) {
    vector<int> ans;
    if (!root) return ans;
    if (!isLeaf(root)) ans.push_back(root->data);
    leftBoundary(root->left, ans);
    collectLeaf(root, ans);
    rightBoundary(root->right, ans);
    return ans;
}
```
**Complexity:**
- Time: $O(n)$
- Space: $O(h)$ — recursion for leaf collection

---

### BT-13. Lowest Common Ancestor (LCA)

**Problem:** Given a binary tree and two nodes `p` and `q`, find their lowest common ancestor.

**Approach:** Recurse the tree. Return immediately if the current node is null, `p`, or `q`. If both left and right recursive calls return non-null, the current node is the LCA. Otherwise propagate the non-null result upward.

**Code:**
```cpp
TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
    if (!root) return root;
    if (root == p || root == q) return root;
    TreeNode* nodeA = lowestCommonAncestor(root->left,  p, q);
    TreeNode* nodeB = lowestCommonAncestor(root->right, p, q);
    if (!nodeA) return nodeB;
    if (!nodeB) return nodeA;
    return root;
}
```
**Complexity:**
- Time: $O(n)$
- Space: $O(h)$

---

### BT-14. Maximum Width of Binary Tree

**Problem:** Find the maximum width of a binary tree, where width counts nodes between the leftmost and rightmost nodes at any level (including nulls in between).

**Approach:** BFS with index-based node numbering. For a node at index `i`, its left child is `2*i+1` and right child `2*i+2`. Normalise indices at each level by subtracting the level's minimum to prevent integer overflow. Width = `last - first + 1`.

**Code:**
```cpp
int widthOfBinaryTree(TreeNode* root) {
    queue<pair<TreeNode*, long>> bfs;
    long ans = 0;
    bfs.push({root, 0});
    while (!bfs.empty()) {
        long minIdx = bfs.front().second;
        int size = bfs.size();
        long first = 0, last = 0;
        for (int i = 0; i < size; i++) {
            long currId = bfs.front().second - minIdx;  // normalise
            if (i == 0)      first = currId;
            if (i == size-1) last  = currId;
            TreeNode* node = bfs.front().first; bfs.pop();
            if (node->left)  bfs.push({node->left,  2 * currId + 1});
            if (node->right) bfs.push({node->right, 2 * currId + 2});
        }
        ans = max(ans, last - first + 1);
    }
    return ans;
}
```
**Complexity:**
- Time: $O(n)$
- Space: $O(n)$

---

### BT-15. Children Sum Property in Binary Tree

**Problem:** Check whether for every internal node, its value equals the sum of its children's values.

**Approach:** Leaf nodes and null nodes satisfy the property trivially. For internal nodes, verify the sum condition, then recurse into both children.

**Code:**
```cpp
bool isSumProperty(Node* root) {
    if (!root) return true;
    if (root->left == NULL && root->right == NULL) return true;
    int sum = 0;
    sum += root->left  ? root->left->data  : 0;
    sum += root->right ? root->right->data : 0;
    if (sum != root->data) return false;
    return isSumProperty(root->left) && isSumProperty(root->right);
}
```
**Complexity:**
- Time: $O(n)$
- Space: $O(h)$

---

### BT-16. Flatten Binary Tree to Linked List

**Problem:** Flatten a binary tree in-place into a linked list in preorder order (using the `right` pointer; `left` always `NULL`).

**Approach:** For each node with a left subtree, find the rightmost node of the left subtree and attach the current right subtree there. Move the entire left subtree to the right and null out the left. Recurse on `root->right`.

**Code:**
```cpp
void flatten(TreeNode* root) {
    if (!root) return;
    if (root->left) {
        TreeNode* temp = root->left;
        root->left = NULL;
        TreeNode* curr = temp;
        while (curr->right) curr = curr->right;
        curr->right = root->right;
        root->right = temp;
    }
    flatten(root->right);
}
```
**Complexity:**
- Time: $O(n)$
- Space: $O(h)$

---

### BT-17. Construct Binary Tree from Inorder and Preorder

**Problem:** Build a binary tree given its preorder and inorder traversal arrays.

**Approach:** The first element of preorder is always the root. Look up its position in inorder (via a hash map) to determine left and right subtree ranges. Recurse for both subtrees, incrementing the preorder index on each root creation.

**Code:**
```cpp
TreeNode* build(vector<int>& preorder, unordered_map<int,int>& mp,
                int& preIndex, int start, int end) {
    if (start > end) return NULL;
    TreeNode* root = new TreeNode(preorder[preIndex++]);
    int rootIndex = mp[root->val];
    root->left  = build(preorder, mp, preIndex, start, rootIndex - 1);
    root->right = build(preorder, mp, preIndex, rootIndex + 1, end);
    return root;
}

TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
    unordered_map<int,int> mp;
    for (int i = 0; i < (int)inorder.size(); i++) mp[inorder[i]] = i;
    int preIndex = 0, start = 0, end = inorder.size() - 1;
    return build(preorder, mp, preIndex, start, end);
}
```
**Complexity:**
- Time: $O(n)$
- Space: $O(n)$ — hash map + recursion stack

---

### BT-18. Construct Binary Tree from Inorder and Postorder

**Problem:** Build a binary tree given its postorder and inorder traversal arrays.

**Approach:** Mirror of preorder construction — the last element of postorder is always the root. Crucially, the **right subtree must be built before the left** because the postorder index decrements from the end (right subtree appears just before the root in postorder).

**Code:**
```cpp
TreeNode* build(vector<int>& postorder, unordered_map<int,int>& mp,
                int& postIndex, int start, int end) {
    if (start > end) return NULL;
    TreeNode* root = new TreeNode(postorder[postIndex--]);
    int rootIndex = mp[root->val];
    root->right = build(postorder, mp, postIndex, rootIndex + 1, end);
    root->left  = build(postorder, mp, postIndex, start, rootIndex - 1);
    return root;
}

TreeNode* buildTree(vector<int>& inorder, vector<int>& postorder) {
    unordered_map<int,int> mp;
    for (int i = 0; i < (int)inorder.size(); i++) mp[inorder[i]] = i;
    int postIndex = postorder.size() - 1, start = 0, end = inorder.size() - 1;
    return build(postorder, mp, postIndex, start, end);
}
```

> **Key insight:** Right subtree is built before left because postorder is read right-to-left (root is at the end, right subtree comes just before it).

**Complexity:**
- Time: $O(n)$
- Space: $O(n)$

---

### BT-19. Same Tree

**Problem:** Given the roots of two binary trees `p` and `q`, check if they are structurally identical with the same node values.

**Approach:** Recursive comparison — both null means equal; one null means not equal; values differ means not equal. Recurse on both left and right subtrees simultaneously.

**Code:**
```cpp
bool isSameTree(TreeNode* p, TreeNode* q) {
    if (!p && !q) return true;
    if (!p || !q) return false;
    if (p->val != q->val) return false;
    return isSameTree(p->left, q->left) && isSameTree(p->right, q->right);
}
```
**Complexity:**
- Time: $O(n)$ — visits every node once
- Space: $O(h)$ — recursion stack

---

### BT-20. Symmetric Tree

**Problem:** Check if a binary tree is a mirror of itself (symmetric around its centre).

**Approach:** A tree is symmetric if its left and right subtrees are mirrors of each other. Two subtrees are mirrors when their roots match, the left's left child mirrors the right's right child, and the left's right child mirrors the right's left child.

**Code:**
```cpp
bool helper(TreeNode* p1, TreeNode* p2) {
    if (!p1 && !p2) return true;
    if (!p1 || !p2) return false;
    if (p1->val != p2->val) return false;
    return helper(p1->left, p2->right) && helper(p1->right, p2->left);
}

bool isSymmetric(TreeNode* root) {
    if (!root->left && !root->right) return true;
    return helper(root->left, root->right);
}
```

> **Key insight:** Mirror check crosses sides — left child of one is compared with right child of the other, not the same side.

**Complexity:**
- Time: $O(n)$
- Space: $O(h)$

---

### BT-21. Root to Leaf Paths

**Problem:** Return all root-to-leaf paths in a binary tree as strings in the format `"1->2->5"`.

**Approach:** DFS while building a string. At each internal node, append `val + "->"`. At a leaf, append just `val` and push to the answer. Passing `temp` by value provides automatic backtracking.

**Code:**
```cpp
void helper(TreeNode* root, string temp, vector<string>& ans) {
    if (!root) return;
    if (!root->left && !root->right) {
        temp += to_string(root->val);
        ans.push_back(temp);
        return;
    }
    temp += to_string(root->val) + "->";
    helper(root->left,  temp, ans);
    helper(root->right, temp, ans);
}

vector<string> binaryTreePaths(TreeNode* root) {
    string temp = "";
    vector<string> ans;
    helper(root, temp, ans);
    return ans;
}
```

> **Note:** `temp` is passed by value (not reference), so each recursive call gets its own copy — no explicit backtracking needed.

**Complexity:**
- Time: $O(n \cdot h)$ — string copy at each node costs O(h)
- Space: $O(h)$ — recursion stack depth

---

### BT-22. Top View of Binary Tree

**Problem:** Return the nodes visible when looking at the tree from the top, ordered from left to right.

**Approach:** BFS with horizontal distance (HD) tracking. The key difference from bottom view — only the **first** node seen at each HD is kept (use `map.find()` to skip if already set). Collect from `minHD` to `maxHD`.

**Code:**
```cpp
vector<int> topView(Node* root) {
    if (!root) return {};
    vector<int> ans;
    int minHD = 0, maxHD = 0;
    queue<pair<Node*, int>> bfs;
    unordered_map<int, int> mp;
    bfs.push({root, 0});
    while (!bfs.empty()) {
        int n = bfs.size();
        for (int i = 0; i < n; i++) {
            Node* node = bfs.front().first;
            int dist   = bfs.front().second;
            bfs.pop();
            minHD = min(minHD, dist);
            maxHD = max(maxHD, dist);
            if (mp.find(dist) == mp.end())   // first-seen wins
                mp[dist] = node->data;
            if (node->left)  bfs.push({node->left,  dist - 1});
            if (node->right) bfs.push({node->right, dist + 1});
        }
    }
    for (int i = minHD; i <= maxHD; i++) ans.push_back(mp[i]);
    return ans;
}
```

| | Top View | Bottom View |
|---|---|---|
| Which node wins at each HD | First seen (shallowest) | Last seen (deepest) |
| Map update rule | Only if key absent | Always overwrite |

**Complexity:**
- Time: $O(n)$
- Space: $O(n)$

---

### BT-23. Vertical Order Traversal

**Problem:** Return nodes column by column. Within the same column and level, nodes are sorted by value.

**Approach:** BFS tracking both horizontal distance (HD) and level. Use a nested ordered map: `map<HD, map<level, multiset<val>>>`. The `multiset` handles multiple nodes at the same HD and level by sorting them. After BFS, flatten the map into the answer.

**Code:**
```cpp
vector<vector<int>> verticalTraversal(TreeNode* root) {
    vector<vector<int>> ans;
    map<int, map<int, multiset<int>>> mp;
    queue<pair<TreeNode*, pair<int,int>>> bfs;
    bfs.push({root, {0, 0}});
    while (!bfs.empty()) {
        TreeNode* node = bfs.front().first;
        int hd    = bfs.front().second.first;
        int level = bfs.front().second.second;
        bfs.pop();
        mp[hd][level].insert(node->val);
        if (node->left)  bfs.push({node->left,  {hd - 1, level + 1}});
        if (node->right) bfs.push({node->right, {hd + 1, level + 1}});
    }
    for (auto& [hd, levels] : mp) {
        vector<int> col;
        for (auto& [lvl, vals] : levels)
            col.insert(col.end(), vals.begin(), vals.end());
        ans.push_back(col);
    }
    return ans;
}
```

> **Why `multiset`?** Multiple nodes can share the same HD and level (e.g. in a complete binary tree). A multiset keeps them sorted and handles duplicates.

**Complexity:**
- Time: $O(n \log n)$ — ordered map + multiset insertions
- Space: $O(n)$

---

### BT-24. Zigzag Level Order Traversal

**Problem:** Return level-order traversal where odd levels go left-to-right and even levels go right-to-left (or vice versa), alternating each level.

**Approach:** Standard BFS, but use a `rev` flag to decide the placement index within each level's row. When `rev` is true, fill the row from right to left by using index `n-1-i` instead of `i`. Toggle `rev` after each level.

**Code:**
```cpp
vector<vector<int>> zigzagLevelOrder(TreeNode* root) {
    if (!root) return {};
    vector<vector<int>> ans;
    queue<TreeNode*> bfs;
    bfs.push(root);
    bool rev = false;
    while (!bfs.empty()) {
        int n = bfs.size();
        vector<int> row(n, 0);
        for (int i = 0; i < n; i++) {
            TreeNode* node = bfs.front(); bfs.pop();
            int idx = rev ? n - 1 - i : i;   // place based on direction
            row[idx] = node->val;
            if (node->left)  bfs.push(node->left);
            if (node->right) bfs.push(node->right);
        }
        rev = !rev;
        ans.push_back(row);
    }
    return ans;
}
```

> **Why pre-allocate `row(n, 0)` and use index tricks instead of reversing?** Avoids an extra O(n) reverse step per level — placement is done correctly in a single pass.

**Complexity:**
- Time: $O(n)$
- Space: $O(n)$

---

*Binary Tree section covers traversals (inorder, preorder, postorder, level-order, zigzag, left/right/top/bottom view, vertical order, boundary), structural queries (height, diameter, balanced check, width, LCA, children sum, same tree, symmetric tree), path problems (root-to-leaf paths, max path sum), tree construction from traversal pairs, and in-place transformation (flatten to linked list).*