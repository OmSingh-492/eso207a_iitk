#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>



//START OF QUESTION-1:-





/* Assuning the entries in the doubly-linked linear list 
are all distinct integers, between INT_MIN and INT_MAX. */

/* Implementing actual nodes of the linked list. */
struct node
{
    int entry;
    /* Set the default values of the pointers to NULL. */
    struct node *prev;
    struct node *next;
};

/* Insert operation after reading an item from the terminal. */
int insert(int data, struct node **start, struct node **end, int position)
{
    /* Varibale position is chosen as:
    -1: Addition at the end.
    0: Addition at the start. */

    /* Return value is chosen as:
    0: Successfully added.
    -1: Insufficient storage.
    1: Wrong value entered for position. */

    struct node *new_node = (struct node *) malloc(sizeof(struct node));
    
    /* If enough space isn't present. */
    if(new_node == NULL)
        return -1;
    
    new_node -> entry = data;
    new_node -> next = NULL;
    new_node -> prev = NULL;
    
    /* If no entries are originally present. */
    if(*start == NULL)
    {
        *start = new_node;
        *end = new_node;
        return 0;
    }
    /* To add an entry at the start. */
    if(position == 0)
    {
        (*start) -> prev = new_node;
        new_node -> next = *start;
        *start = new_node;
        return 0;
    }
    /* To add an entry at the end. */
    if(position == -1)
    {
        (*end) -> next = new_node;
        new_node -> prev = *end;
        *end = new_node;
        return 0;
    }
    /* To add an entry at arbitraty position. */
    struct node *temp = *start;
    for(int i = 0; i < position; i += 1)
    {
        if(temp -> next != NULL)
            temp = temp -> next;
        // The position entered does not exist.
        else 
            return 1;
    }
    temp -> prev -> next = new_node;
    new_node -> prev = temp -> prev;
    temp -> prev = new_node;
    new_node -> next = temp;
    return 0;
}

/* Delete operation after reading an item from the terminal. */
bool delete(int data, struct node **start, struct node **end)
{
    /* Return value is chosen as:
    true: Successfully deleted.
    false: No such item found. */

    /* If no elements are added. */
    if(*start == NULL)
        return false;
    
    /* Deleting the item if it is at the start. */
    if((*start) -> entry == data)
    {
        struct node *temp = *start;
        *start = temp -> next;
        (*start) -> prev = NULL;
        free(temp);
        return true;
    }

    /* Deleting the item if it is at the end. */
    if((*end) -> entry == data)
    {
        struct node *temp = *end;
        *end = temp -> prev;
        (*end) -> next = NULL;
        free(temp);
        return true;
    }

    /* Delete the item which is not the start or the end. */
    struct node *temp = *start;
    while(temp != NULL)
    {
        if(temp -> entry == data)
        {
            temp -> prev -> next = temp -> next;
            temp -> next -> prev = temp -> prev;
            free(temp); // Freeing the memory occupied by temp.
            return true;
        }
        temp = temp -> next;
    }
    // Item isn't present in the doubly-linked list.
    return false;
}

/* Print the items in order. */
void print(struct node **start)
{
    /* We created a temp varaible to keep start untouched. */
    struct node *temp = *start;
    printf("The contents of the doubly linked list are:");
    while(temp != NULL)
    {
        printf("%d ", temp -> entry);
        temp = temp -> next;
    }
    printf("\n");
}

/* Print the items in reverse order. */
void print_reverse(struct node **end)
{
    /* We created a temp varaible to keep end untouched. */
    struct node *temp = *end;
    printf("The contents of the doubly linked list in the reverse order are:");
    while(temp != NULL)
    {
        printf("%d ", temp -> entry);
        temp = temp -> prev;
    }
    printf("\n");
}





// START OF QUESTION-2:-






int main(void)
{
    struct node *start = NULL;
    struct node *end = NULL;
    printf("Instructions:\n1. Don't delete an item before inserting atleast one item.\n");
    printf("2. Don't access the elements without inserting atleast one item.\n");
    printf("3. Other errors if any shall be displayed later.\n\n");
    printf("Driver functions:\n");
    printf("1. Push an element into the stack.\n");
    printf("2. Enqueue an element into the queue.\n");
    printf("3. Insert an element at an arbitraty position in the linked list.\n");
    printf("4. Pop an element from the stack.\n");
    printf("5. Dequeue an element from the queue.\n");
    printf("6. Delete an abitrary element from the linked list.\n");
    printf("7. Print the elements in order (space-separated).\n");
    printf("8. Print the elements in reverse order (space-separated).\n");
    printf("9. Exit the program.\nEnter your input: ");
    int input;
    scanf("%d", &input);
    if(input == 9)
        return 0;
    while(input != 9)
    {
        if(input == 1)
        {
            printf("Enter the element to be pushed: ");
            int data;
            scanf("%d", &data);
            int status = insert(data, &start, &end, 0);
            if(status == 0)
                printf("Successfully added!\n");
            else
                printf("Insuffcient storage!\n");
        }
        else if(input == 2)
        {
            printf("Enter the element to be enqueued: ");
            int data;
            scanf("%d", &data);
            int status = insert(data, &start, &end, -1);
            if(status == 0)
                printf("Successfully added!\n");
            else
                printf("Insuffcient storage!\n");
        }
        else if(input == 3)
        {
            printf("Enter the element to be inserted: ");
            int data;
            scanf("%d", &data);
            printf("Enter the position (0-indexed) where it is to be inserted: ");
            int position;
            scanf("%d", &position);
            int status = insert(data, &start, &end, position);
            if(status == 0)
                printf("Successfully added!\n");
            else if(status == -1)
                printf("Insuffcient storage!\n");
            else
                printf("Incorrect position entered!\n");
        }
        else if(input == 4)
        {
            int data = start -> entry;
            bool val = delete(start -> entry, &start, &end);
            if(!val)
                printf("Item isn't present in the stack!\n");
            else
                printf("The element %d popped out successfully!\n", data);
        }
        else if(input == 5)
        {
            int data = start -> entry;
            bool val = delete(start -> entry, &start, &end);
            if(!val)
                printf("Item isn't present in the queue!\n");
            else
                printf("The element %d dequeued successfully!\n", data);
        }
        else if(input == 6)
        {
            int data;
            printf("Enter the item to be deleted\n");
            scanf("%d", &data);
            bool val = delete(data, &start, &end);
            if(!val)
                printf("Item not found in the doubly-linked list!\n");
            else   
                printf("Item deleted successfully!\n");
        }
        else if(input == 7)
        {
            print(&start);
        }
        else if(input == 8)
        {
            print_reverse(&end);
        }
        else
            printf("Wrong input entered");
        printf("Enter your next input as per the menu above: ");
        scanf("%d", &input);
    }
    return 0;
}