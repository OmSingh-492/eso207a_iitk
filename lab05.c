#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

int **multiply(int **a, int **b, int n)
{
    int **c = (int **)malloc(n * sizeof(int *));
    for(int i = 0; i < n; i += 1)
        *(c + i) = (int *)malloc(n * sizeof(int));
    for(int i = 0; i < n; i += 1)
    {
        for(int j = 0; j < n; j += 1)
        {
            *(*(c + i) + j) = 0;
            for(int k = 0; k < n; k += 1)
                *(*(c + i) + j) += (*(*(a + i) + k)) * (*(*(b + k) + j));
        }
    }
    return c;
}

int **operation(int **a, int **b, int n, int op)
{
    int **c = (int **)malloc(n * sizeof(int *));
    for(int i = 0; i < n; i += 1)
        *(c + i) = (int *)malloc(n * sizeof(int));
    for(int i = 0; i < n; i += 1)
    {
        for(int j = 0; j < n; j += 1)
        {
            if(op == 0)
                *(*(c + i) + j) = *(*(a + i) + j) + (*(*(b + i) + j));
            else if(op == 1)
                *(*(c + i) + j) = *(*(a + i) + j) - (*(*(b + i) + j));
        }
    }
    return c;
}

int **strassen(int **a,int **b, int n)
{
    int **c;
    c = (int **)malloc(n * sizeof(int *));
    for(int i = 0; i < n; i += 1)
        *(c + i) = (int *)malloc(n * sizeof(int));
    
    if(n <= 8)
    {
        c = multiply(a, b, n);
        return c; 
    }

    int **A11 = (int **)malloc((n / 2) * sizeof(int *));
    int **A12 = (int **)malloc((n / 2) * sizeof(int *));
    int **A21 = (int **)malloc((n / 2) * sizeof(int *));
    int **A22 = (int **)malloc((n / 2) * sizeof(int *));
    int **B11 = (int **)malloc((n / 2) * sizeof(int *));
    int **B12 = (int **)malloc((n / 2) * sizeof(int *));
    int **B21 = (int **)malloc((n / 2) * sizeof(int *));
    int **B22 = (int **)malloc((n / 2) * sizeof(int *)); 
    int **P = (int **)malloc((n / 2) * sizeof(int *));
    int **Q = (int **)malloc((n / 2) * sizeof(int *));
    int **R = (int **)malloc((n / 2) * sizeof(int *));
    int **S = (int **)malloc((n / 2) * sizeof(int *));
    int **T = (int **)malloc((n / 2) * sizeof(int *));
    int **U = (int **)malloc((n / 2) * sizeof(int *));
    int **V = (int **)malloc((n / 2) * sizeof(int *));
    int **C11 = (int **)malloc((n / 2) * sizeof(int *));
    int **C12 = (int **)malloc((n / 2) * sizeof(int *));
    int **C21 = (int **)malloc((n / 2) * sizeof(int *));
    int **C22 = (int **)malloc((n / 2) * sizeof(int *));

    for(int i = 0; i < n / 2; i += 1)
    {
        *(A11 + i) = (int *)malloc((n / 2) * sizeof(int));
        *(A12 + i) = (int *)malloc((n / 2) * sizeof(int));
        *(A21 + i) = (int *)malloc((n / 2) * sizeof(int));
        *(A22 + i) = (int *)malloc((n / 2) * sizeof(int));
        *(B11 + i) = (int *)malloc((n / 2) * sizeof(int));
        *(B12 + i) = (int *)malloc((n / 2) * sizeof(int));
        *(B21 + i) = (int *)malloc((n / 2) * sizeof(int));
        *(B22 + i) = (int *)malloc((n / 2) * sizeof(int));
        *(P + i) = (int *)malloc((n / 2) * sizeof(int));
        *(Q + i) = (int *)malloc((n / 2) * sizeof(int));
        *(R + i) = (int *)malloc((n / 2) * sizeof(int));
        *(S + i) = (int *)malloc((n / 2) * sizeof(int));
        *(T + i) = (int *)malloc((n / 2) * sizeof(int));
        *(U + i) = (int *)malloc((n / 2) * sizeof(int));
        *(V + i) = (int *)malloc((n / 2) * sizeof(int));
        *(C11 + i) = (int *)malloc((n / 2) * sizeof(int));
        *(C12 + i) = (int *)malloc((n / 2) * sizeof(int));
        *(C21 + i) = (int *)malloc((n / 2) * sizeof(int));
        *(C22 + i) = (int *)malloc((n / 2) * sizeof(int));
    }
    
    for(int i = 0; i < n / 2; i += 1)
    {
        for(int j = 0; j < n / 2; j += 1)
        {
            *(*(A11 + i) + j) = *(*(a + i) + j); 
            *(*(B11 + i) + j) = *(*(b + i) + j); 
            *(*(A12 + i) + j) = *(*(a + i) + (j + n / 2));
            *(*(B12 + i) + j) = *(*(b + i) + (j + n / 2));
            *(*(A21 + i) + j) = *(*(a + (i + n / 2)) + j);
            *(*(B21 + i) + j) = *(*(b + (i + n / 2)) + j);
            *(*(A22 + i) + j) = *(*(a + (i + n / 2)) + (j + n / 2));
            *(*(B22 + i) + j) = *(*(b + (i + n / 2)) + (j + n / 2));
        }
    }

    P = strassen(operation(A12, A22, n / 2, 1), operation(B21, B22, n / 2, 0), n / 2);
    Q = strassen(operation(A11, A22, n / 2, 0), operation(B11, B22, n / 2, 0), n / 2);
    R = strassen(operation(A11, A21, n / 2, 1),operation(B11, B12, n / 2, 0), n / 2);
    S = strassen(operation(A11, A12, n / 2, 0), B22, n / 2);
    T = strassen(operation(A21, A22, n / 2, 0), B11, n / 2);
    U = strassen(A11, operation(B12, B22, n / 2, 1), n / 2);
    V = strassen(A22, operation(B21, B11, n / 2, 1), n / 2);

    C11 = operation(operation(operation(P, Q, n / 2, 0), V, n / 2, 0), S, n / 2, 1);
    C12 = operation(operation(Q, U, n / 2, 0), operation(R, T, n / 2, 0), n / 2, 1);
    C21 = operation(V, T, n / 2, 0);
    C22 = operation(S, U, n / 2, 0);

    for(int i = 0; i < n / 2; i += 1)
    {
        for(int j = 0; j < n / 2; j += 1)
        {
            *(*(c + i) + j) = *(*(C11 + i) + j);
            *(*(c + (i + n / 2)) + j) = *(*(C21 + i) + j);
            *(*(c + (i + n / 2)) + (j + n / 2)) = *(*(C12 + i) + j);
            *(*(c + i) + (j + n / 2)) = *(*(C22 + i) + j);
        }
    }

    free(A11); 
    free(B11); 
    free(C11);
    free(A12); 
    free(B12); 
    free(C12);
    free(A21); 
    free(B22); 
    free(C21);
    free(A22); 
    free(B21); 
    free(C22);
    free(P);
    free(Q);
    free(R);
    free(S);
    free(T);
    free(U);
    free(V);
    return c;
}


