#include <stdio.h>
#include <stdlib.h>

struct node
{
    int key;
    struct node *left;
    struct node *right;
};

struct node *createNode(int value)
{
    struct node *temp = (struct node *)malloc(sizeof(struct node));
    temp -> key = value;
    temp -> left = NULL;
    temp -> right = NULL;
    return temp;
}

// Function for in order traversal of the Binary Search Tree.
void inOrder(struct node *root)
{
    if(root != NULL)
    {
        inOrder(root -> left);
        printf("%d\n", root -> key);
        inOrder(root -> right);
    }
}

// Function to insert a new node in the Binary Search Tree. We don't use root straightaway to implement a recursive function.
struct node *insert(struct node *node, int value)
{
    // Base Case
    if(node == NULL)
        return createNode(value);
    // Recursive step
    if(value < node -> key)
        node -> left = insert(node -> left, value);
    else if(value > node -> key)
        node -> right = insert(node -> right, value);
    
    // Return statement
    return node;
}

struct node *findMin(struct node *node)
{
    struct node *current = node;
    while(current != NULL && current -> left != NULL)
        current = current -> left;
    return current;
}

struct node *delete(struct node *root, int value)
{
    // Base case
    if(root == NULL)
        return root;
    // Recursive Part
    if(value < root -> key)
        root -> left = delete(root -> left, value);
    else if(value > root -> key)
        root -> right = delete(root -> right, value);
    else
    {
        if(root -> left == NULL)
        {
            struct node *temp = root -> right;
            free(root);
            return temp;
        }
        else if(root -> right == NULL)
        {
            struct node *temp = root -> left;
            free(root);
            return temp;
        }
        struct node *temp = findMin(root -> right);
        root -> key = temp -> key;
        root -> right = delete(root -> right, temp -> key);
    }
    
    // Return statement
    return root;
}

// search returns 0 if the value is found, else 1.
int search(struct node *root, int value)
{
    // Base case
    if(root == NULL)
        return 1;
    
    // Recursive Part
    if(value < root -> key)
        search(root -> left, value);
    else if(value > root -> key)
        search(root -> right, value);
    else
        return 0;
}

int main(void)
{
    int number;
    printf("Enter the number of numbers to be inserted: ");
    scanf("%d", &number);
    struct node *root = NULL;
    for(int i = 0; i < number; i += 1)
        root = insert(root, rand());
    printf("Insertion Successful! Now, traversing the tree in order:\n");
    inOrder(root);
    printf("Enter the number of times the minimum item has to be deleted: ");
    scanf("%d", &number);
    for(int i = 0; i < number; i += 1)
    {
        struct node *minimum = findMin(root);
        printf("The item being deleted: %d\n", minimum -> key);
        root = delete(root, minimum -> key);
    }
    printf("After deletion, an in order traversal gives:\n");
    inOrder(root);
    return 0;
}