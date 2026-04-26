int helper(TreeNode* root){
    if(!root) return 0;

    int lh=helper(root->left);
    int rh=helper(root->right);
    if(lh==INT_MAX || rh==INT_MAX) return INT_MAX;
    if(abs(lh-rh)>1) return INT_MAX;
    return max(lh,rh)+1;
}

bool isBalanced(TreeNode* root) {
    if(!root) return true;
    int ans=helper(root);
    return ans==INT_MAX?false:true;
}