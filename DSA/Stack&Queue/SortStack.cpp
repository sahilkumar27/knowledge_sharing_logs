void insert(stack<int> &st,int temp){
    if(st.empty() || st.top()<=temp){
        st.push(temp);
        return;
    }
    int element=st.top();
    st.pop();
    insert(st,temp);
    st.push(element);
}
void sortStack(stack<int> &st) {
    // code here
    if(st.empty()) return;
    
    int top=st.top();
    st.pop();
    sortStack(st);
    insert(st,top);
}