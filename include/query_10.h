#ifndef __QUERY10_H__
#define __QUERY10_H__

#include <toInclude.h>

/**
	@file query_10.h
   
	Ficheiro .h com a assinatura da função auxiliar da Query 10
*/


gboolean bestAnswer (gpointer key_pointer, gpointer post_pointer, gpointer info);


/** \brief Função que, dado um ID de uma pergunta, devolve o ID da melhor resposta.
	
	A pontuação de uma resposta é calculada através da média ponderada explícita na função answer_score.
	
	@param *com_post Árvore dos Posts
	@param *com_postAux Tabela de Hash auxiliar dos Posts
	@param id Identificador da Pergunta

	@returns Identificador da melhor resposta, ou -1 caso a pergunta não exista ou não tenha nenhuma resposta.
*/
long better_answer_aux(GTree* com_post, GHashTable* com_postAux, long id);

#endif
