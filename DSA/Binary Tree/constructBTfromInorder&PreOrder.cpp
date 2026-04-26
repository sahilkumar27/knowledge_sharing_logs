TreeNode* build(vector<int>& preorder,unordered_map<int,int> &mp,int &preIndex,int start,int end){
    if(start>end) return NULL;
    TreeNode *root=new TreeNode(preorder[preIndex++]);
    int rootIndex=mp[root->val];
    root->left=build(preorder,mp,preIndex,start,rootIndex-1);
    root->right=build(preorder,mp,preIndex,rootIndex+1,end);

    return root;
}

TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
    unordered_map<int,int> mp;
    for(int i=0;i<inorder.size();i++){
        mp[inorder[i]]=i;
    }

    int preIndex=0,start=0,end=inorder.size()-1;
    return build(preorder,mp,preIndex,start,end);
}