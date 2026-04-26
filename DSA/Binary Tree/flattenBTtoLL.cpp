void flatten(TreeNode* root) {
    if(!root) return;

    if(root->left){
        TreeNode *temp=root->left;
        root->left=NULL;
        TreeNode* curr=temp;
        while(curr->right!=NULL){
            curr=curr->right;
        }
        curr->right=root->right;
        root->right=temp;
    }

    flatten(root->right);
}