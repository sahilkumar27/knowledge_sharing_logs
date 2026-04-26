TreeNode* build(vector<int>& postorder,unordered_map<int,int> &mp,int &postIndex,int start,int end){
    if(start>end) return NULL;
    TreeNode *root=new TreeNode(postorder[postIndex--]);
    int rootIndex=mp[root->val];
    root->right=build(postorder,mp,postIndex,rootIndex+1,end);
    root->left=build(postorder,mp,postIndex,start,rootIndex-1);

    return root;
}

TreeNode* buildTree(vector<int>& inorder, vector<int>& postorder) {
    unordered_map<int,int> mp;
    for(int i=0;i<inorder.size();i++){
        mp[inorder[i]]=i;
    }

    int postIndex=postorder.size()-1,start=0,end=inorder.size()-1;
    return build(postorder,mp,postIndex,start,end);
}