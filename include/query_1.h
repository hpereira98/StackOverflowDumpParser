#ifndef __QUERY1_H__
#define __QUERY1_H__

/**
	@file query_1.h
   
	Definição...
*/

#include "toInclude.h"

/** \brief ola.

	sou eu.
	@param *com_post teste1
	@param *com_postAux teste2
	@param *com_user teste3
	@param id teste4

	@returns
*/
STR_pair info_from_post_aux(GTree* com_post, GHashTable* com_postAux, GHashTable* com_user, long id);

#endif