#include <query_10.h>


double answer_score (int score, int rep, int vots, int comments) {
	return ( (score*0.45)+(rep*0.25)+(vots*0.2)+(comments*0.1));
}

void bestAnswer (gpointer key_pointer, gpointer post_pointer, gpointer info) {
	Post post = (Post)post_pointer;
	int* parentId = ((int**)info)[0];
	double* max = ((double**)info)[1];
	int* answerId = ((int**)info)[2];
	double score=0;
	int postVots = getPostNUpVotes(post) - getPostNDownVotes(post);

	if( getPostTypeID(post) == 2 && getPostParentID(post) == *parentId) {
		score=answer_score(getPostScore(post), getPostOwnerRep(post),postVots, getPostNComments(post));
		if (score>(*max)) {
			*max=score;
			*answerId=getPostID(post);
		}
	}
}

long better_answer_aux(GHashTable* com_post, long id){

	int* parentId = malloc(sizeof(int));
	*parentId=id;

	int *max = malloc(sizeof(int));
	*max=0;

	int *answerId = malloc(sizeof(int));

	void* info[3] = {(void*)parentId, (void*)max, (void*)answerId};

	g_hash_table_foreach(com_post, bestAnswer, info);

	return (long)*answerId;
}
