// {100, 2} target = 1
// target - 100 = 1 - 100 = -99 < 0 return
void helper(vector<int>& candidates, int target, vector<int>& current, int ind, vector<vector<int>>& ans){
    if(target < 0) {
        return;
    }
    if(target == 0) {
        ans.push_back(current);
        return;
    }

    int n = candidates.size();
    for(int i=ind; i<n; i++) {
        // if the current candidate is the same as the previous candidate then we can not take it
        if(i > ind && candidates[i] == candidates[i-1]) {
            continue;
        }
        current.push_back(candidates[i]); // take
        helper(candidates, target - candidates[i], current, i+1, ans); // we increase the index because we can not take the same element multiple times 
        
        current.pop_back(); // not take
    }
}


vector<vector<int>> combinationSum2(vector<int>& candidates, int target) {
    vector<vector<int>> ans;
    sort(begin(candidates), end(candidates));

    vector<int> current;
    helper(candidates, target, current, 0, ans);

    return ans;
}