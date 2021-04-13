#include<stdio.h>
#include<stdlib.h>

struct Date
{
    int day;
    int month;
    int year;
};
struct Date d1;

struct Student
{
    int roll_number;
    float marks;
    float attendence;
    struct Date date_of_birth;
};
struct Student s1;

int main(void)
{
    printf("Size of struct date: %zu\n", sizeof(struct Date));
    printf("Size of struct student: %zu\n", sizeof(struct Student));
    return (0);
}