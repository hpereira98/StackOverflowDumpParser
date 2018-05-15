#ifndef __QUERY6_H__
#define __QUERY6_H__

/**
	@file query_6.h
   
	Ficheiro .h com a assinatura da função auxiliar da Query 6.
*/

#include "toInclude.h"

/** \brief Função que, dado um inteiro e um intervalo de datas, retorna uma LONG_list com IDs das respostas com mais votos.

	@param *com_post Árvore dos Posts
	@param begin Data inicial
	@param end Data final

	@returns LONG_list com IDs das respostas com mais votos.
*/
LONG_list most_voted_answers_aux(GTree* com_post, int N, Date begin, Date end);


#endif