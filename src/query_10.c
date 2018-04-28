#include <query_10.h>


double answer_score (int score, int rep, int comments) {
	return ((score*0.65) + (rep*0.25) + (comments*0.1)); 
}

gboolean bestAnswer (gpointer key_pointer, gpointer post_pointer, gpointer info) {
	Post post = (Post)post_pointer;
	double score=0;

	long* parentId = ((long**)info)[0];
	double* max = ((double**)info)[1];
	long* answerId = ((long**)info)[2];
	char* data = ((char**)info)[3];
	char* post_date = getPostDate(post);

	if(strcmp(post_date, data) < 0){
		free(post_date);
		return TRUE;
	}
	
	if( getPostTypeID(post) == 2 && getPostParentID(post) == *parentId){
		score = answer_score(getPostScore(post), getPostOwnerRep(post), getPostNComments(post));

		if (score > *max) {	
			*max = score;
			*answerId = getPostID(post);
		}

	}

	free(post_date);

	return FALSE;
}

long better_answer_aux(GTree* com_post, GHashTable* com_postAux, long id){
	
	Post post = getPost(com_post,com_postAux,id);

	if (!post || getPostTypeID(post) != 1){
		printf("Post with ID %li is not a question\n",id);
		return -2;
	}	

	long parentId = id;
	double max = 0;
	long answerId = -2;
	char *data = getPostDate(post);

	void* info[4] = {&parentId, &max, &answerId, data};

	g_tree_foreach(com_post, (GTraverseFunc)bestAnswer, info);

	if(answerId == -2)
		//printf("The post with ID %li has no answers.\n",id);

	free(data);
	
	return answerId;
}
