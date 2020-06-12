#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void reverse(char s[], int len)
{
	int i;
	char r[100];

	int count = len - 1;

	for(i = 0; i < len; i++)
	{
		r[i] = s[count];
		count--;		
	}
	r[i] = '\0';
	printf("Reversed string: %s\n", r);
}

int main(void)
{
	char s[100];

	strcpy(s, "atewhs");
	reverse(s, strlen(s));
}
