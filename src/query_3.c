#include <query_3.h>

gboolean posts_count(gpointer key, gpointer post_pointer, gpointer info){
	int dateCheck;
	
	Post post = (Post) post_pointer;
	char* post_date = getPostSimpleDate(post);

	char* date_begin = ((char**)(info))[0];
	char* date_end = ((char**)(info))[1];

	int* numQuestions = ((int**)(info))[2];
	int* numAnswers = ((int**)(info))[3];
	
	dateCheck = comparaDatas(date_begin, date_end, post_date);

	if(dateCheck == -1) return TRUE; // parar a travessia caso tenha sido passada a data inferior

	if(dateCheck == 0){
		if(getPostTypeID(post)==1) (*numQuestions)++;
			else if(getPostTypeID(post)==2) (*numAnswers)++;
	}

	return FALSE;
}


LONG_pair total_posts_aux(GTree* com_posts, Date begin, Date end){

	char* date_begin = dateToString(begin);
	char* date_end = dateToString(end);

	int numQuestions=0, numAnswers=0;

	void* info[4] = {date_begin,date_end, &numQuestions, &numAnswers};
	
	g_tree_foreach(com_posts, (GTraverseFunc)posts_count, info);
	
	LONG_pair totalPost = create_long_pair(numQuestions,numAnswers);
	
	return totalPost;
	
}
