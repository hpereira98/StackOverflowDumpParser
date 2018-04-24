#ifndef __QUERY10_H__
#define __QUERY10_H__

/**
	@file query_10.h
   
	Definição...
*/

#include "toInclude.h"

/** \brief ola.

	sou eu.
	@param score
	@param rep
	@param comments

	@returns
*/
double answer_score (int score, int rep, int comments);


/** \brief ola.

	sou eu.
	@param key_pointer
	@param post_pointer
	@param info

	@returns TRUE -
	@returns FALSE -
*/
gboolean bestAnswer (gpointer key_pointer, gpointer post_pointer, gpointer info);


/** \brief ola.

	sou eu.
	@param *com_post
	@param *com_postAux
	@param id

	@returns
*/
long better_answer_aux(GTree* com_post, GHashTable* com_postAux, long id);

#endif
