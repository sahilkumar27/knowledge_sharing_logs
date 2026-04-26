bool isLeaf(Node *root){
    if(root->left==NULL && root->right==NULL){
        return true;
    }
    
    return false;
}

void leftBoundary(Node *root,vector<int> &ans){
    if(!root) return;
    
    while(!isLeaf(root)){
        ans.push_back(root->data);
        if(root->left) root=root->left;
        else if(root->right) root=root->right;
    }
    
}

void rightBoundary(Node *root,vector<int> &ans){
    if(!root) return;
    vector<int> temp;
    
    while(!isLeaf(root)){
        temp.push_back(root->data);
        if(root->right) root=root->right;
        else if(root->left) root=root->left;
    }
    
    int n=temp.size()-1;
    for(int i=n;i>=0;i--){
        ans.push_back(temp[i]);
    }
}

void collectLeaf(Node *root,vector<int> &ans){
    if(!root) return;
    
    if(isLeaf(root)) ans.push_back(root->data);
    
    collectLeaf(root->left,ans);
    collectLeaf(root->right,ans);
}

vector<int> boundaryTraversal(Node *root) {
    // code here
    vector<int> ans;
    if(!root) return ans;
    
    if(!isLeaf(root)) ans.push_back(root->data);
    
    leftBoundary(root->left,ans);
    
    collectLeaf(root,ans);
    
    rightBoundary(root->right,ans);
    
    return ans;
}