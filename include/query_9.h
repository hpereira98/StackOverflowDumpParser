#ifndef __QUERY9_H__
#define __QUERY9_H__

/**
	@file query_9.h
   
	Ficheiro .h com a assinatura da função auxiliar da Query 0
*/

#include "toInclude.h"



/** \brief Função que lista, no máximo, os N IDs dos Posts em que dois utilizadores participam.

	@param *com_user Tabela de Hash dos Users
	@param *com_post Árvore dos Posts
	@param *com_postAux Tabela de Hash auxiliar dos Posts
	@param id1 Identificador do primeiro User
	@param id2 Identificador do segundo User
	@param N Número máximo de IDs a listar

	@returns LONG_list dos IDs em que ambos os Users participam

*/
LONG_list both_participated_aux(GHashTable* com_user, GTree* com_post, GHashTable* com_postAux, long id1, long id2, int N);


#endif
