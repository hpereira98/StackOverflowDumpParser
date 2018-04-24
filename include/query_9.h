#ifndef __QUERY9_H__
#define __QUERY9_H__

/**
	@file query_9.h
   
	Definição...
*/

#include "toInclude.h"

/** \brief ola.

	sou eu.
	@param *a
	@param *b

	@returns
*/
int sortByDate(Post* a, Post* b);


/** \brief ola.

	sou eu.
	@param *com_post
	@param *com_postAux
	@param *posts

*/
void swapAnswerPID (GTree* com_post, GHashTable* com_postAux, GArray* posts);


/** \brief ola.

	sou eu.
	@param *com_user
	@param *com_post
	@param *com_postAux
	@param id1
	@param id2
	@param N

*/
LONG_list both_participated_aux(GHashTable* com_user, GTree* com_post, GHashTable* com_postAux, long id1, long id2, int N);


#endif
