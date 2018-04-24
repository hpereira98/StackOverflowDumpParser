#ifndef __LOAD_H__
#define __LOAD_H__

/**
	@file load.h
   
	Definição...
*/

#include "toInclude.h"


/** \brief ola.

	sou eu.
	@param *com_user
	@param *com_post
	@param *com_postAux
	@param *com_tags
	@param *dump_path
	
*/
void load_aux(GHashTable* com_user, GTree* com_post, GHashTable* com_postAux, GHashTable* com_tags, char* dump_path);

/** \brief ola.

	sou eu.

*/
TAD_community init();


#endif
