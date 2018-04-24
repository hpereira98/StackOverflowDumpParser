#ifndef __QUERY7_H__
#define __QUERY7_H__

/**
	@file query_7.h
   
	Definição...
*/

#include "toInclude.h"

/** \brief ola.

	sou eu.
	@param *a
	@param *b

	@returns
*/
int sortByNRespostas(Post* a, Post *b);


/** \brief ola.

	sou eu.
	@param key_pointer
	@param post_pointer
	@param info

	@returns TRUE -
	@returns FALSE -
*/
gboolean inserePosts(gpointer key_pointer, gpointer post_pointer, gpointer info);


/** \brief ola.

	sou eu.
	@param *com_post
	@param begin
	@param end

	@returns
*/
LONG_list most_answered_questions_aux(GTree* com_post, int N, Date begin, Date end);


#endif