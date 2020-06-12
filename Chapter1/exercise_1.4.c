/*
This program converts and prints temperatures from celsius to fahrenheit values. 
Commented lines converts temperatures from fahrenheit to celsius values.
It is demonstration of for loop.
*/

#include <stdio.h>

int main(void)
{
	int lower = 0; 
	int upper = 300; 
	int step = 20;
	int celsius, fahr;

	for(celsius = lower; celsius <= upper; celsius = celsius + step)
	{
		fahr = ((9 * celsius)/ 5) + 32;
		printf("%d\t%d\n", celsius, fahr);
	}
	/*int fahr;	
	for(fahr = 0; fahr <= 300; fahr = fahr + 20)
	{
		printf("%d\t%6.1f\n", fahr, ((5.0 / 9.0) * (fahr - 32)));
	}*/
	return 0;	
}
