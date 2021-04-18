#include<stdio.h>
#include<stdlib.h>

int get_square_1(int);          /*  Param passing by value  */
int get_square_2(int*);         /*  Param passing by reference  */
void get_square_3(int, int*);   /*  'Out' param     */
void get_square_4(int*);        /*  'Inout' param   */

int main(void)
{
    int n;
    int return_value;

    printf("Enter n:");
    scanf("%d", &n);

    return_value = get_square_1(n);
    printf("get_square_1: ret = %d\n", return_value);
    printf("*****************************************\n");

    return_value = get_square_2(&n);
    printf("get_square_2: ret = %d\n", return_value);
    printf("*****************************************\n");

    return_value = -1;
    printf("Before call to function, return_value = %d\n", return_value);
    get_square_3(n, &return_value);
    printf("After call to function, return_value = %d\n", return_value);
    printf("*****************************************\n");

    printf("Before call to function, n = %d\n", n);
    get_square_4(&n);
    printf("After call to function, n = %d\n", n);

    return(0);
}

int get_square_1(int v)
{
    int res;
    res = v * v;
    return(res);
}

int get_square_2(int *p)
{
    int local = *p;
    int res;
    res = local * local;
    return(res);
}

void get_square_3(int v, int* p)
{
    *p = v * v;
}

void get_square_4(int* p)
{
    int local = *p;
    *p = local * local;
}
