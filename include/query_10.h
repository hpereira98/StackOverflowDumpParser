#ifndef __QUERY10_H__
#define __QUERY10_H__

/**
	@file query_10.h
   
	Ficheiro .h da Query 10
*/

#include "toInclude.h"

/** \brief Função que calcula a pontuação de uma resposta.
	
	Calcula a pontuação a partir de uma média ponderada.
	
	@param score Score do Post (UpVotes-DownVotes)
	@param rep Reputação do criador do Post
	@param comments Número de comentários do Post

	@returns Pontuação da resposta
*/
double answer_score (int score, int rep, int comments);


/** \brief Função que itera a Árvore dos Posts, guardando o ID da Resposta com maior pontuação para a Pergunta escolhida.

	@param key_pointer Apontador para a chave
	@param post_pointer Apontador para o Post
	@param info Informações a guardar entre iterações

	@returns TRUE - quando a data do Post é anterior à data da Pergunta
	@returns FALSE - enquanto a data do Post for posterior à data da Pergunta 
*/
gboolean bestAnswer (gpointer key_pointer, gpointer post_pointer, gpointer info);


/** \brief Função que, dado um ID de uma Pergunta, devolve o ID da melhor Resposta.
	
	A pontuação de uma resposta é calculada através da média ponderada explícita na função answer_score.
	
	@param *com_post Árvore dos Posts
	@param *com_postAux Tabela de Hash auxiliar dos Posts
	@param id Identificador da Pergunta

	@returns Identificador da melhor Resposta
*/
long better_answer_aux(GTree* com_post, GHashTable* com_postAux, long id);

#endif
