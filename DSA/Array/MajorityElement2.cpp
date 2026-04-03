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

// Time Complexity: O(n) due to two passes through the array (counting frequencies and collecting results)
// Space Complexity: O(n) in the worst case due to the unordered_map storing frequencies of all unique elements in the array