// Brute Force Approach
vector<int> findMissingRepeatingNumbers(vector<int> &arr, int n) {
    int repeating = -1, missing = -1;

    for (int i = 1; i <= n; i++) {
        int count = 0;

        for (int j = 0; j < n; j++) {
            if (arr[j] == i) {
                count++;
            }
        }

        if (count > 1) {
            repeating = i;
        }

        if (count == 0) {
            missing = i;
        }

        if (repeating != -1 && missing != -1) {
            break;
        }
    }

    return {repeating, missing};
}

// Time Complexity: O(n^2) due to nested loops
// Space Complexity: O(1) as we are using only a constant amount of extra space




// Optimal Approach using Hashing

vector<int> findMissingRepeatingNo(vector<int>& nums) {
    int n = nums.size();
    int repeating = -1, missing = -1;

    vector<int> hash(n + 1, 0);

    for (int i = 0; i < n; i++) {
        hash[nums[i]]++;
    }

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

// Time Complexity: O(n) due to single pass through the array and hash vector
// Space Complexity: O(n) due to the hash vector storing counts for each number from





// Optimal Approach using Mathematical Formulas

vector<int> findMissingRepeatingNo(vector<int>& nums) {
    long long n = nums.size();

    // Sum of first n natural numbers
    long long SN = (n * (n + 1)) / 2;

    // Sum of squares of first n natural numbers
    long long S2N = (n * (n + 1) * (2 * n + 1)) / 6;

    // Calculate actual sum and sum of squares from array
    long long S = 0, S2 = 0;

    for (int i = 0; i < n; i++) {
        S += nums[i];
        S2 += (long long)nums[i] * nums[i];
    }

    // Differences
    long long val1 = S - SN;        // x - y
    long long val2 = S2 - S2N;      // x^2 - y^2

    // x + y
    val2 = val2 / val1;

    // Solve for x (repeating) and y (missing)
    int x = (val1 + val2) / 2;
    int y = x - val1;

    return {x, y};   // {repeating, missing}
}

// Time Complexity: O(n) due to single pass through the array
// Space Complexity: O(1) as we are using only a constant amount of extra space