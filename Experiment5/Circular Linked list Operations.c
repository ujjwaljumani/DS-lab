#include <stdio.h>
#include <stdlib.h>

struct node {
    int data;
    struct node *next;
};

typedef struct node *NODE;

// Create a new node with given data
NODE createNodeInCLL(int data) {
    NODE temp = (NODE) malloc(sizeof(struct node));
    temp->data = data;
    temp->next = NULL;
    return temp;
}

// Create CLL with n nodes
NODE createCLL(int n) {
	NODE head = NULL, tail = NULL;
    int val;
    for (int i = 0; i < n; i++) {
        scanf("%d", &val);
        NODE newNode = createNodeInCLL(val);
        if (head == NULL) {
            head = newNode;
            newNode->next = head;
            tail = newNode;
        } else {
            tail->next = newNode;
            newNode->next = head;
            tail = newNode;
        }
    }
    return head;
}

// Traverse CLL
void traverseListInCLL(NODE head) {
if (head == NULL) return;
    NODE temp = head;
    do {
        printf("%d -> ", temp->data);
        temp = temp->next;
    } while (temp != head);
    printf("\n");
}

// Insert at given position in CLL
NODE insertAtPositionInCLL(NODE head, int pos, int data) {
	int n = 0;
    if (head != NULL) {
        NODE temp = head;
        do { n++; temp = temp->next; } while (temp != head);
    }

    if (pos < 1 || pos > n + 1) {
        printf("Position not found\n");
        return head;
    }

    NODE newNode = createNodeInCLL(data);
    if (head == NULL) {
        newNode->next = newNode;
        return newNode;
    }

    if (pos == 1) {
        NODE tail = head;
        while (tail->next != head) tail = tail->next;
        newNode->next = head;
        tail->next = newNode;
        return newNode; // New head
    } else {
        NODE temp = head;
        for (int i = 1; i < pos - 1; i++) temp = temp->next;
        newNode->next = temp->next;
        temp->next = newNode;
        return head;
	}
}

// Delete node at given position in CLL
NODE deleteAtPositionInCLL(NODE head, int pos) {
	 int n = 0;
    NODE temp = head;
    do { n++; temp = temp->next; } while (temp != head);

    if (pos < 1 || pos > n) {
        printf("Position not found\n");
        return head;
    }

    temp = head;
    if (pos == 1) {
        printf("Deleted element: %d\n", head->data);
        if (head->next == head) {
            free(head);
            return NULL;
        }
        NODE tail = head;
        while (tail->next != head) tail = tail->next;
        head = head->next;
        tail->next = head;
        free(temp);
        return head;
    } else {
        NODE prev = NULL;
        for (int i = 1; i < pos; i++) {
            prev = temp;
            temp = temp->next;
        }
        prev->next = temp->next;
        printf("Deleted element: %d\n", temp->data);
        free(temp);
        return head;
    }
}

// Reverse CLL
NODE reverseCLL(NODE head) {
	 if (head == NULL || head->next == head) return head;

    NODE prev = NULL, current = head, nextNode;
    NODE tail = head;
    while (tail->next != head) tail = tail->next;

    do {
        nextNode = current->next;
        current->next = prev;
        prev = current;
        current = nextNode;
    } while (current != head);

    // Re-link the circularity: old head points to new head (prev)
    head->next = prev;
    return prev; // Return the new head
}

// Concatenate two CLLs
NODE concatCLL(NODE first, NODE second) {
 if (first == NULL) return second;
    if (second == NULL) return first;

    NODE tail1 = first;
    while (tail1->next != first) tail1 = tail1->next;

    NODE tail2 = second;
    while (tail2->next != second) tail2 = tail2->next;

    tail1->next = second;
    tail2->next = first;

    return first;
}

int main() {
    NODE first = NULL, second = NULL;
    int x, pos, op, n;

    while (1) {
        printf("1.Create 2.Insert 3.Delete 4.Display 5.Reverse 6.Concat 7.Exit\n");
        printf("choice: ");
        scanf("%d", &op);
        switch (op) {
            case 1:
                printf("How many nodes? ");
                scanf("%d", &n);
                first = createCLL(n);
                break;
            case 2:
                printf("Position: ");
                scanf("%d", &pos);
                if (pos <= 0) {
                    printf("Position not found\n");
                } else {
                    printf("Element: ");
                    scanf("%d", &x);
                    first = insertAtPositionInCLL(first, pos, x);
                }
                break;
            case 3:
                if (first == NULL) {
                    printf("CLL is empty\n");
                } else {
                    printf("Position: ");
                    scanf("%d", &pos);
                    first = deleteAtPositionInCLL(first, pos);
                }
                break;
            case 4:
                if (first == NULL) {
                    printf("CLL is empty\n");
                } else {
                    printf("Elements in CLL are: ");
                    traverseListInCLL(first);
                }
                break;
            case 5:
                if (first == NULL) {
                    printf("CLL is empty\n");
                } else {
                    first = reverseCLL(first);
                    printf("CLL reversed\n");
                    traverseListInCLL(first);   // <-- display reversed list
                }
                break;
            case 6:
                printf("Creating second CLL to concatenate...\n");
                printf("How many nodes in second CLL? ");
                scanf("%d", &n);
                second = createCLL(n);
                first = concatCLL(first, second);
                printf("Concatenated CLL:\n");
                traverseListInCLL(first);
                break;
            case 7:
                exit(0);
        }
    }
}
