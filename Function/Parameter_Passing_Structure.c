#include<stdio.h>
#include<stdlib.h>
#include<math.h>

struct point2d
{
    float x;
    float y;
};

float distance(struct point2d*, struct point2d*);

int main(void)
{
    struct point2d p1 = {1.1f, 2.2f};
    struct point2d p2 = {3.3f, 4.4f};
    float d;

    d = distance(&p1, &p2);         /*  Pass structure instance to a function   */
    printf("Distance = %.3f\n", d);

    return(0);    
}

float distance(struct point2d* p1, struct point2d* p2)
{
    float delta_x, delta_y;
    float ret;

    delta_x = p2->x - p1->x;
    delta_y = p2->y - p2->y;

    ret = sqrt(delta_x * delta_x + delta_y * delta_y); 
    return(ret);
}