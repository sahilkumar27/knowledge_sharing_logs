vector<vector<int>> verticalTraversal(TreeNode* root) {
       vector<vector<int>> ans;
       map<int,map<int,multiset<int>>> mp;
       queue<pair<TreeNode*,pair<int,int>>> bfs;
       bfs.push({root,{0,0}});
       while(!bfs.empty()){
        TreeNode *node=bfs.front().first;
        int hd=bfs.front().second.first;
        int level=bfs.front().second.second;
        bfs.pop();
        mp[hd][level].insert(node->val);
        if(node->left) bfs.push({node->left,{hd-1,level+1}});
        if(node->right) bfs.push({node->right,{hd+1,level+1}}); 
       }

       for(auto p:mp){
           vector<int> col;
           for(auto q:p.second){
            col.insert(col.end(),q.second.begin(),q.second.end());
           }
           ans.push_back(col);
       }

       return ans;
    }