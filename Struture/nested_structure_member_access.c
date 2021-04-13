#include<stdio.h>
#include<stdlib.h>

struct Date
{
    int day;
    int month;
    int year;
};
struct Student
{
    int roll_number;
    float marks;
    float attendence;
    struct Date date_of_birth;
};
struct Student s = {10, 78.90, 80.9, {04, 04, 2021}};
int main(void)
{
    int roll;
    float marks, attendence;
    int dd, mm, yy;

    // Read from struct
    roll = s.roll_number;
    marks = s.marks;
    attendence = s.attendence;
    dd = s.date_of_birth.day;
    mm = s.date_of_birth.month;
    yy = s.date_of_birth.year;
    printf("roll = %d marks = %.2f attendence = %.2f dd = %d mm = %d yy = %d\n",
            roll, marks, attendence, dd, mm, yy);

    // Write to structure
    s.roll_number = 22;
    s.marks = 200;
    s.attendence = 50.9;
    s.date_of_birth.day = 05;
    s.date_of_birth.month = 04;
    s.date_of_birth.year = 2022;

    // Read from structure
    roll = s.roll_number;
    marks = s.marks;
    attendence = s.attendence;
    dd = s.date_of_birth.day;
    mm = s.date_of_birth.month;
    yy = s.date_of_birth.year;
    printf("New values:\n");
    printf("roll = %d marks = %.2f attendence = %.2f dd = %d mm = %d yy = %d",
            roll, marks, attendence, dd, mm, yy);

    return(0);
}