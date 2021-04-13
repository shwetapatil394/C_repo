#include<stdio.h>
#include<stdlib.h>

int n1, n2, n3;
int find_max_within_3(int, int, int);

int main(void)
{
    int ret;

    printf("Enter n1:");
    scanf("%d", &n1);
    printf("Enter n2:");
    scanf("%d", &n2);
    printf("Enter n3:");
    scanf("%d", &n3);

    ret = find_max_within_3(n1, n2, n3);

    printf("Max no. among above three nos.:%d\n", ret);

    return(0);
}
int find_max_within_3(int num1, int num2, int num3)
{
    int max_number;
    if(num1 > num2)
        max_number = num1;
    else
        max_number = num2;
    if(num3 > max_number)
        max_number = num3;

    return (max_number);
}