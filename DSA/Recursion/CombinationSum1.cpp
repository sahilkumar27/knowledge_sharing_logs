void helper(int ind, vector<int>& candidates, int target,
                vector<vector<int>>& ans, vector<int>& current, int size) {
        // base case
        if (target < 0 || ind>=size) {
            return;
        }

        if (target == 0) {
            ans.push_back(current);
            return;
        }

        // take
        //if the target is smaller than the current candidate then we can not take it
        if (target >= candidates[ind]) {
            current.push_back(candidates[ind]);
            // we do not increase the index because we can take the same element multiple times
            helper(ind, candidates, target - candidates[ind], ans, current, size);
            current.pop_back();
        }
        //not take
        helper(ind + 1, candidates, target, ans, current, size);
    }
    vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
        int ind = 0, n = candidates.size();
        vector<vector<int>> ans;
        vector<int> current;
        helper(ind, candidates, target, ans, current, n);
        return ans;
    }