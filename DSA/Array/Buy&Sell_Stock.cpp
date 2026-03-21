int maxProfit(vector<int> &prices)
{
    // storing the minimum element as the first element and initializing the profit as 0.
    // Then we will iterate through the array and calculate the profit by subtracting the minimum element from the current element
    // and updating the profit if it is greater than the current profit. We will also update the minimum element if the current element is less than the minimum element.
    int minBuy = prices[0], profit = 0;
    for (int i = 1; i < prices.size(); i++)
    {
        profit = max(profit, prices[i] - minBuy);
        minBuy = min(minBuy, prices[i]);
    }

    return profit;
}

// Time Complexity: O(n) where n is the size of the input array.
// Space Complexity: O(1) as we are using only constant extra space.