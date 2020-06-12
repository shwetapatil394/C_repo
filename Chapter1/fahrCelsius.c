/*
This program prints temperature conversion table from fahrenheit to celsius.
Demo of for loop usage.
*/

#include<stdio.h>

void convertTemp(int, int, int);

int main(void)
{
	int lower = 0;
	int upper = 300;
	int step = 20;

	printf("Table for fahr to celsius:\n");
	convertTemp(lower, upper, step);

}
	
void convertTemp(int lower, int upper, int step)
{
	float fahr, celsius;
	for(fahr = lower; fahr <= upper; fahr = fahr+step)
	{
		celsius = 5.0 * (fahr-32) / 9.0;
		printf("%3.0f %6.1f\n", fahr, celsius);
	}
}
	
