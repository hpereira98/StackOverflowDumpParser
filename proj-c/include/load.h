#ifndef __LOAD_H__
#define __LOAD_H__

/**
	@file load.h
   
	Ficheiro .h para o Load dos ficheiros XML
*/

#include "toInclude.h"


/** \brief Função que carrega a informação dos ficheiros XML do dump do Stack Overflow para as estruturas definidas.

	@param *com_user Tabela de Hash dos Users
	@param *com_post Árvore Binária dos Posts
	@param *com_postAux Tabela de Hash auxiliar dos Posts
	@param *com_tags Tabela de Hash das Tags
	@param *dump_path Caminho da pasta com os ficheiros XML
	
*/
void load_aux(GHashTable* com_user, GTree* com_post, GHashTable* com_postAux, GHashTable* com_tags, char* dump_path);

/** \brief Função que inicializa a estrutura TAD_community.

	Aloca o espaço necessário à inicialização das estruturas por nós definidas, que são parte da estrutura global para tratamento da informação.

*/
TAD_community init();


#endif
