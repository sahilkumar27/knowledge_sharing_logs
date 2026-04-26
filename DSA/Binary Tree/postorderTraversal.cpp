void helper(TreeNode* root,vector<int> &ans){
    if(!root) return;

    helper(root->left,ans);
    helper(root->right,ans);
    ans.push_back(root->val);
}

vector<int> preorderTraversal(TreeNode* root) {
    vector<int> ans;
    helper(root,ans);
    return ans;
}