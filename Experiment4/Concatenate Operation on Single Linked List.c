struct node {
    int data;
    struct node* next;
};

typedef struct node* NODE;

NODE createNode(int x) {
        NODE newNode = (NODE)malloc(sizeof(struct node));
    if (newNode == NULL) {
        printf("Memory allocation failed\n");
        exit(1);
    }
    newNode->data = x;
    newNode->next = NULL;
    return newNode;
}

NODE addNode(NODE first, int x) {
    NODE newNode = createNode(x);
    
    // If the list is empty, the new node becomes the head
    if (first == NULL) {
        return newNode;
    }
    
    // Traverse to the last node
    NODE temp = first;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    
    // Link the last node's next to the new node
    temp->next = newNode;
    return first;
}

NODE concatenate(NODE t1, NODE t2) {
     if (t1 == NULL) {
        return t2;
	 }
    // If second list is empty, return the first list
    if (t2 == NULL) {
        return t1;
    }
    
    // Traverse to the end of the first list
    NODE temp = t1;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    
    // Point the last node of t1 to the head of t2
    temp->next = t2;
    
    return t1;
}

void displayList(NODE first) {
    NODE temp = first;
    
    // Traverse the list until the end
    while (temp != NULL) {
        printf("%d --> ", temp->data);
        temp = temp->next;
    }
    
    // Final pointer in the list
    printf("NULL\n");
}
