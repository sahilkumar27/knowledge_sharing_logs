int helper(TreeNode* root,int &diameter){
    if(!root) return 0;

    int lh=helper(root->left,diameter);
    int rh=helper(root->right,diameter);
    diameter=max(diameter,lh+rh);
    return max(lh,rh)+1;
}

int diameterOfBinaryTree(TreeNode* root) {
    int diameter=0;
    helper(root,diameter);

    return diameter;
}