ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
    if(!l1){
        return l2;
    }
    if(!l2){
        return l1;
    }
    ListNode* dummyNode=new ListNode(0);
    ListNode* temp= dummyNode;
    int carry=0;
    while(l1 || l2 || carry){
        int sum=carry;
        if(l1){
            sum+=l1->val;
            l1=l1->next;
        }
        if(l2){
            sum+=l2->val;
            l2=l2->next;
        }
        carry=sum/10;
        sum%=10;
        ListNode *newNode=new ListNode(sum);
        temp->next=newNode;
        temp=newNode;
    }
    return dummyNode->next;
}