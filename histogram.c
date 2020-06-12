#include <stdio.h>

#define STAR_CHAR		'*'
#define MAX_WORD_LEN_LIMIT	255

int main(void)
{
	int c, i, j;
	int max_word_len = 0, word_len = 0;
	int max_word_occurence = 0, occurence = 0;
	int word_histogram[MAX_WORD_LEN_LIMIT];
	
	for(i = 0; i < MAX_WORD_LEN_LIMIT; i++)
		word_histogram[i] = 0;

	printf("Input word length : max value = 255\n");	
	while((c = getchar()) != EOF)
	{
		if(c == ' ' || c == '\t' || c == '\n')
		{
			occurence = ++word_histogram[word_len];
			if(word_len > max_word_len)
				max_word_len = word_len;
			if(occurence > max_word_occurence)
				max_word_occurence = occurence;
			word_len = 0;		
		}
		else
		{
			++word_len;
		}
	}
	printf("\n	Horizontal histogram	\n");
	printf("	--------------------	\n");
	for(i = 1; i <= max_word_len; i++)
	{
		printf("%2d", i);
		for(j = 0; j < word_histogram[i]; j++)
			printf("%4c", STAR_CHAR);
		printf("%4d\n", word_histogram[i]);
	}
	printf("\n	Vertical histogram	\n");
	printf("	--------------------	\n");
	for(i = max_word_occurence; i > 0; i--)
	{
		printf("%2d", i);
		for(j = 1; j <= max_word_len; j++)
		{
			if(i <= word_histogram[j])
			{
				printf("%4c", STAR_CHAR);
			}		
			else
			{
				printf("    ");
			}
		}
		printf("\n");
	}
	printf("  ");
	for(i = 1; i <= max_word_len; i++)
	{
		printf("%4d", i);
	}	
	printf("\n\n");
	return 0;
}
