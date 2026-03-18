ListNode* reverseKGroup(ListNode* head, int k) {
    ListNode *curr=head;
    for(int i=0;i<k;i++){
        if(!curr){
            return head;
        }
        curr=curr->next;
    }
    curr=head;
    ListNode *temp=NULL,*prev=NULL;
    for(int i=0;i<k;i++){
        temp=curr->next;
        curr->next=prev;
        prev=curr;
        curr=temp;
    }
    head->next=reverseKGroup(curr,k);
    return prev;
    }