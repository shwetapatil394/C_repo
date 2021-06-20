/*	Declaration for own assert function	*/

#ifndef _CPA_ASSERT_H
#define _CPA_ASSERT_H

#include <stdio.h>

#define cpa_assert(cond)	do\
							{\
								if(!cond)\
								{\
									fprintf(stderr, "%s:%d:"#cond" failed\n", __FILE__, __LINE__);\
									exit(EXIT_FAILURE);\
								}\
							}while(0)\

#endif	/*	_CPA_ASSERT_H	*/