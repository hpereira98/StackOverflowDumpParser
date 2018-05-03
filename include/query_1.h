#ifndef __QUERY1_H__
#define __QUERY1_H__

/**
	@file query_1.h
   
	Ficheiro .h com a assinatura da função auxiliar da Query 1.
*/

#include "toInclude.h"

/** \brief Função que, dado o ID de um Post, devolve um Par com o título da pergunta correspondente ao Post e o nome do User.

	@param *com_post Árvore dos Posts
	@param *com_postAux Tabela de Hash auxiliar dos Posts
	@param *com_user Tabela de Hash dos Users
	@param id Identificador do Post

	@returns Par de Strings com o título da pergunta correspondente e nome do User que a criou.
*/
STR_pair info_from_post_aux(GTree* com_post, GHashTable* com_postAux, GHashTable* com_user, long id);

#endif
