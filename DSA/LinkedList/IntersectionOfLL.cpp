int lengthofLL(ListNode *head){
    int count=0;
    while(head){
        head=head->next;
        count++;
    }
    return count;
}

ListNode* getIntersection(ListNode* headA, ListNode* headB) {
    if(!headA || !headB) return NULL;
    int lenA=lengthofLL(headA);
    int lenB=lengthofLL(headB);
    ListNode* tempA=NULL,*tempB=NULL;
    if(lenA>lenB){
        tempA=headA;
        tempB=headB;
    }else{
        tempA=headB;
        tempB=headA;
    }
    int diff=abs(lenA-lenB);
    while(diff--){
        tempA=tempA->next;
    }

    while(tempA && tempB){
        if(tempA==tempB){
            return tempA;
        }
        tempA=tempA->next;
        tempB=tempB->next;
    }
    return NULL;
}