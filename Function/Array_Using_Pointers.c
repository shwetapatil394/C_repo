#include<stdio.h>
#include<stdlib.h>

/*  Note: 
    The method of manipulating array by using pointer to its element is more elegant.
    So, instead of declaring 'pointer to array', we generally use this syntax of declaration 
    of 'pointer to array element'. Then we use pointer arithmetic (addition of a constant / 
    subtraction of a constant) to read from / write to an array.
*/
int A[10];

void display(int *p, int size);

int main()
{
    int *parr = NULL; 
    int i;

    parr = &A[0];          /*  Pointer to array element    */
    
    /*  Write operation */
    for(i = 0; i < 10; ++i)
        *(parr + i) = (i+1) * 10;

    display(&A[0], 10);

    exit(0);
}

void display(int *parr, int size)
{
    int i;

    /*  Read operation  */
    for(i = 0; i < size; ++i)
        printf("A[%d] = %d\n", i, *(parr+i));
}