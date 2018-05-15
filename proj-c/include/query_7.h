#ifndef __QUERY7_H__
#define __QUERY7_H__

/**
	@file query_7.h
   
	Ficheiro .h com a assinatura da função auxiliar da Query 7
*/

#include "toInclude.h"

/** \brief Função que, dado um inteiro e um intervalo de datas, retorna uma LONG_list com IDs das perguntas com mais respostas.

	@param *com_post Árvore dos Posts
	@param N número de IDs a devolver
	@param begin Data inicial
	@param end Data final

	@returns LONG_list com IDs das perguntas com mais respostas.
*/
LONG_list most_answered_questions_aux(GTree* com_post, int N, Date begin, Date end);

#endif