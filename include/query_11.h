#ifndef __QUERY11_H__
#define __QUERY11_H__

/**
	@file query_11.h
   
	Definição...
*/

#include "toInclude.h"


/** \brief ola.

	sou eu.
	@param *a
	@param *b

	@returns
*/
int cmpInt(long *a, long* b);


/** \brief ola.

	sou eu.
	@param *a
	@param *b

	@returns
*/
int sortMSet(LONG_pair* a, LONG_pair* b);


/** \brief ola.

	sou eu.
	@param *a
	@param *b

	@returns
*/
int sortByRep(User* a,User *b);


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