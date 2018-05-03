#ifndef __QUERY4_H__
#define __QUERY4_H__

/**
	@file query_4.h
   
	Ficheiro .h com a assinatura da função auxiliar da Query 4.
*/

#include "toInclude.h"


/** \brief Função que, dado um intervalo de tempo e uma tag, retorna uma LONG_list contendo os IDs de perguntas, feitas no intervalo, que contenham essa  tag.

	@param *com_post Árvore dos Posts
	@param *com_tags Tabela de Hash das tags
	@param tagName Tag a procurar
	@param begin Data inicial
	@param end Data final

	@returns LONG_list contendo os ids das perguntas que utilizaram a tag passada como argumento, ordenos por cornologia inversa.
*/
LONG_list questions_with_tag_aux(GTree* com_post, GHashTable* com_tags, char* tagName, Date begin, Date end);

#endif