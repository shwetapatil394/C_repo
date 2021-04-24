#include<stdio.h>
#include<stdlib.h>

/*  get_summation() is a function: 
    accepting:
                1. pointer to array of integers
                2. integer
    returning:  
                integer
*/
int get_summation(int (*parr)[], int size);

int main()
{
    int A[10] = {10, 20, 30, 40, 50, 60, 70, 80, 90, 100};
    int sum;
    sum = get_summation(A, 10);
    printf("Textbook method: sum = %d\n", sum);
    return(0);
}

int get_summation(int (*parr)[], int size)
{
    int summation = 0;
    int i;
    for(i = 0; i < size; ++i)
        summation = summation + (*parr)[i];
    return summation;
}