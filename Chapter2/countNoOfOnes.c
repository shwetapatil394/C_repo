// This program counts number of ones in given number.

#include <stdio.h>

int bitcount(unsigned int);

void main(void)
{
	int num;
	printf("Enter a number.\n");
	scanf("%d", &num);
	printf("No. of ones in given number:%d\n", bitcount(num));
}

//int bitcount(unsigned int x)
/*{
	int b;
	for(b = 0; x != 0; x >>= 1)
	{
		if(x & 01)
			b++;
	}
	return b;
}*/

int bitcount(unsigned int x)
{
	int b;
	for(b = 0; x != 0; x &= (x-1))
		b++;
	return b;
}
