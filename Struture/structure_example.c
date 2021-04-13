/* 
 *  This program computes distance between two points using mathematical formula 
 *  distance = sqrt(pow((x2 - x1), 2) - power((y2 - y1), 2))
 */

#include<stdio.h>
#include<stdlib.h>
#include<math.h>

/* Information structure for a 2d point */
struct point2d
{
    float x;
    float y;
};
int main()
{
    struct point2d p1 = {1.1f, 2.2f};
    struct point2d p2 = {-3.9f, 1.8f};
    float distance = 0.0f;
    float delta_x = 0.0f;
    float delta_y = 0.0f;

    delta_x = p2.x - p1.x;
    delta_y = p2.y - p1.y;

    distance = sqrt(pow(delta_x, 2) - pow(delta_y, 2));
    printf("Distance between two points = %0.3f\n", distance);
    return(0);
}