#include<stdio.h>

struct Date
{
    int day;
    int month;
    int year;
};
struct Date d1 = {03, 04, 2021};
struct Date d2;
void main(void)
{
    int dd, mm, yy;
    // Read operation on structure members
    dd = d1.day;
    mm = d1.month;
    yy = d1.year;
    printf("dd = %d mm = %d yy = %d\n", dd, mm, yy);

    // Write operation on structure members
    d1.day = 04;
    d1.month = 05;
    d1.year = 2022;

    dd = d1.day;
    mm = d1.month;
    yy = d1.year;
    printf("After:\tdd = %d mm = %d yy = %d\n", dd, mm, yy);

    // Initialise structure instance d2 from user inputs
    printf("Enter day value for d2:");
    scanf("%d", &d2.day);

    printf("Enter month value for d2:");
    scanf("%d", &d2.month);

    printf("Enter year value for d2:");
    scanf("%d", &d2.year);
    printf("d2.day = %d  d2.month = %d   d2.year = %d\n", d2.day, d2.month, d2.year);

    //return(0);
}