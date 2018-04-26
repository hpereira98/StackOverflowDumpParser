#ifndef __QUERY9_H__
#define __QUERY9_H__

/**
	@file query_9.h
   
	Ficheiro .h da Query 9
*/

#include "toInclude.h"

/** \brief Função que troca Respostas por Perguntas.

	Percorre um array de Posts, removendo as Respostas e anexando no final do array a Pergunta correspondente.
	@param *com_post Árvore dos Posts
	@param *com_postAux Tabela de Hash auxiliar dos Posts
	@param *posts Array dinâmico de Posts

*/
void swapAnswerPID (GTree* com_post, GHashTable* com_postAux, GArray* posts);


/** \brief Função que lista os N IDs dos Posts em que dois utilizadores arbitrários participam.

	@param *com_user Tabela de Hash dos Users
	@param *com_post Árvore dos Posts
	@param *com_postAux Tabela de Hash auxiliar dos Posts
	@param id1 Identificador do primeiro User
	@param id2 Identificador do segundo User
	@param N Número de IDs a listar

	@returns LONG_list dos IDs em que ambos os Users participam

*/
LONG_list both_participated_aux(GHashTable* com_user, GTree* com_post, GHashTable* com_postAux, long id1, long id2, int N);


#endif
