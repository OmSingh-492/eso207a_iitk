#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

void swap(int *arr, int i, int j)
{
    int temp = *(arr + i);
    *(arr + i) = *(arr + j);
    *(arr + j) = temp;
}

void sink(int *arr, int len, int index, int r)
{
    int *child = (int *)malloc((r + 1) * sizeof(int));
    while(true)
    {
        for(int i = 1; i <= r; i += 1)
        {
            if((r * index + i) < len)
                *(child + i) = r * index + i;
            else
                *(child + i) = -1;
        }
        int min_child = INT_MAX, min_child_index;
        for(int i = 1; i <= r; i += 1)
        {
            if(*(child + i) != -1 && *(arr + (*(child + i))) < min_child)
            {
                min_child_index = *(child + i);
                min_child = *(arr + *(child + i));
            }
        }
        if(min_child == INT_MAX)
            break;
        if(*(arr + index) > *(arr + min_child_index))
            swap(arr, index, min_child_index);
        index = min_child_index;
    }
    free(child);
}

void heapifyUp(int *arr, int index, int r)
{
    int parent = (index - 1) / r;
    while(parent > 0)
    {
        if(*(arr + index) < *(arr + parent))
        {
            swap(arr, index, parent);
            index = parent;
            parent = (index - 1) / r;
        }
        else
            break;
    }
}

void buildHeap(int *arr, int n, int r)
{
    for(int i = (n - 1) / r; i > 0; i -= 1)
        sink(arr, n, i, r);
}

void insert(int *arr, int *n, int r, int element)
{
    *(arr + *n) = element;
    *n = *n + 1;
    heapifyUp(arr, *n - 1, r);
}

int extractMin(int *arr, int *n, int r)
{
    int min = *(arr + 0);
    *(arr + 0) = *(arr + *n - 1);
    *n = *n - 1;
    sink(arr, *n, 0, r);
    return min;
}

void printArray(int *arr, int *n)
{
    printf("The contents of the array are:\n");
    for(int i = 0; i < *n; i += 1)
        printf("%d\n", *(arr + i));
}

int main(void)
{
    int r, capacity, n = 0;
    printf("Enter the value of parameter r and the maximum capacity of the heap: ");
    scanf("%d%d", &r, &capacity);
    int *arr = (int *)malloc(capacity * sizeof(int));
    for(int i = 0; i < capacity; i += 1)
    {
        int number = rand();
        insert(arr, &n, r, number);
    }
    printArray(arr, &n);
    buildHeap(arr, n, r);
    int number;
    printf("Enter the number of numbers to be deleted: ");
    scanf("%d", &number);
    for(int i = 0; i < number; i += 1)
    {
        int min = extractMin(arr, &n, r);
        printf("The deleted item is: %d\n", min);
    }
    printArray(arr, &n);
    return 0;
}