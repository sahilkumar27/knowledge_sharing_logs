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