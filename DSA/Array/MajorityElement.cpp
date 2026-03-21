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