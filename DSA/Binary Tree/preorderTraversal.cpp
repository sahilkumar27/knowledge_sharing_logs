void helper(TreeNode *root,vector<int> &ans){
    if(!root) return;

    ans.push_back(root->val);
    helper(root->left,ans);
    helper(root->right,ans);
}

vector<int> postorderTraversal(TreeNode* root) {
    vector<int> ans;
    helper(root,ans);
    return ans;
}