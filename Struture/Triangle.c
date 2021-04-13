/*  Basic triangle and its operations   */
#include<stdio.h>
#include<stdlib.h>
#include<math.h>

#define M_PI    3.14159265358979323846

/*  Structure declaration for a 2D point    */
struct point2d{
    float x;
    float y;
};
/*  Structure for declaration of a triangle */
struct triangle{
    struct point2d A;
    struct point2d B;
    struct point2d C;
};
struct triangle T;

int main()
{
    float a, b, c, s;
    int triangle_valid_flag = 1;
    float perimeter;
    float area;
    float angle_A_rad;
    float angle_B_rad;
    float angle_C_rad;
    float angle_A_in_degrees;
    float angle_B_in_degrees;
    float angle_C_in_degrees;
    float cos_of_A;
    float cos_of_B;
    float cos_of_C;

    /*  Input triangle coordinates  */
    printf("Enter A.x:");
    scanf("%f", &T.A.x);
    printf("Enter A.y:");
    scanf("%f", &T.A.y);

    printf("Enter B.x:");
    scanf("%f", &T.B.x);
    printf("Enter B.y:");
    scanf("%f", &T.B.y);

    printf("Enter C.x:");
    scanf("%f", &T.C.x);
    printf("Enter C.y:");
    scanf("%f", &T.C.y);

    /*  F1: Compute a, b, c where a = l(BC), b = l(CA), c = l(AB)   */
    a = sqrt(pow((T.B.x - T.C.x), 2) + pow((T.B.y - T.C.y), 2));
    b = sqrt(pow((T.C.x - T.A.x), 2) + pow((T.C.y - T.A.y), 2));
    c = sqrt(pow((T.A.x - T.B.x), 2) + pow((T.A.y - T.B.y), 2));

    printf("a = %.3f, b = %.3f, c = %.3f\n", a, b, c);

    /*  F2: Check for validity  */
    if((a + b <= c) || (b + c <= a) || (c + a <= b))
        triangle_valid_flag = 0;

    if(triangle_valid_flag == 0)
    {
        puts("Points A, B, C do not form a valid triangle.\n");
        exit(-1);
    }

    /*  F3: Compute perimeter of triangle   */
    perimeter = a + b + c;
    printf("perimeter = %.3f\n", perimeter);

    /*  F4: Compute area of triangle    */
    s = perimeter / 2;
    area = sqrt(s * (s - a) * (s - b) * (s - c));
    printf("area = %.3f\n", area);

    /*  F5: Compute angles  */
    /*  F5.1: Compute cosine ratios of all triangles    */
    cos_of_A = (pow(b, 2) + pow(c, 2) - pow(a, 2))/(2*b*c);
    cos_of_B = (pow(c, 2) + pow(a, 2) - pow(b, 2))/(2*c*a);
    cos_of_C = (pow(a, 2) + pow(b, 2) - pow(c, 2))/(2*a*b);

    angle_A_rad = acos(cos_of_A);
    angle_B_rad = acos(cos_of_B);
    angle_C_rad = acos(cos_of_C);

    angle_A_in_degrees = angle_A_rad * (180.0f / M_PI);
    angle_B_in_degrees = angle_B_rad * (180.0f / M_PI);
    angle_C_in_degrees = angle_C_rad * (180.0f / M_PI);

    printf("measure angle A in degrees = %.3f\n", angle_A_in_degrees);
    printf("measure angle B in degrees = %.3f\n", angle_B_in_degrees);
    printf("measure angle C in degrees = %.3f\n", angle_C_in_degrees);

    printf("Summation of all angles of triangle = %.3f\n",
            angle_A_in_degrees + angle_B_in_degrees + angle_C_in_degrees);

    return(0);

}