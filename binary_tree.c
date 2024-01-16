#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// initializes data type of tree node
typedef struct TreeNode {
    int data;
    struct TreeNode *left;
    struct TreeNode *right;
} TreeNode;

// helper function prototypes
TreeNode *createNode(int data);
TreeNode *insert(TreeNode *root, int data);
void freeTree(TreeNode *root);

// create tree node
TreeNode *createNode(int data) {
    TreeNode *newNode = malloc(sizeof(TreeNode)); // allocates memory for the node

    // checks to make sure node allocation did not fail
    if (newNode == NULL) {
        printf("Error allocating memory.\n");
        exit(EXIT_FAILURE);
    }

    // initializes node, left and right does not point to anything yet
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;

    return newNode;
}

// inserts node into the tree, in a sorted order
TreeNode *insert(TreeNode *root, int data) {
    // if the tree does not exist yet, just create a node to start the tree
    if (root == NULL) {
        return createNode(data);
    }

    // recursively insert into left or right subtree
    if (data <= root->data) {
        root->left = insert(root->left, data);
    } else if (data > root->data) {
        root->right = insert(root->right, data);
    }

    // return root; required due to recursively calling and assigning this function's output to nodes, as shown above   
    return root;
}

void preorder(TreeNode *root) {
    // check if node is null, if so, basically exit out of the current recursion
    if (root == NULL)
    {
        return;
    }

    // if node is not null:
    printf("%i", root->data);
    preorder(root->left);
    preorder(root->right);
    
}

void postorder(TreeNode *root) {
    // check if node is null, if so, basically exit out of the current recursion
    if (root == NULL)
    {
        return;
    }

    // if node is not null:
    postorder(root->left);
    postorder(root->right);
    printf("%i", root->data);
    
}

void inorder(TreeNode *root) {
    // check if node is null, if so, basically exit out of the current recursion
    if (root == NULL)
    {
        return;
    }

    // if node is not null:
    inorder(root->left);
    printf("%i", root->data);
    inorder(root->right);
    
}

void freeTree(TreeNode *root) {
    // while the current node is not empty
    if (root != NULL) {
        freeTree(root->left);
        freeTree(root->right);
        free(root);
    }
}

int main(void) {
    TreeNode *root = NULL;

    root = insert(root, 5);
    insert(root, 3);
    insert(root, 8);
    insert(root, 7);
    insert(root, 4);
    insert(root, 2);
    insert(root, 6);
    insert(root, 9);
    insert(root, 1);
    
    preorder(root);
    printf("\n");
    postorder(root);
    printf("\n");
    inorder(root);
    printf("\n");
    return 0;
}