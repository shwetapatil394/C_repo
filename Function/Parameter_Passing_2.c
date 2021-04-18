#include<stdio.h>
#include<stdlib.h>

#define SIZE 10
int get_summation(int* A, int n);

int main()
{
    int A[SIZE];
    int i, n, result;

    printf("Enter 10 elements:\n");
    for(i = 0; i < SIZE; ++i)
        scanf("%d", &A[i]);

    printf("Get no. of elements whose sum is requested:");
    scanf("%d", &n);

    result = get_summation(&A[0], n);
    printf("Result = %d\n", result);

    return(0);   
}

int get_summation(int* p, int n)
{
    int i;
    int summation = 0;

    for(i = 0; i < n; ++i)
        summation = summation + p[i];

    return(summation);
}