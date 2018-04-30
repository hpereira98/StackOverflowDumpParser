#ifndef __QUERY8_H__
#define __QUERY8_H__

/**
	@file query_8.h
   
	Ficheiro .h com a assinatura da função auxiliar da Query 8
*/

#include "toInclude.h"



/** \brief Função que, dada uma palavra e um inteiro N, retorna uma LONG_list com, no máximo N, IDs de peruntas cujos títulos contenham a palavra dada.

	sou eu.
	@param *com_post Árvore dos Posts
	@param *word Palavra a procurar nos títulos
	@param N Número máximo de IDs a devolver

	@returns LONG_list com, no máximo N, IDs de peruntas cujos títulos contenham a palavra dada.
*/
LONG_list contains_word_aux(GTree* com_post, char* word, int N);

#endif