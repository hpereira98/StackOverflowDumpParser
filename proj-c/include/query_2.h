#ifndef __QUERY2_H__
#define __QUERY2_H__

/**
	@file query_2.h
   
	Ficheiro .h com a assinatura da função auxiliar da Query 2.
*/

#include "toInclude.h"

/** \brief Função que lista os utilizadores mais ativos da comunidade.

	@param *com_user Tabela de Hash dos Utilizadores
	@param N Número de utilizadores a listar

	@returns LONG_list dos N utilizadores mais ativos.
*/
LONG_list top_most_active_aux(GHashTable* com_user, int N);


#endif
