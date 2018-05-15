#include <query_3.h>

/*
 Função que identifica o tipo de Post a ser processado e incrementa o respetivo contador 
 do número total de Posts do seu tipo.
*/
gboolean posts_count(gpointer key, Post post, gpointer info){
	char* post_date = getPostSimpleDate(post);
	char* date_begin = ((char**)(info))[0];
	char* date_end = ((char**)(info))[1];

	int* numQuestions = ((int**)(info))[2];
	int* numAnswers = ((int**)(info))[3];
	
	int dateCheck = comparaDatas(date_begin, date_end, post_date);

	free(post_date);

	if(dateCheck == -1) return TRUE; 

	if(dateCheck == 0){
		if(getPostTypeID(post)==1) (*numQuestions)++;
			else (*numAnswers)++;
	}

	return FALSE;
}


LONG_pair total_posts_aux(GTree* com_posts, Date begin, Date end){

	char* date_begin = dateToString(begin);
	char* date_end = dateToString(end);

	int numQuestions=0, numAnswers=0;

	void* info[4] = {date_begin, date_end, &numQuestions, &numAnswers};
	
	g_tree_foreach(com_posts, (GTraverseFunc)posts_count, info);
	
	LONG_pair totalPosts = create_long_pair(numQuestions, numAnswers);

	RESULT(
		printf("Num Perguntas: %d -- Num Respostas: %d\n", numQuestions, numAnswers);
	)
	
	free(date_begin);
	free(date_end);
	
	return totalPosts;
	
}
