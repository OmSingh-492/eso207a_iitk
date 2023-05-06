#include <stdio.h>
#include <float.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

//Initiating the problem
struct point
{
    int x;
    int y;
};

double min(double x, double y)
{
    if(x > y)
        return y;
    return x;
}

struct point *generatePoints(struct point *P, int N, int lower, int upper)
{
    for(int i = 0; i < N; i += 1)
    {
        (P + i) -> x = lower + rand() % (upper - lower);
        (P + i) -> y = lower + rand() % (upper - lower);
    }
    return P;
}

void printPoints(struct point *P, int N)
{
    for(int i = 0; i < N; i += 1)
    {
        printf("(%d, %d)\n", (P + i) -> x, (P + i) -> y);
    }
}

double distance(struct point *P, int i, int j)
{
    double distance = sqrt(pow(((P + i) -> y - (P + j) -> y), 2) + pow(((P + i) -> x - (P + j) -> x), 2));
    return distance;
}

int compareX(const void *a, const void *b)
{
    struct point *p1 = (struct point *)a;
    struct point *p2 = (struct point *)b;
    return ((p1 -> x) - (p2 -> x));
}

int compareY(const void *a, const void *b)
{
    struct point *p1 = (struct point *)a;
    struct point *p2 = (struct point *)b;
    return ((p1 -> y) - (p2 -> y));
}

//The Brute Force Algorithm
double bruteForce(struct point *P, int N)
{
    double minimum = FLT_MAX;
    for(int i = 0; i < N; i += 1)
    {
        for(int j = i + 1; j < N; j += 1)
            minimum = min(minimum, distance(P, i, j));
    }
    return minimum;
}

//Actual Divide and Conquer Algorithm
double aux2(struct point *strip, int size, double d)
{
    double minimum = d;
    qsort(strip, size, sizeof(struct point), compareY);
    for(int i = 0; i < size; i += 1)
    {
        for(int j = i + 1; j < size && (((strip + j) -> y) - ((strip + i) -> y) < minimum); j += 1)
            minimum = min(minimum, distance(strip, i, j));
    }
    return minimum;
}

double aux1(struct point *P, int N)
{
    if(N <= 3)
        return bruteForce(P, N);
    int mid = N / 2;
    struct point *midPoint = (P + mid);
    double dLeft = aux1(P, mid);
    double dRight = aux1(P + mid, N - mid);
    double d = min(dLeft, dRight);
    
    struct point *strip = (struct point *)malloc(N * sizeof(struct point));
    int j = 0;
    for(int i = 0; i < N; i += 1)
    {
        if(abs(((P + i) -> x) - (midPoint -> x)) < d)
        {
            *(strip + j) = *(P + i);
            j += 1;
        }
    }
    double closest = aux2(strip, j, d);
    free(strip);
    return min(d, closest);
}

double divideAndConquer(struct point *P, int N)
{
    qsort(P, N, sizeof(struct point), compareX);
    return aux1(P, N);
}

//Driver Function
int main(void)
{
    int N, choice, lower, upper;
    printf("Enter the number of points to be generated, lower limit and upper limit of the coordinates: ");
    scanf("%d %d %d", &N, &lower, &upper);
    struct point *P = (struct point *)malloc(N * sizeof(struct point));
    P = generatePoints(P, N, lower, upper);
    printf("Menu:\n1. Find the closest pair of points using the O(n^2) algorithm.\n2. Find the closest pair of points using the O(nlg n) D&C algorithm.\n3. To print the points.\n");
    printf("4. Exit.\nEnter your choice: ");
    scanf("%d", &choice);
    while(choice != 4)
    {
        if(choice == 1)
        {
            double minDistance;
            clock_t start, elapsed;
            start = clock();
            minDistance = bruteForce(P, N);
            elapsed = clock() - start;
            double timeTaken = (double) elapsed / CLOCKS_PER_SEC;
            printf("The brute force algorithm for %d points took %lf seconds!\n", N, timeTaken);
            printf("The minimum distance between any pair of points was found out to be: %lf.\n", minDistance);
        }
        else if(choice == 2)
        {
            double minDistance;
            clock_t start, elapsed;
            start = clock();
            minDistance = divideAndConquer(P, N);
            elapsed = clock() - start;
            double timeTaken = (double) elapsed / CLOCKS_PER_SEC;
            printf("The divide and conquer algorithm for %d points took %lf seconds!\n", N, timeTaken);
            printf("The minimum distance between any pair of points was found out to be: %lf.\n", minDistance);
        }
        else if(choice == 3)
            printPoints(P, N);
        else
            printf("Wrong input entered!\n");
        printf("Enter next choice: ");
        scanf("%d", &choice);
    }
    free(P);
    return 0;
}