#include <query_3.h>

gboolean posts_count(gpointer key, gpointer post_pointer, gpointer info){
	
	Post post = (Post) post_pointer;
	Date post_date = getPostDate(post);

	Date begin = ((Date*)(info))[0];
	Date end = ((Date*)(info))[1];

	int* numQuestions = ((int**)(info))[2];
	int* numAnswers = ((int**)(info))[3];
	
	if(comparaDatas(begin, end, post_date) == 0){
		if(getPostTypeID(post)==1) (*numQuestions)++;
			else if(getPostTypeID(post)==2) (*numAnswers)++;
	}

	else if(comparaDatas(begin, end, post_date) == -1) return TRUE;

	return FALSE;
}


LONG_pair total_posts_aux(GTree* com_posts, Date begin, Date end){

	int *numQuestions = malloc(sizeof(int));
	int *numAnswers = malloc(sizeof(int));
	*numQuestions = *numAnswers = 0;

	void* info[4] = {begin, end, numQuestions, numAnswers};
	
	g_tree_foreach(com_posts, (GTraverseFunc)posts_count, info);
	LONG_pair totalPost = create_long_pair(*numQuestions,*numAnswers);

	return totalPost;
	
}
