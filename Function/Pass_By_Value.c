#include<stdio.h>
#include<stdlib.h>

int get_square(int);

int main(void)
{
    int m = 100;
    printf("Value of m before func call = %d\n", m);
    int rs = get_square(m);
    printf("Result : %d\n", rs);
    printf("Value of m after func call = %d\n", m);    
    return(0);
}

int get_square(int n)
{
    int rs;
    printf("get_square(): Value of n = %d\n", n);
    rs = n * n;
    n = 200;
    return(rs);
}