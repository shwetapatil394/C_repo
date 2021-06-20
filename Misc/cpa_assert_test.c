/*	Use of our own cpa_assert function	*/

#include <stdio.h>
#include <stdlib.h>

#include "cpa_assert.h"

int main(void)
{
	int nr, dr;
	printf("Enter numerator:");
	scanf("%d", &nr);

	printf("Enter denominator:");
	scanf("%d", &dr);

	cpa_assert(dr!=0);

	printf("Division = %f\n", (float)nr/dr);
	exit(EXIT_SUCCESS);
}