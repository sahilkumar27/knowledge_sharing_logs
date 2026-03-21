void nextPermutation(vector<int> &nums)
{
    // code here
    // Your code goes here
    int pivot = -1, n = nums.size();
    // need to find the rightmost element which is smaller than it's next , store the index in pivot
    for (int i = n - 2; i >= 0; i--)
    {
        if (nums[i] < nums[i + 1])
        {
            pivot = i;
            break;
        }
    }

    // if no such element exists then reverse the whole array

    if (pivot == -1)
    {
        // reverse
        int last = n - 1, start = 0;
        while (start < last)
        {
            swap(nums[start], nums[last]);
            start++;
            last--;
        }
    }

    // if element exists then find the element from the right which is greater than it, store the index in num

    else
    {
        // swap the arr[pivot] & arr[num]
        for (int i = n - 1; i >= 0; i--)
        {
            if (nums[i] > nums[pivot])
            {
                swap(nums[pivot], nums[i]);
                break;
            }
        }

        // reverse the element from index: pivot+1 to n-1
        int last = n - 1, start = pivot + 1;
        while (start < last)
        {
            swap(nums[start], nums[last]);
            start++;
            last--;
        }
    }
}

// Time Complexity: O(n) where n is the size of the input array.
// Space Complexity: O(1) as we are using only constant extra space.