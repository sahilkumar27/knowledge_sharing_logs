int findDuplicate(vector<int>& nums) {
    int slow = nums[0], fast = nums[0];
    // Floyd's Tortoise and Hare (Cycle Detection) algorithm
    //loop detection
    do {
        slow = nums[slow];
        fast = nums[nums[fast]];
    } while (slow != fast);
    slow = nums[0];
    //finding the duplicate number
    while (slow != fast) {
        slow = nums[slow];
        fast = nums[fast];
    }
    return slow;
}
// Time Complexity: O(n)
// Space Complexity: O(1)



// // BRUTE FORCE APPROACH
// int findDuplicate(vector<int>& nums) {
//     sort(nums.begin(), nums.end());

//     for (int i = 0; i < nums.size() - 1; i++) {
//         if (nums[i] == nums[i + 1]) {
//             return nums[i];
//         }
//     }

//     return -1; // fallback if no duplicate found (shouldn't happen per problem constraints)
// }
// // Time Complexity: O(n log n) due to sorting
// // Space Complexity: O(1) if sorting in-place, otherwise O(n) due to sorting space complexity



// // USING HASH SET
// int findDupliucate(vector<int>& nums) {
//     unordered_set<int> s;

//     for(auto val : nums) {
//         if(s.find(val) != s.end()) {
//             return val;
//         }
//         else {
//             s.insert(val);
//         }
//     }
//     return -1; // fallback if no duplicate found (shouldn't happen per problem constraints)
// }
// // Time Complexity: O(n) due to single pass through the array
// // Space Complexity: O(n) due to the unordered_set storing up to n-1 unique numbers in the worst case.