#include <stdio.h>
#include <stdlib.h>

struct TreeNode {
	int val;
	struct TreeNode* left;
	struct TreeNode* right;
};
struct TreeNode* createNode(int data) {
    struct TreeNode* newNode = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    newNode->val = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// Option 1: Insert Node (Duplicates allowed in the right subtree)
struct TreeNode* insertNode(struct TreeNode* root, int data) {
    if (root == NULL) {
        return createNode(data);
    }
    if (data < root->val) {
        root->left = insertNode(root->left, data);
    } else {
        // Data >= root->val goes to the right
        root->right = insertNode(root->right, data);
    }
    return root;
}

// Helper for traversals to avoid repeating "The tree is empty" check
void inorder(struct TreeNode* root) {
    if (root) {
        inorder(root->left);
        printf("%d ", root->val);
        inorder(root->right);
    }
}

void preorder(struct TreeNode* root) {
    if (root) {
        printf("%d ", root->val);
        preorder(root->left);
        preorder(root->right);
    }
}

void postorder(struct TreeNode* root) {
    if (root) {
        postorder(root->left);
        postorder(root->right);
        printf("%d ", root->val);
    }
}

// Option 2, 3, 4: Traversal Wrappers
void inorderTraversal(struct TreeNode* root) {
    if (root == NULL) printf("The tree is empty\n");
    else {
        inorder(root);
        printf("\n");
    }
}

void preorderTraversal(struct TreeNode* root) {
    if (root == NULL) printf("The tree is empty\n");
    else {
        preorder(root);
        printf("\n");
    }
}

void postorderTraversal(struct TreeNode* root) {
    if (root == NULL) printf("The tree is empty\n");
    else {
        postorder(root);
        printf("\n");
    }
}

// Option 5: Delete Node
struct TreeNode* deleteNode(struct TreeNode* root, int data, int* found) {
    if (root == NULL) return NULL;

    if (data < root->val) {
        root->left = deleteNode(root->left, data, found);
    } else if (data > root->val) {
        root->right = deleteNode(root->right, data, found);
    } else {
        // Node found
        *found = 1;
        if (root->left == NULL) {
            struct TreeNode* temp = root->right;
            free(root);
            return temp;
        } else if (root->right == NULL) {
            struct TreeNode* temp = root->left;
            free(root);
            return temp;
        }
        // Two children: Get inorder successor (smallest in right subtree)
        struct TreeNode* temp = root->right;
        while (temp && temp->left != NULL) temp = temp->left;
        
        root->val = temp->val;
        // Delete the inorder successor (passing a dummy flag)
        int dummy;
        root->right = deleteNode(root->right, temp->val, &dummy);
    }
    return root;
}

// Memory Cleanup
void freeTree(struct TreeNode* root) {
    if (root) {
        freeTree(root->left);
        freeTree(root->right);
        free(root);
    }
}
int main() {
    struct TreeNode* root = NULL;
    int choice, data;

    while (1) {
        printf("1. Insert Node\n");
        printf("2. In-Order Traversal\n");
        printf("3. Pre-Order Traversal\n");
        printf("4. Post-Order Traversal\n");
        printf("5. Delete Node\n");
        printf("6. Exit\n");
        printf("Choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Data: ");
                scanf("%d", &data);
                root = insertNode(root, data);
                break;
            case 2:
                inorderTraversal(root);
                break;
            case 3:
                preorderTraversal(root);
                break;
            case 4:
                postorderTraversal(root);
                break;
            case 5: {
                printf("Delete: ");
                scanf("%d", &data);
                int found = 0;
                root = deleteNode(root, data, &found);
                if (!found) {
                    printf("Value not found\n");
                }
                break;
            }
            case 6:
                freeTree(root);
                exit(0);
            default:
                printf("Invalid choice\n");
        }
    }

    return 0;
}
