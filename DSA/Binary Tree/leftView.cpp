vector<int> leftSideView(TreeNode* root) {
        if(!root) return {};

        queue<TreeNode*> bfs;
        vector<int> ans;
        bfs.push(root);
        while(!bfs.empty()){
            int n=bfs.size();
            for(int i=0;i<n;i++){
                TreeNode* node=bfs.front();
                bfs.pop();
                if(node->left) bfs.push(node->left);
                if(node->right) bfs.push(node->right);
                if(i==0) ans.push_back(node->val);
            }
        }
        
        return ans;
    }