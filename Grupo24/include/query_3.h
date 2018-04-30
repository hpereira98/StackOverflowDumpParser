#ifndef __QUERY3_H__
#define __QUERY3_H__

/**
	@file query_3.h
   
	Ficheiro .h com a assinatura da função auxiliar da Query 3
*/

#include "toInclude.h"


/** \brief Função que, dado um intervalo de tempo, conta quantas perguntas e quantas respostas foram feitas durante o mesmo.

	@param *com_posts Árvore dos Posts
	@param begin Data inicial
	@param end Data final

	@returns LONG_pair cuja primeira componente corresponde ao número de perguntas, e a segunda ao número de respostas.
*/
LONG_pair total_posts_aux(GTree* com_posts, Date begin, Date end);


#endif