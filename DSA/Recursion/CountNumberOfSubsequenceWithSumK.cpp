int countSubSequence(int ind,vector<int>& nums,int target){
        //base case
        if(target<0){      
            return 0;
        }
        if(target==0){
            return 1;
        }
        if(ind==nums.size()){
            return 0;
        }
        //take the element
        int take=countSubSequence(ind+1,nums,target-nums[ind]);

        //not take the element
        int notTake=countSubSequence(ind+1,nums,target);

        //return the count of subsequence
        return take+notTake;
    }
    
int numSubseq(vector<int>& nums, int target) {
    int ind=0;
    return countSubSequence(ind,nums,target);
}