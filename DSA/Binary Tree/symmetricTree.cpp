bool helper(TreeNode* p1,TreeNode *p2){
    if(!p1 && !p2) return true;
    if(!p1 || !p2) return false;

    if(p1->val!=p2->val) return false;

    return helper(p1->left,p2->right) && helper(p1->right,p2->left);
}

bool isSymmetric(TreeNode* root) {
    if(!root->left && !root->right) return true;

    return helper(root->left,root->right);
}