/*	@brief	: Basic file operations			*/
/*	@details: File open, read, write, close	*/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define BUFFER_SIZE	256

int main(int argc, char* argv[])
{
	FILE* fp = NULL;
	char *lines[] = {"This is first line\n", 
						"This is second line\n",
							"This is last line\n"};
	int i;
	char buffer[BUFFER_SIZE];
	int nr_lines = sizeof(lines)/sizeof(lines[0]);

	/*	Input sanitization	*/
	if(argc != 2)
	{
		fprintf(stderr, "UsageError:%s file\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	/*	Open the file and write some data	*/
	fp = fopen(argv[1], "w");
	assert(fp!=NULL);
	for(i = 0; i < nr_lines; ++i)
	{
		fputs(lines[i], fp);
	}
	fclose(fp);
	fp = NULL;

	/*	Read the file data and put it on console	*/
	fp = fopen(argv[1], "r");
	assert(fp != NULL);
	for(i = 0; i < nr_lines; ++i)
	{
		fgets(buffer, BUFFER_SIZE, fp);
		printf("%s", buffer);
		memset(buffer, 0, BUFFER_SIZE);
	}
	fclose(fp);
	fp = NULL;

	exit(EXIT_SUCCESS);
}