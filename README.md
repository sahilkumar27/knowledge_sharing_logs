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

## 29. Remove Nth Node From End of Linked List

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

### 30. Count Inversions in an Array

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