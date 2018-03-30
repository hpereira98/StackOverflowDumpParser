#include <query_10.h>

// QUERY 10

double answer_score (int score, int rep, int vots, int comments) {
	return ( (score*0.45)+(rep*0.25)+(vots*0.2)+(comments*0.1));
}

void bestAnswer (gpointer key_pointer, gpointer post_pointer, gpointer info) {
	struct Post* post = (struct Post*)post_pointer;
	int* parentId = ((int**)info)[0];
	double* max = ((double**)info)[1];
	int* answerId = ((int**)info)[2];
	double score=0;

	if (post->type_id == 2 && post->parent_id == *parentId) {
		score=answer_score(post->score, post->owner_rep, (post->n_upvotes)-(post->n_downvotes), post->n_comments);
		if (score>(*max)) {
			*max=score;
			*answerId=post->id;
		}
	}
}

long better_answer(TAD_community com, long id) {

	int* parentId = malloc(sizeof(int));
	*parentId=id;

	int *max = malloc(sizeof(int));
	*max=0;

	int *answerId = malloc(sizeof(int));

	void* info[3] = {(void*)parentId, (void*)max, (void*)answerId};

	g_hash_table_foreach(com->post, bestAnswer, info);

	return (long)*answerId;
}
