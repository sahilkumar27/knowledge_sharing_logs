TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
    if(!root) return root;
    if(root==p || root==q) return root;

    TreeNode *nodeA=lowestCommonAncestor(root->left,p,q);
    TreeNode *nodeB=lowestCommonAncestor(root->right,p,q);
    
    if(!nodeA) return nodeB;
    if(!nodeB) return nodeA;

    return root;
}