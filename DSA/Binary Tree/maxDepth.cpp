int helper(TreeNode* root){
    if(!root) return 0;

    int lh=helper(root->left);
    int rh=helper(root->right);

    return max(lh,rh)+1;
}

int maxDepth(TreeNode* root) {
    return helper(root);    
}