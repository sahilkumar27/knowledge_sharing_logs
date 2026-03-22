int merge(vector<int> &arr,int low,int high,int mid){
    int left=low,right=mid+1,count=0;
    vector<int> temp;
    while(left<=mid && right<=high){
        if(arr[left]<=arr[right]){
            temp.push_back(arr[left]);
            left++;
        }else {
            count+=mid-left+1;
            temp.push_back(arr[right]);
            right++;
        }
    }
    
    while(left<=mid){
        temp.push_back(arr[left]);
        left++;
    }
    
    while(right<=high){
        temp.push_back(arr[right]);
        right++;
    }
    
    //copying back to original array
    for(int i=low;i<=high;i++){
        arr[i]=temp[i-low];
    }
    return count;
}
    
int countInversion(vector<int> &arr,int low,int high){
    //base case
    if(low>=high){
        return 0;
    }
    int count=0,mid=low+(high-low)/2;
    count+=countInversion(arr,low,mid);
    count+=countInversion(arr,mid+1,high);
    count+=merge(arr,low,high,mid);
    return count;
}
    
int inversionCount(vector<int> &arr) {
    // Code Here
    return countInversion(arr,0,arr.size()-1);
}