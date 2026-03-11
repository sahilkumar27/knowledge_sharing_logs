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