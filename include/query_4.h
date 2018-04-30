#ifndef __QUERY4_H__
#define __QUERY4_H__

/**
	@file query_4.h
   
	Ficheiro .h com a assinatura da função auxiliar da Query 4
*/

#include "toInclude.h"


/** \brief Função que, dado um intervalo de tempo e uma tag, retorna uma LONG_list contendo os IDs de perguntas, feitas no intervalo, que contenham essa  tag.

	@param *com_post 
	@param *tag
	@param begin
	@param end

	@returns
*/
LONG_list questions_with_tag_aux(GTree* com_post, GHashTable* com_tags, char* tagName, Date begin, Date end);

#endif