#ifndef __QUERY2_H__
#define __QUERY2_H__

/**
	@file query_2.h
   
	Definição...
*/

#include "toInclude.h"

/** \brief ola.

	sou eu.
	@param *a
	@param *b

	@returns
*/
int sortByNPosts(User* a,User *b);


/** \brief ola.

	sou eu.
	@param key_pointer
	@param user_pointer
	@param info
*/
void appendUserToArray (gpointer key_pointer, gpointer user_pointer, gpointer info);


/** \brief ola.

	sou eu.
	@param *com_user
	@param N

	@returns
*/
LONG_list top_most_active_aux(GHashTable* com_user, int N);


#endif