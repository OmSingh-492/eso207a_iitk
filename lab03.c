#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void swap(int *a, int x, int y)
{
    int temp = *(a + x);
    *(a + x) = *(a + y);
    *(a + y) = temp;
}

int min(int x, int y)
{
    if(x < y)
        return x;
    else
        return y;
}

void generate_random(int N, int m)
{
    FILE *fp;
    fp = fopen("random.txt", "w");
    for(int i = 0; i < N; i += 1)
    {
        int num = rand() % (m  + 1);
        fprintf(fp, "%d\n", num);
    }
    fclose(fp);
}

int *generateArrHeap(int n)
{
    int *a = (int *)malloc((n + 1) * sizeof(int));
    FILE *fp = fopen("random.txt", "r");
    for(int i = 1; i <= n; i += 1)
    {
        fscanf(fp, "%d", (a + i));
    }
    fclose(fp);
    *a = -1;
    return a;
}

void generateSortedHeap(int *a, int N)
{
    FILE *fp = fopen("sorted.txt", "w");
    for(int i = N; i >= 1; i -= 1)
    {
        fprintf(fp, "%d\n", *(a + i));
    }
    fclose(fp);
}

void generate_sorted(int *a, int N)
{
    FILE *fp = fopen("sorted.txt", "w");
    for(int i = 0; i < N; i += 1)
    {
        fprintf(fp, "%d\n", *(a + i));
    }
    fclose(fp);
}

void generate_sorted_bucket(int *arr, int max)
{
    FILE *fp = fopen("sorted.txt", "w");
    for(int i = 0; i < max + 1; i += 1)
    {
        for(int j = 0; j < *(arr + i); j += 1)
            fprintf(fp, "%d\n", i);
    }
    fclose(fp);
}

int *generate_arr(int n)
{
    int *a = (int *)malloc(n * sizeof(int));
    FILE *fp = fopen("random.txt", "r");
    for(int i = 0; i < n; i += 1)
    {
        fscanf(fp, "%d", (a + i));
    }
    fclose(fp);
    return a;
}

void sink(int *a, int k, int N)
{
    while(2 * k <= N)
    {
        int j = 2 * k;
        if(j < N && *(a + j) > *(a + j + 1))
            j += 1;
        if(*(a + k) < *(a + j))
            break;
        swap(a, k, j);
        k = j;
    }
}

void heap_sort(int *a, int length)
{
    clock_t t, t_elapsed;
    t = clock();
    for(int k = length / 2; k >= 1; k -= 1)
        sink(a, k, length);
    while(length > 1)
    {
        swap(a, 1, length);
        length -= 1;
        sink(a, 1, length);
        t_elapsed = clock() - t;
        if(((double) t_elapsed) / CLOCKS_PER_SEC > 180)
            printf("More than three minutes consumed! Exit using Ctrl + C!\n");
    }
    t_elapsed = clock() - t;
    double elapsed = ((double) t_elapsed) / CLOCKS_PER_SEC;
    printf("Heap Sort successfully executed in %lf seconds!\n", elapsed);
}

int *bucket_sort(int *a, int length, int max)
{
    clock_t t, t_elapsed;
    t = clock();
    int *arr = (int *) malloc((max + 1) * sizeof(int));
    for(int i = 0; i < max + 1; i += 1)
        *(arr + i) = 0;
    for(int i = 0; i < length; i += 1)
    {
        int element = *(a + i);
        *(arr + element) += 1;
        t_elapsed = clock() - t;
        if((double) t_elapsed / CLOCKS_PER_SEC > 180)
            printf("More than three minutes consumed! Exit using Ctrl + C!\n");
    }
    t_elapsed = clock() - t;
    double elapsed = ((double)t_elapsed) / CLOCKS_PER_SEC;
    printf("Bucket Sort successfully executed in %lf seconds!\n", elapsed);
    return arr;
}

void merge(int *a, int l, int m, int r)
{
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;
    int L[n1], R[n2];
    for(i = 0; i < n1; i += 1)
        L[i] = *(a + l + i);
    for(j = 0; j < n2; j += 1)
        R[j] = *(a + m + 1 + j);
    i = 0;
    j = 0;
    k = l;
    while(i < n1 && j < n2)
    {
        if(L[i] <= R[j])
        {
            *(a + k) = L[i];
            i += 1;
        }
        else
        {
            *(a + k) = R[j];
            j += 1;
        }
        k += 1;
    }
    while(i < n1)
    {
        *(a + k) = L[i];
        i += 1;
        k += 1;
    }
    while(j < n2)
    {
        *(a + k) = R[j];
        j += 1;
        k += 1;
    }
}

void merge_sort(int *a, int length)
{
    clock_t t, t_elapsed;
    t = clock(); 
    for(int curr_size = 1; curr_size < length; curr_size += 1)
    {
        for(int left_start = 0; left_start < length - 1; left_start += 2 * curr_size)
        {
            int mid = min(left_start + curr_size - 1, length - 1);
            int right_end = min(left_start + 2 * curr_size - 1, length - 1);
            merge(a, left_start, mid, right_end);
            t_elapsed = clock() - t;
            if((double) t_elapsed / CLOCKS_PER_SEC > 180)
                printf("More than three minutes consumed! Exit using Ctrl + C!\n");
        }
    }
    t_elapsed = clock() - t;
    double elapsed = ((double)t_elapsed) / CLOCKS_PER_SEC;
    printf("Merge Sort successfully executed in %lf seconds!\n", elapsed);
}

int main(void)
{
    printf("Menu:\n1. To generate a fixed number of random numbers and put them in random.txt.\n");
    printf("2. To generate an array out of random.txt for Bucket Sort or Merge Sort.\n");
    printf("3. To generate an array out of random.txt for Heap Sort.\n");
    printf("4. To run the Bucket Sort algorithm on random.txt.\n");
    printf("5. To run the Iterative Merge Sort algorithm on random.txt.\n");
    printf("6. To run the Heap Sort algorithm on random.txt.\n");
    printf("7. To copy the result of Bucket Sort to the file sorted.txt.\n");
    printf("8. To copy the result of Iterative Merge Sort to the file sorted.txt.\n");
    printf("9. To copy the result of Heap Sort to the file sorted.txt.\n");
    printf("10. To exit out of the program.\n");
    printf("Enter your choice: ");
    int input;
    scanf("%d", &input);
    int *a;
    int N, max;
    while(input != 10)
    {
        if(input == 1)
        {
            printf("Enter the number of numbers to be randomly generated and the range for maximum integer (space-separated): ");
            scanf("%d%d", &N, &max);
            generate_random(N, max);
            printf("Numbers generated successfully!\n");
        }
        else if(input == 2)
        {
            a = generate_arr(N);
            printf("Array generation successful!\n");
        }
        else if(input == 3)
        {
            a = generateArrHeap(N);
            printf("Array generation successful!\n");
        }
        else if(input == 4)
        {
            a = bucket_sort(a, N, max);
        }
        else if(input == 5)
        {
            merge_sort(a, N);
        }
        else if(input == 6)
        {
            heap_sort(a, N + 1);
        }
        else if(input == 7)
        {
            generate_sorted_bucket(a, max);
            printf("File generation successful!\n");
        }
        else if(input == 8)
        {
            generate_sorted(a, N);
            printf("File generation successful!\n");
        }
        else if(input == 9)
        {
            generateSortedHeap(a, N);
            printf("File generation successful!\n");
        }
        else if(input != 10)
            printf("Wrong Input!\n");
        printf("Enter your next input: ");
        scanf("%d", &input);
    }
    return 0;
}