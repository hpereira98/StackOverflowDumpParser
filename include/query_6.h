#ifndef __QUERY6_H__
#define __QUERY6_H__

/**
	@file query_6.h
   
	Definição...
*/

#include "toInclude.h"

/** \brief ola.

	sou eu.
	@param *a
	@param *b

	@returns
*/
int sortByScore(Post *a, Post *b);


/** \brief ola.

	sou eu.
	@param *com_post
	@param begin
	@param end

	@returns
*/
LONG_list most_voted_answers_aux(GTree* com_post, int N, Date begin, Date end);


#endif