vector<vector<int>> zigzagLevelOrder(TreeNode* root) {
    if(!root) return {};
    vector<vector<int>> ans;
    queue<TreeNode*> bfs;
    bfs.push(root);
    bool rev=false;
    while(!bfs.empty()){
        int n=bfs.size();
        vector<int> row(n,0);
        for(int i=0;i<n;i++){
            TreeNode *node=bfs.front();
            bfs.pop();
            int idx=rev?n-1-i:i;
            row[idx]=node->val;
            if(node->left) bfs.push(node->left);
            if(node->right) bfs.push(node->right);
        }
        rev=!rev;
        ans.push_back(row);
    }

    return ans;
}