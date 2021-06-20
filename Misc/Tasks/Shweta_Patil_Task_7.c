/*	
 *	@brief: 	Implementation of own 'cp' command
 *	@details:	This file contains basic implementation for copying single input source file to destination file.
 *				Usage example: cp_command.exe src.txt dest.txt 
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define BUFFER_SIZE 1024

int main(int argc, char *argv[])
{
	int i, ch;
	FILE* f_src = NULL;
	FILE* f_dest = NULL;

	/*	Input sanitization	*/
	if(argc != 3)
	{
		#ifdef DEBUG
			fprintf(stderr, "Usage error:%s:%d:Incorrect argument count:%d\n", __FILE__, __LINE__, argc);
		#else
			fprintf(stderr, "Usage error:%s file\n", __FILE__);
		#endif
		exit(EXIT_FAILURE);
	}

	/*	Step 1: Open the source file in read mode	*/
	f_src = fopen(argv[1], "r");
	if(f_src == NULL)
	{
		#ifdef DEBUG
			fprintf(stderr, "Usage error:%s:%d:%s file can't be opened\n", __FILE__, __LINE__, argv[1]);
		#else
			fprintf(stderr, "%s:Error while opening source file\n", __FILE__);
		#endif
		exit(EXIT_FAILURE);	
	}	

	/*	Step 2: Open the destination file	*/
	f_dest = fopen(argv[2], "w");
	if(f_dest == NULL)
	{
		#ifdef DEBUG
			fprintf(stderr, "Usage error:%s:%d:%s file can't be opened\n", __FILE__, __LINE__, argv[2]);
		#else
			fprintf(stderr, "%s:Error while opening destination file\n", __FILE__);
		#endif
		exit(EXIT_FAILURE);
	}
	

	/*	Step 3: Read each char from source and write to destination file	*/
	while((ch = fgetc(f_src)) != EOF)
	{
		fputc(ch, f_dest);	
	}

	/*	Step 4: Close both files & release the handles	*/
	fclose(f_src);
	f_src = NULL;

	fclose(f_dest);
	f_dest = NULL;

	exit(EXIT_SUCCESS);
}