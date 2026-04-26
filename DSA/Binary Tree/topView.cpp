vector<int> topView(Node *root) {
        // code here
         if(!root) return {};
        vector<int> ans;
        int minHD=0,maxHD=0;
        queue<pair<Node*,int>> bfs;
        unordered_map<int,int> mp;
        bfs.push({root,0});
        
        while(!bfs.empty()){
            int n=bfs.size();
            
            for(int i=0;i<n;i++){
                Node *node=bfs.front().first;
                int dist=bfs.front().second;
                minHD=min(minHD,dist);
                maxHD=max(maxHD,dist);
                if(mp.find(dist)==mp.end()){
                 mp[dist]=node->data;   
                }
                bfs.pop();
                if(node->left) bfs.push({node->left,dist-1});
                if(node->right) bfs.push({node->right,dist+1});
            }
        }
        
        for(int i=minHD;i<=maxHD;i++){
            ans.push_back(mp[i]);
        }
        
        return ans;
        
    }