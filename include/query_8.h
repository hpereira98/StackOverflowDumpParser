#ifndef __QUERY8_H__
#define __QUERY8_H__

/**
	@file query_8.h
   
	Definição...
*/

#include "toInclude.h"

/** \brief ola.

	sou eu.
	@param key_pointer
	@param post_pointer
	@param info

	@returns 
*/
gboolean word_lookup(gpointer key_pointer, gpointer post_pointer, gpointer info);


/** \brief ola.

	sou eu.
	@param *com_post
	@param *word
	@param N

	@returns
*/
LONG_list contains_word_aux(GTree* com_post, char* word, int N);

#endif