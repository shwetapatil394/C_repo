/*
 *	@file: 		recursion.c
 *	@brief:		Usage examples of 'recursive' routines
 *	@details:	Following recursive routines are implemented:
 *				Factorial, Summation, print_array_reverse, print_array
 *				array_reverse_in_place, find_max, search
 */

#include <stdio.h>
#include <stdlib.h>

unsigned long long fact(unsigned long long);
unsigned long long sigma(int*, int);
void print_array_reverse_r(int*, int);
void print_array_r(int*, int, int);
void array_reverse_in_place_r(int*, int, int);
int find_max(int*, int, int);
int search(int*, int, int, int);
void insertion_sort(int*, int);

int main(void)
{
	/*	Variable declarations	*/
	unsigned long long n = 5;
	unsigned long long summation = 0;
	int a[5] = {1, 2, 3, 4, 5};
	int b[15] = {	
					500, 6786, 1, 5858, 9,
					78787, 99, 878, 660, 700,
					887, 343, 999, 99999, 0
				};
	int i = 0, index = 0;
	int max_element;

	printf("fact(%llu):%llu\n", n, fact(n));
	summation = sigma(a, 5);
	printf("sigma(a, 5):%llu\n", summation);
	print_array_reverse_r(a, 5);
	print_array_r(a, 0, 5);

	puts("Array before reversal:");
	for(i = 0; i < 5; ++i)
		printf("a[%d]:%d\n", i, a[i]);
	array_reverse_in_place_r(a, 0, 4);
	puts("Array after reversal[0:4]:");
	for(i = 0; i < 5; ++i)
		printf("a[%d]:%d\n", i, a[i]);
	array_reverse_in_place_r(a, 2, 4);
	puts("Array after inplace reversal[2:4]");
	for(i = 0; i < 5; ++i)
		printf("a[%d]:%d\n", i, a[i]);
	max_element = find_max(b, 0, 14);
	printf("Max_Element = %d\n", max_element);
	insertion_sort(b, 15);
	for(i = 0; i < 15; ++i)
	{
		index = search(b, b[i], 0, 14);
		printf("Element %d is found at index %d\n", b[i], index);
	}
	return(EXIT_SUCCESS);
}

/*	Factorial	*/
/*
			=	n * fact(n-1)	... if n>0
	fact(n)    
			=	1				... if n = 0
*/			
unsigned long long fact(unsigned long long n)
{
	if(n == 0)
		return (1);
	return(n * fact(n-1));
}

/*	Summation of all the array elements	*/
/*
					= A[N-1] + SIGMA[A, N-1]	... if N >= 1
	SIGMA(A, N)  
					= 0							... if N = 0
*/
unsigned long long sigma(int *pa, int N)
{
	if(N == 0)
		return (0);
	return (pa[N-1] + sigma(pa, N-1));
}

/*	Print array in reverse order	*/
/*
								= 	print(A[N-1])
									PrintArrayReverse(A, N-1)	.. if N > 0
	PrintArrayReverse(A, N)  
								= 	print(END)					.. if N == 0			
*/
void print_array_reverse_r(int* pa, int N)
{
	if(N == 0)
	{
		puts("END");
		return;
	}
	printf("a[%d]:%d\n", N-1, pa[N-1]);
	print_array_reverse_r(pa, N-1);
}

/*	Print array in forward order	*/
/*
									print(a[index])
									print_array(a, index+1, size)	... if index < size
	print_array(a, index, size) = 
									print(END)						.... if index == size

*/
void print_array_r(int* pa, int index, int size)
{
	if(index == size)
	{
		puts("END");
		return;
	}
	printf("a[%d]:%d\n", index, pa[index]);
	print_array_r(pa, index+1, size);
}

/*	Inplace reversal of array: recursive version	*/
/*
							= swap(A[start], A[end])
								  reverse(A, start+1, end-1)		.. if start < end
	 	reverse(A, start, end)
							= Nothing								... if start >= end
*/
void array_reverse_in_place_r(int* pa, int start, int end)
{
	int tmp;
	if(start == end)
		return;
	tmp = pa[start];
	pa[start] = pa[end];
	pa[end] = tmp;
	array_reverse_in_place_r(pa, start+1, end-1);
}

//////////////////////////////////////////////////////////////////////////

/*	DOUBLE LEVEL RECURSION	*/

/*	Find max element from given array 	*/
/*
				max(
						max(A, i, (i+j)/2)
						max(A, ((i+j)/2)+1, j)
					)	...	if i < j
max(A, i, j) = 
				A[i]	...	if i == j
*/
int find_max(int* pa, int start_index, int end_index)
{
	int mid_index;
	int max_L, max_R;
	if(start_index == end_index)
		return pa[start_index];
	mid_index = (start_index + end_index)/2;
	max_L = find_max(pa, start_index, mid_index);
	max_R = find_max(pa, mid_index + 1, end_index);
	if(max_L > max_R)
		return max_L;
	return max_R;
}

/*	Search an element in the given array 	*/
/*													search(A, search_element, si, (si+ei/2) - 1) .......... 	if si <= ei and search_element < A[si+ei/2]						

													search(A, search_element, (si+ei/2)+1, ei)	...........		if si <= ei and search_element > A[si+ei/2]

													A[si+ei/2]   ...... if si <= ei and A[si+ei/2] == search_element
search(A, search_element, start_index, end_index) = 
													= -1 	.... if si > ei
*/
int search(int* pa, int search_element, int start_index, int end_index)
{
	int mid_index;

	if(start_index <= end_index)
	{
		mid_index = (start_index + end_index) / 2;
		if(search_element == pa[mid_index])
			return mid_index;
		else if(search_element < pa[mid_index])
			return search(pa, search_element, start_index, mid_index);
		else if(search_element > pa[mid_index])
			return search(pa, search_element, mid_index+1, end_index);
	}

	return (-1);
}

/*	Insertion sort 	*/
void insertion_sort(int* pa, int size)
{
	int i, j, key;
	
	for(j = 1; j < size; ++j)
	{
		key = pa[j];
		i = j - 1;
		while(i > -1 && pa[i] > key)
		{
			pa[i+1] = pa[i];
			i = i - 1;
		}
		pa[i+1] = key;
	}
}