void print_matrix(int **a, int n)
{
    for(int i = 0; i < n; i += 1)
    {
        for(int j = 0; j < n; j += 1)
            printf("%d ", *(*(a + i) + j));
        printf("\n");
    }
}

void populate_matrices(int **a, int n)
{
    for(int i = 0; i < n; i += 1)
    {
        for(int j = 0; j < n; j += 1)
            *(*(a + i) + j) = rand() % 100;
    }
}

int main(void)
{
    int k, n, input;
    printf("Enter the value of k: ");
    scanf("%d", &k);
    n = pow(2, k);
    int **a = (int **)malloc(n * sizeof(int *));
    int **b = (int **)malloc(n * sizeof(int *));
    int **c = (int **)malloc(n * sizeof(int *));
    for(int i = 0; i < n; i += 1)
    {
        *(a + i) = (int *)malloc(n * sizeof(int));
        *(b + i) = (int *)malloc(n * sizeof(int));
        *(c + i) = (int *)malloc(n * sizeof(int));
    }
    populate_matrices(a, n);
    populate_matrices(b, n);
    printf("Menu:\n1. Multiply matrices using Strassen's Algorithm.\n2. Perform usual matrix multiplication.\n3. To print first matrix.\n");
    printf("4. To print the second matrix.\n5. To print the result.\n6. Exit.\nEnter your choice: ");
    scanf("%d", &input);
    clock_t start ,elapsed;
    while(input != 6)
    {
        if(input == 1)
        {
            start = clock();
            c = strassen(a, b, n);
            elapsed = clock() - start;
            printf("Time taken to multiply the matrices was %lf seconds!\n", ((double)elapsed)/CLOCKS_PER_SEC);
        }
        else if(input == 2)
        {
            start = clock();
            c = multiply(a, b, n);
            elapsed = clock() - start;
            printf("Time taken to multiply the matrices was %lf seconds!\n", ((double)elapsed)/CLOCKS_PER_SEC);
        }
        else if(input == 3)
        {
            printf("Contents of Matrix A:\n");
            print_matrix(a, n);
        }
        else if(input == 4)
        {
            printf("Contents of Matrix B:\n");
            print_matrix(b, n);
        }
        else if(input == 5)
        {
            printf("Contents of Matrix C:\n");
            print_matrix(c, n);
        }
        else if(input != 6)
            printf("Incorrect Input!\n");
        printf("Enter your next input: ");
        scanf("%d", &input);
    }
    free(a);
    free(b);
    free(c);
    return 0;
}