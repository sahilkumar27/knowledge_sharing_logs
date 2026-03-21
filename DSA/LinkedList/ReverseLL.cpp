// Iterative approach: Time complexity=O(n), Space complexity=O(1)
ListNode *reverseList(ListNode *head)
{
    ListNode *curr = head, *temp = curr, *prev = NULL;
    while (curr)
    {
        temp = curr->next;
        curr->next = prev;
        prev = curr;
        curr = temp;
    }
    return prev;
}

// Recursive approach: Time complexity=O(n), Space complexity=O(n)
ListNode *reverseList(ListNode *head)
{
    if (head == NULL || head->next == NULL)
    {
        return head;
    }
    ListNode *revHead = reverseList(head->next);
    head->next->next = head;
    head->next = NULL;
    return revHead;
}