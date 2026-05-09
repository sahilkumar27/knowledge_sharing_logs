vector<int> nextGreaterElement(vector<int>& nums1, vector<int>& nums2) {
    unordered_map<int,int> mp;
    vector<int> res;
    stack<int> st;
    for(int i=nums2.size()-1;i>=0;i--){
        while(!st.empty() && nums2[i]>=st.top()){
            st.pop();
        }

        mp[nums2[i]]=!st.empty()?st.top():-1;
        st.push(nums2[i]);
    }
    
    for(auto num: nums1){
        res.push_back(mp[num]);
    }

    return res;
}