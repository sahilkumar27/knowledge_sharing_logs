ListNode *reverseNode(ListNode *currHead)
{
    ListNode *curr = currHead, *temp = currHead, *prev = NULL;
    while (curr)
    {
        temp = curr->next;
        curr->next = prev;
        prev = curr;
        curr = temp;
    }
    return prev;
}
bool isPalindrome(ListNode *head)
{
    if (!head || !head->next)
    {
        return true;
    }

    ListNode *slow = head, *fast = head, *prev = NULL, *first = NULL, *second = NULL;
    while (fast != NULL && fast->next != NULL)
    {
        prev = slow;
        slow = slow->next;
        fast = fast->next->next;
    }
    first = head;
    // in case of even length linked list, fast will be null
    if (fast == NULL)
    {
        second = slow;
        cout << second->val << endl;
    }
    // in case of odd length linked list, fast->next will be null
    else
    {
        second = slow->next;
    }
    prev->next = NULL;
    ListNode *revHead = reverseNode(second);
    while (revHead != NULL)
    {
        if (revHead->val != first->val)
        {
            return false;
        }
        revHead = revHead->next;
        first = first->next;
    }
    return true;
}