#include<stdio.h>
#include<stdlib.h>

struct point2d
{
    float x;
    float y;
};
struct triangle
{
    struct point2d* p_A;
    struct point2d* p_B;
    struct point2d* p_C;
};
struct point2d A;
struct point2d B;
struct point2d C;

/*  Create structure instance variable  */
struct triangle T;

int main(void)
{
    /*  Create structure pointer variable   */
    struct triangle* pT = NULL;
    pT = &T;

    /*  Access structure elements using pointer variable    */
    pT->p_A = &A;
    pT->p_B = &B;
    pT->p_C = &C;

    pT->p_A->x = 10.34;
    pT->p_A->y = 20.90;

    pT->p_B->x = 30.987;
    pT->p_B->y = 40.9;

    pT->p_C->x = 50.45;
    pT->p_C->y = 60.4;

    printf("Printing value of triangle vertices:\n");
    printf("A:%.3f, %.3f\n", pT->p_A->x, pT->p_A->y);
    printf("B:%.3f, %.3f\n", pT->p_B->x, pT->p_B->y);
    printf("C:%.3f, %.3f\n", pT->p_C->x, pT->p_C->y);

    return(0);
}