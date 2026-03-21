ListNode *detectCycle(ListNode *head)
{
    if (head == NULL)
    {
        return NULL;
    }
    ListNode *slow = head, *fast = head;
    while (fast != NULL && fast->next != NULL)
    {
        slow = slow->next;
        fast = fast->next->next;
        // in case it detects a loop we need to break out of this loop, otherwise it will give TLE
        if (slow == fast)
        {
            break;
        }
    }
    if (fast == NULL || fast->next == NULL)
    {
        return NULL;
    }

    slow = head;
    while (slow != fast)
    {
        slow = slow->next;
        fast = fast->next;
    }
    return slow;
}