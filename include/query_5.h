#ifndef __QUERY5_H__
#define __QUERY5_H__

/**
	@file query_5.h
   
	Ficheiro .h com a assinatura da função auxiliar da Query 5.
*/

#include "toInclude.h"

/** \brief Função que dado um ID retorna informação sobre o correspondente User.
	
	@param *com_user Tabela de Hash dos Users
	@param id Identificador do utilizador

	@returns USER (short_bio do User, últimos 10 posts do User).
	@returns NULL caso User com o id dado não exista.
*/
USER get_user_info_aux(GHashTable* com_user, long id);

#endif

