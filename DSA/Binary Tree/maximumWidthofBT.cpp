int widthOfBinaryTree(TreeNode* root) {
    queue<pair<TreeNode*,long>> bfs;
    long ans=0;
    bfs.push({root,0});
    while(!bfs.empty()){
        long min=bfs.front().second;
        int size=bfs.size();
        long first=0,last=0;

        for(int i=0;i<size;i++){
        long currId=bfs.front().second-min;
        if(i==0) first=currId;
        if(i==size-1) last=currId;
        TreeNode* node=bfs.front().first;
        bfs.pop();
        if(node->left) bfs.push({node->left,2*currId+1});
        if(node->right) bfs.push({node->right,2*currId+2});
        }
    
        ans=max(ans,last-first+1);
    }
    return ans;
}