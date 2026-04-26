bool isSumProperty(Node *root) {
    if(!root) return true;
    // code here
    if(root->left==NULL && root->right==NULL) return true;
    
    int sum=0;
    sum+=root->left?root->left->data:0;
    sum+=root->right?root->right->data:0;
    
    if(sum!=root->data) return false;
    
    return isSumProperty(root->left) && isSumProperty(root->right);
}