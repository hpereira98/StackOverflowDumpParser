#ifndef __QUERY3_H__
#define __QUERY3_H__

/**
	@file query_3.h
   
	Definição...
*/

#include "toInclude.h"

/** \brief ola.

	sou eu.
	@param key_pointer
	@param post_pointer
	@param info

	@returns TRUE -
	@returns FALSE -
*/
gboolean posts_count(gpointer key_pointer, gpointer post_pointer, gpointer info);


/** \brief ola.

	sou eu.
	@param *com_posts
	@param begin
	@param end

	@returns
*/
LONG_pair total_posts_aux(GTree* com_posts, Date begin, Date end);


#endif