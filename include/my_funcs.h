#ifndef __MYFUNCS_H__
#define __MYFUNCS_H__

/**
	@file my_funcs.h
   
	Definição...
*/

#include "toInclude.h"

/** \brief ola.

	sou eu.
	@param a
	@param b

	@returns
*/
int cmpTreeKey(PostKey a, PostKey b);


/** \brief ola.

	sou eu.
	@param date

	@returns
*/
char* dateToString(Date date);


/** \brief ola.

	sou eu.
	@param *begin
	@param *end
	@param *post_date

	@returns
*/
int comparaDatas(char* begin, char* end, char* post_date);


/** \brief ola.

	sou eu.
	@param *tags
	@param *i

	@returns
*/
char* nextTag(char* tags, int *i);

#endif
