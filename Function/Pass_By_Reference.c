#include<stdio.h>
#include<stdlib.h>

/*  Function declaration    */
int get_square(int*);

int main(void)
{
    int m = 100;
    int rs;

    printf("Address of m:%p\n", &m);

    printf("Value of m before call to function = %d\n", m);
    rs = get_square(&m);
    printf("result = %d\n", rs);
    printf("Value of m after call to function = %d\n", m);    
    return(0);
}

/*  Function definition */
int get_square(int* p)
{
    int n = *p;    
    int rs;
    printf("get_square:p = %p, n = %d\n", p, n);
    rs = n * n;
    *p = 200;
    return(rs);
}