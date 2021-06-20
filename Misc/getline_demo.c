/* @brief: Demo usage of getline() function on linux	*/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

int main(int argc, char* argv[])
{
	FILE *ip_file = NULL;
	ip_file = fopen(argv[1], "r");
	assert(ip_file);

	char *line = NULL;
	size_t n = 0;

	while(getline(&line, &n, ip_file) != -1)
	{
		printf("%s", line);
		free(line);
		line = NULL;
		n = 0;
	}
	exit(EXIT_SUCCESS);
}

/*
int n = 5;
int* ptr = &n;	// pointer to int

int value = {1, 2, 3, 4, 5};
int (*ptr_i)[5] = &value;// pointer to array

int *ptr_val = &value[0]; or int *ptr_val = value;// pointer to array element 
*/

