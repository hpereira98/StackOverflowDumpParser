#include "query_3.h"

void posts_count(gpointer key, gpointer post_pointer, gpointer info){
	
	Post post = (Post) post_pointer;
	Date post_date = getPostDate(post);

	Date begin = ((Date*)(info))[0];
	Date end = ((Date*)(info))[1];

	int* numQuestions = ((int**)(info))[2];
	int* numAnswers = ((int**)(info))[3];
	
	if(comparaDatas(post_date,begin)==1 && comparaDatas(end,post_date)==1){
		if(getPostTypeID(post)==1) (*numQuestions)++;
			else if(getPostTypeID(post)==2) (*numAnswers)++;
	}
}


LONG_pair total_posts_aux(GHashTable* com_posts, Date begin, Date end){

	int *numQuestions = malloc(sizeof(int));
	int *numAnswers = malloc(sizeof(int));
	*numQuestions = *numAnswers = 0;

	void* info[4] = {begin, end, numQuestions, numAnswers};
	
	g_hash_table_foreach(com_posts,posts_count,info);
	LONG_pair totalPost = create_long_pair(*numQuestions,*numAnswers);

	return totalPost;
	
}
