#include<stdio.h>
#include<stdlib.h>

struct point2d
{
    float x;
    float y;
};
struct triangle
{
    struct point2d A;
    struct point2d B;
    struct point2d C;
};

/*  Create structure instance variable  */
struct triangle T;

int main()
{
    // struct T* pT = NULL;    /*  Create pointer variable for structure   */
    struct triangle* pT = NULL;
    pT = &T;

    /*  Get user input data for triangle coordinates    */
    printf("Enter point A x value:");
    scanf("%f", &T.A.x);
    printf("Enter point A y value:");
    scanf("%f", &T.A.y);
    printf("Enter point B x value:");
    scanf("%f", &T.B.x);
    printf("Enter point B y value:");
    scanf("%f", &T.B.y);
    printf("Enter point C x value:");
    scanf("%f", &T.C.x);
    printf("Enter point C y value:");
    scanf("%f", &T.C.y);

    /*  Show the data entered back on screen    */
    printf("You entered..\n");
    printf("A->x = %.3f\n", pT->A.x);
    printf("A->y = %.3f\n", pT->A.y);
    printf("B->x = %.3f\n", pT->B.x);
    printf("B->y = %.3f\n", pT->B.y);
    printf("C->x = %.3f\n", pT->C.x);
    printf("C->y = %.3f\n", pT->C.y);

    return(0);
}