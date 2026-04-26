vector<vector<int>> levelOrder(TreeNode* root) {
    if(!root) return {};
    vector<vector<int>> ans;
    queue<TreeNode*> bfs;
    bfs.push(root);
    while(!bfs.empty()){
        int n=bfs.size();
        vector<int> row;
        for(int i=0;i<n;i++){
            TreeNode* node=bfs.front();
            bfs.pop();
            row.push_back(node->val);
            if(node->left) bfs.push(node->left);
            if(node->right) bfs.push(node->right);
        }
        ans.push_back(row);
    }

    return ans;
}