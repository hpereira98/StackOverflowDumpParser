#ifndef __QUERY4_H__
#define __QUERY4_H__

/**
	@file query_4.h
   
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
gboolean adicionaComTag(gpointer key_pointer, gpointer post_pointer, gpointer info);


/** \brief ola.

	sou eu.
	@param *com_post
	@param *tag
	@param begin
	@param end

	@returns
*/
LONG_list questions_with_tag_aux(GTree* com_post, char* tag, Date begin, Date end);

#endif