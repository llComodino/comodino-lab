#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct Node {
    int data;
    struct Node *left;
    struct Node *right;
} Node;

// Prototypes
Node *createNode(int data);
Node *insertNode(Node *root, int data);
void printTree(Node *root);
void printTreeInOrder(Node *root);
void printTreePreOrder(Node *root);
void printTreePostOrder(Node *root);
void printTreeLevelOrder(Node *root);
void printTreeLevel(Node *root, int level);
int findHeight(Node *root);
int findMax(Node *root);
int findMin(Node *root);
int findSize(Node *root);

int main() {
 
    Node *root = NULL;
    
    root = insertNode(root, 10);
    root = insertNode(root, 5);
    root = insertNode(root, 15);
    root = insertNode(root, 3);
    root = insertNode(root, 7);
    root = insertNode(root, 13);
    root = insertNode(root, 17);
    root = insertNode(root, 1);
    root = insertNode(root, 4);
    root = insertNode(root, 6);
    root = insertNode(root, 8);
    root = insertNode(root, 12);
    root = insertNode(root, 14);
    root = insertNode(root, 16);
    root = insertNode(root, 18);
    
    puts("Tree:");
    printTree(root);

    puts("\n\n");

    puts("Tree Traversals:");
    puts("In Order:");
    printTreeInOrder(root);
    printf("\n");

    puts("Pre Order:");
    printTreePreOrder(root);
    printf("\n");

    puts("Post Order:");
    printTreePostOrder(root);
    printf("\n");

    puts("Level Order:");
    printTreeLevelOrder(root);
    puts("\n");

    printf("Height: %d\n", findHeight(root));
    printf("Max: %d\n", findMax(root));
    printf("Min: %d\n", findMin(root));
    printf("Size: %d\n", findSize(root));
    
    puts("\n\n");

    return 0;
}

Node *createNode(int data) {
    Node *newNode = malloc(sizeof(Node));
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

Node *insertNode(Node *root, int data) {
    if (root == NULL) {
        return createNode(data);
    } else if (data < root->data) {
        root->left = insertNode(root->left, data);
    } else if (data > root->data) {
        root->right = insertNode(root->right, data);
    }
    return root;
}

void printTree(Node *root) {
    if (root == NULL) {
        return;
    }
    printTree(root->left);
    printf("%d ", root->data);
    printTree(root->right);
}

void printTreeInOrder(Node *root) {
    if (root == NULL) {
        return;
    }
    printf("%d ", root->data);
    printTreeInOrder(root->left);
    printTreeInOrder(root->right);
}

void printTreePreOrder(Node *root) {
    if (root == NULL) {
        return;
    }
    printTreePreOrder(root->left);
    printf("%d ", root->data);
    printTreePreOrder(root->right);
}

void printTreePostOrder(Node *root) {
    if (root == NULL) {
        return;
    }
    printTreePostOrder(root->left);
    printTreePostOrder(root->right);
    printf("%d ", root->data);
}

void printTreeLevelOrder(Node *root) {
    if (root == NULL) {
        return;
    }
    int height = findHeight(root);
    for (int i = 1; i <= height; i++) {
        printTreeLevel(root, i);
    }
}

void printTreeLevel(Node *root, int level) {
    if (root == NULL) {
        return;
    }
    if (level == 1) {
        printf("%d ", root->data);
    } else if (level > 1) {
        printTreeLevel(root->left, level - 1);
        printTreeLevel(root->right, level - 1);
    }
}

int findHeight(Node *root) {
    if (root == NULL) {
        return 0;
    }
    int leftHeight = findHeight(root->left);
    int rightHeight = findHeight(root->right);
    if (leftHeight > rightHeight) {
        return leftHeight + 1;
    } else {
        return rightHeight + 1;
    }
}

int findMax(Node *root) {
    if (root == NULL) {
        return -1;
    }
    int max = root->data;
    int leftMax = findMax(root->left);
    int rightMax = findMax(root->right);
    if (leftMax > max) {
        max = leftMax;
    }
    if (rightMax > max) {
        max = rightMax;
    }
    return max;
}

int findMin(Node *root) {
    if (root == NULL) {
        return -1;
    }
    int min = root->data;
    int leftMin = findMin(root->left);
    int rightMin = findMin(root->right);
    if (leftMin < min) {
        min = leftMin;
    }
    if (rightMin < min) {
        min = rightMin;
    }
    return min;
}

int findSize(Node *root) {
    if (root == NULL) {
        return 0;
    }
    return findSize(root->left) + findSize(root->right) + 1;
}
