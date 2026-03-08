void storePath(int row,int col,string path,vector<vector<int>> &maze,vector<vector<int>> &visited,vector<string> &ans,int n){
        //base case
        if(row<0||col<0||row>=n ||col>=n){
            return;
        }
        if(maze[row][col]==0 || visited[row][col]){
            return;
        }
        if(row==n-1 && col==n-1){
            ans.push_back(path);
            return;
        }
        
        //recursion call
        
        visited[row][col]=1;
        //moving in right direction
        storePath(row,col+1,path+'R',maze,visited,ans,n);
        //moving in left direction
        storePath(row,col-1,path+'L',maze,visited,ans,n);
        //moving in up direction
        storePath(row-1,col,path+'U',maze,visited,ans,n);
        //moving in down direction
        storePath(row+1,col,path+'D',maze,visited,ans,n);
        
        visited[row][col]=0;
        
    }
    vector<string> ratInMaze(vector<vector<int>>& maze) {
        // code here
        int n=maze.size();
        vector<vector<int>> visited(n,vector<int>(n,0));
        vector<string> ans;
        string path="";
        storePath(0,0,path,maze,visited,ans,n);
        return ans;
    }
    //Time complexity: O(4^n^2)
    //Space complexuty: O(n^2)