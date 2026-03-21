Node* removeNthFromEnd(Node* head, int N) {

    // calculate length of linked list
    int length = 0;
    Node* curr = head;

    while (curr != nullptr) {
        length++;
        curr = curr->next;
    }

    // find position from start
    int target = length - N + 1;

    // if head needs to be removed
    if (target == 1) {
        Node* newHead = head->next;
        delete head;
        return newHead;
    }

    // move to node before target
    curr = head;
    for (int i = 1; i < target - 1; i++) {
        curr = curr->next;
    }

    // delete target node
    Node* nodeToDelete = curr->next;
    curr->next = curr->next->next;
    delete nodeToDelete;

    return head;
}

// TC: O(L) where L is the length of the linked list.
// SC: O(1) as we are using only constant extra space.