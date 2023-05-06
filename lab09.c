#include <stdio.h>
#include <stdlib.h>

struct node
{
    int key;
    struct node *left;
    struct node *right;
    struct node *parent;
    int rank;
};

struct node *createNode(int value)
{
    struct node *temp = (struct node *)malloc(sizeof(struct node));
    temp -> key = value;
    temp -> left = NULL;
    temp -> right = NULL;
    temp -> parent = NULL;
    temp -> rank = 1;
    return temp;
}

// Trinode Operation
void trinodeOperation(struct node *newNode)
{
    struct node *p = newNode -> parent;
    struct node *g = p -> parent;
    if(newNode == p -> right && p == g -> left)
    {
        g -> right = newNode;
        newNode -> parent = g;
        p -> right = NULL;
        int temp = newNode -> key;
        newNode -> key = g -> key;
        g -> key = temp;
    }
    else if(newNode == p -> right && p == g -> right)
    {
        g -> left = p;
        (g -> left) -> parent = g;
        g -> left -> right = NULL;
        g -> right = newNode;
        newNode -> parent = g;
        int temp = g -> key;
        g -> key = (g -> left) -> key;
        (g -> left) -> key = temp;
    }
    else if(newNode == p -> left && p == g -> left)
    {
        p -> right = g;
        g -> parent = p;
        g = p;
    }
    else
    {
        p -> left = NULL;
        g -> left = newNode;
        newNode -> parent = g;
        int temp = (g -> left) -> key;
        (g -> left) -> key = g -> key;
        g -> key = temp;
    }
}

// Function for in order traversal of the Binary Search Tree.
// Recursion is being used as an exception here to print the BST.
void inOrder(struct node *root)
{
    if(root != NULL)
    {
        inOrder(root -> left);
        printf("%d\n", root -> key);
        inOrder(root -> right);
    }
}

// Search routine, to return the failure node corresponding to the inserted item.
struct node *search(struct node *root, int value)
{
    struct node *prev = root;
    while(root != NULL)
    {
        if(value > root -> key)
        {
            prev = root;
            root = root -> right;
        }
        else if(value < root -> key)
        {
            prev = root;
            root = root -> left;
        }
        else
            return NULL;
    }
    return prev;
}

// Function to insert a new node in the Binary Search Tree. We don't use root straightaway to implement a recursive function.
struct node *insert(struct node *root, int value)
{
    struct node *position = search(root, value);
    struct node *newNode = createNode(value);
    if(position != NULL)
    {
        newNode -> parent = position;
        if(value > position -> key)
            position -> right = newNode;
        else
            position -> left = newNode;
    }
    else if(position == NULL)
        return newNode;
    if(position -> parent != NULL)
    {
        struct node *p = newNode -> parent;
        struct node *g = p -> parent;
        if(newNode -> rank == p -> rank && p -> rank == g -> rank)
        {
            if(g -> key >= p -> key && g -> right != NULL && (g -> right) -> rank == g -> rank)
                g -> rank += 1;
            else if(g -> key <= p -> key && g -> left != NULL &&(g -> left) -> rank == g -> rank)
                g -> rank += 1;
            else if(g -> key >= p -> key && g -> right != NULL && (g -> right) -> rank == g -> rank - 1)
                trinodeOperation(newNode);
            else if(g -> key <= p -> key && g -> left != NULL &&(g -> left) -> rank == g -> rank - 1)
                trinodeOperation(newNode);
            else
                newNode -> rank += 1;
        }
        return root;
    }
    return root;
}

struct node *findMin(struct node *root)
{
    struct node *current = root;
    while(current != NULL && current -> left != NULL)
        current = current -> left;
    return current;
}

struct node *delete(struct node *root, int value)
{
    struct node* curr = root;
    struct node* prev = NULL;
    while(curr != NULL && curr -> key != value)
    {
        prev = curr;
        if (value < curr -> key)
            curr = curr -> left;
        else
            curr = curr -> right;
    }
    if (curr == NULL) 
        return root;
    if (curr -> left == NULL || curr -> right == NULL)
    {
        struct node* newCurr;
        if (curr -> left == NULL)
            newCurr = curr -> right;
        else
            newCurr = curr -> left;
        if (prev == NULL)
            return newCurr;
        if (curr == prev -> left)
            prev -> left = newCurr;
        else
            prev -> right = newCurr;
        free(curr);
    }
    else 
    {
        struct node* p = NULL;
        struct node* temp;
        temp = curr -> right;
        while (temp -> left != NULL) 
        {
            p = temp;
            temp = temp -> left;
        }
        if (p != NULL)
            p -> left = temp -> right;
        else
            curr -> right = temp -> right;
        curr -> key = temp -> key;
        free(temp);
    }
    return root;
}

int main(void)
{
    int number;
    printf("Enter the number of numbers to be inserted: ");
    scanf("%d", &number);
    struct node *root = createNode(rand());
    for(int i = 0; i < number - 1; i += 1)
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