#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

int min(int x, int y)
{
    if(x < y)
        return x;
    else
        return y;
}

void generate_random(int N)
{
    FILE *fp = fopen("random.txt", "w");
    for(int i = 0; i < N; i += 1)
        fprintf(fp, "%d\n", rand());
    fclose(fp);
    printf("Random numbers generates successfully!\n");
}

int *generate_arr(int N)
{
    int *a = (int *)malloc(N * sizeof(int));
    FILE *fp = fopen("random.txt", "r");
    for(int i = 0; i < N; i += 1)
        fscanf(fp, "%d", (a + i));
    fclose(fp);
    printf("Array generated successfully!\n");
    return a;
}

void generate_sorted(int *a, int N)
{
    FILE *fp = fopen("sorted.txt", "w");
    for(int i = 0; i < N; i += 1)
        fprintf(fp, "%d\n", *(a + i));
    printf("File sorted.txt generated successfully!\n");
    fclose(fp);
    free(a);
}

void merge(int *a, int l, int m, int r)
{
    int n1 = m - l + 1;
    int n2 = r - m;
    int *L = (int *)malloc(n1 * sizeof(int));
    int *R = (int *)malloc(n2 * sizeof(int));
    for(int i = 0; i < n1; i += 1)
        *(L + i) = *(a + l + i);
    for(int j = 0; j < n2; j += 1)
        *(R + j) = *(a + m + 1 + j);
    int i = 0, j = 0, k = l;
    while(i < n1 && j < n2)
    {
        if(*(L + i) <= *(R + j))
        {
            *(a + k) = *(L + i);
            i += 1;
        }
        else
        {
            *(a + k) = *(R + j);
            j += 1;
        }
        k += 1;
    }
    while(i < n1)
    {
        *(a + k) = *(L + i);
        i = i + 1;
        k = k + 1;
    }
    while(j < n2)
    {
        *(a + k) = *(R + j);
        j = j + 1; 
        k = k + 1;
    }
    free(L);
    free(R);
}

void merge_sort(int *a, int l, int r)
{
    if(l < r)
    {
        int m = l + (r - l) / 2;
        merge_sort(a, l, m);
        merge_sort(a, m + 1, r);
        merge(a, l, m, r);
    }
}

void merge_sort_iterative(int *a, int N)
{
    for(int curr_size = 1; curr_size < N; curr_size *= 2)
    {
        for(int left_start = 0; left_start < N - 1; left_start += 2 * curr_size)
        {
            int mid = min(left_start + curr_size - 1, N - 1);
            int right_end = min(left_start + 2 * curr_size - 1, N - 1);
            merge(a, left_start, mid, right_end);
        }
    }
}

int partition(int *a, int low, int high)
{
    int pivot = *(a + low);
    int i = low - 1, j = high + 1;
    while(true)
    {
        do
        {
            i += 1;
        } while (*(a + i) < pivot);
        do
        {
            j -= 1;
        } while(*(a + j) > pivot);
        if(i >= j)
            return j;
        int temp = *(a + i);
        *(a + i) = *(a + j);
        *(a + j) = temp;
    }
}

int partition_random(int *a, int low, int high)
{
    int random = low + rand() % (high - low);
    int temp = *(a + random);
    *(a + random) = *(a + low);
    *(a + low) = temp;
    return partition(a, low, high);
}

void quick_sort(int *a, int low, int high)
{
    if(low < high)
    {
        int pi = partition_random(a, low, high);
        quick_sort(a, low, pi);
        quick_sort(a, pi + 1, high);
    }
}

int main(void)
{
    printf("Menu:\n1. Generate random numbers.\n");
    printf("2. To generate an array out of random.txt.\n");
    printf("3. To sort the array using Recursive Merge Sort.\n");
    printf("4. To sort the array using Recursive Quick Sort.\n");
    printf("5. To sort the array using Iterative Merge Sort.\n");
    printf("6. To generate the file sorted.txt.\n");
    printf("7. Exit out of the program.\nEnter your input: ");
    int input, N;
    int *a;
    scanf("%d", &input);
    while(input != 7)
    {
        if(input == 1)
        {
            printf("Enter the number of random numbers to be generated: ");
            scanf("%d", &N);
            generate_random(N);
        }
        else if(input == 2)
            a = generate_arr(N);
        else if(input == 3)
        {
            clock_t start, elapsed;
            start = clock();
            merge_sort(a, 0, N - 1);
            elapsed = clock() - start;
            double time_taken = ((double)elapsed) / CLOCKS_PER_SEC;
            printf("Recursive Merge Sort implemented successfully in %lf seconds!\n", time_taken);
        }
        else if(input == 4)
        {
            clock_t start, elapsed;
            start = clock();
            quick_sort(a, 0, N - 1);
            elapsed = clock() - start;
            double time_taken = ((double)elapsed) / CLOCKS_PER_SEC;
            printf("Recursive Quick Sort implemented successfully in %lf seconds!\n", time_taken);
        }
        else if(input == 5)
        {
            clock_t start, elapsed;
            start = clock();
            merge_sort_iterative(a, N);
            elapsed = clock() - start;
            double time_taken = ((double)elapsed) / CLOCKS_PER_SEC;
            printf("Iterative Merge Sort inplemented successfully in %lf seconds!\n", time_taken);
        }
        else if(input == 6)
            generate_sorted(a, N);
        else if(input != 7)
            printf("Wrong Input!\n");
        printf("Enter your next input: ");
        scanf("%d", &input);
    }
    return 0;
}