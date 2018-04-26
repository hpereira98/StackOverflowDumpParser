#ifndef __QUERY11_H__
#define __QUERY11_H__

/**
	@file query_11.h
   
	Definição...
*/

#include "toInclude.h"


/** \brief ola.

	sou eu.
	@param key_pointer
	@param user_pointer
	@param info

	@returns
*/
void insereUsers(gpointer key_pointer, gpointer user_pointer, gpointer info);


/** \brief ola.

	sou eu.
	@param *tagsId

	@returns 
*/
GArray* tagsIdToMSet(GArray* tagsId);


/** \brief ola.

	sou eu.
	@param *tagsId
	@param *postTags
	@param *com_tags

*/
void addTagId(GArray* tagsId, GArray* postTags, GHashTable* com_tags);


/** \brief ola.

	sou eu.
	@param *com_user
	@param *com_post
	@param N
	@param begin
	@param end

	@returns
*/
LONG_list most_used_best_rep_aux(GHashTable* com_user, GHashTable* com_tags, int N, Date begin, Date end);

#endif