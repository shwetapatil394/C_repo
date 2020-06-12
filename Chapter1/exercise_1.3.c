/*
This prorgram prints fahrenheit to celsius temperature table with a header.
Demo of while loop usage. 
*/

#include <stdio.h>

int main()
{
	float celsius, fahr;
	int lower, upper, step;
	
	lower = 0;
	upper = 300;
	step = 20;
	
	fahr = lower;
	char *column1 = "fahr";
	char *column2 = "celsius";

	printf("%3s\t%3s\n", column1, column2);

	while(fahr <= upper)
	{
		celsius = (5.0 / 9.0) * (fahr-32.0);
		printf("%3.2f\t%3.2f\n", fahr, celsius);
		fahr = fahr + step;
	}
	return 0;
}
