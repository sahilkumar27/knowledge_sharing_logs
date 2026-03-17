void deleteNode(Node* del_node) {
        // code here
        Node *prev=NULL;
        while(del_node->next!=NULL){
            prev=del_node;
            del_node->data=del_node->next->data;
            del_node=del_node->next;
        }
        prev->next=NULL;
        delete(del_node);
}