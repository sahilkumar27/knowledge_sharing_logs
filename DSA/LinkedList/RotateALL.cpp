int lengthOfLL(ListNode *curr)
{
    int count = 0;
    while (curr)
    {
        count++;
        curr = curr->next;
    }
    return count;
}
ListNode *rotateRight(ListNode *head, int k)
{
    if (!head || !head->next)
    {
        return head;
    }
    int length = lengthOfLL(head);
    k = k % length;
    if (k == 0)
    {
        return head;
    }
    k = length - k;
    ListNode *prev = NULL, *temp = head, *ans = NULL;
    while (k--)
    {
        prev = temp;
        temp = temp->next;
    }
    prev->next = NULL;
    ans = temp;
    while (temp->next != NULL)
    {
        temp = temp->next;
    }
    temp->next = head;
    return ans;
}