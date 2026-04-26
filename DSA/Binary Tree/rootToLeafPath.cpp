void helper(TreeNode* rootA,string temp,vector<string> &ans){
    if(!rootA) return;
    if(!rootA->left && !rootA->right){
        temp+=to_string(rootA->val);
        ans.push_back(temp);
        return;
    }

    temp+=to_string(rootA->val)+"->";
    helper(rootA->left,temp,ans);
    helper(rootA->right,temp,ans);
}
vector<string> binaryTreePaths(TreeNode* root) {
    string temp="";
    vector<string> ans;
    helper(root,temp,ans);
    return ans;
}