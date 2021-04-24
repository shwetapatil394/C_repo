#include<stdio.h>
#include<stdlib.h>

/*  Notes: Typewise evaluation 
    typeof(A) = int [10]
    typeof(&A) = int (*)[10]

    similarly, typeof(parr) = int (*)[10]
*/
int A[10];          /*  A is an array 10 of integers */

int main()
{
    int (*parr)[10] = NULL;     /*  Declaration of pointer to array 10 of int   */
    int i;
    parr = &A;

    /*  Write operation using pointer to array  */
    for(i = 0; i < 10; ++i)
        (*parr)[i] = (i+1) * 10;

    /*  Read operation using pointer to array   */
    for(i = 0; i < 10; ++i)
        printf("A[%d] = %d\n", i, (*parr)[i]);

    exit(EXIT_SUCCESS);    
}