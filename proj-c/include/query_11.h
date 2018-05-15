#ifndef __QUERY11_H__
#define __QUERY11_H__

/**
	@file query_11.h
   
	Ficheiro .h com a assinatura da função auxiliar da Query 11.
*/

#include "toInclude.h"

/** \brief Função que lista as tags mais usadas, pelos N utilizadores com melhor reputação, durante um dado intervalo de tempo.

	@param *com_user Tabela de Hash dos Users
	@param *com_post Àrvore dos Posts
	@param N Número de utilizadores a considerar na resposstas
	@param begin Data inicial
	@param end Data final

	@returns LONG_list com as N tags mais usadas conforme os critérios estabelecidos.
*/
LONG_list most_used_best_rep_aux(GHashTable* com_user, GHashTable* com_tags, int N, Date begin, Date end);

#endif