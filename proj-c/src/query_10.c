#include <query_10.h>

/*
 Função que calcula a pontuação de uma resposta.
*/

double answer_score(int score, int rep, int comments) {
	return ((score*0.65) + (rep*0.25) + (comments*0.1)); 
}

/*
 Função que guarda e atualiza o ID da Resposta com maior pontuação para a Pergunta escolhida,
 à medida que a àrvore dos posts é atravessada.
*/
gboolean bestAnswer(gpointer key_pointer, gpointer post_pointer, gpointer info) {
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
		RESULT(
			printf("postID: %ld não existe, ou então nao corresponde a uma Pergunta.\n",id);
		)

		return -1;
	}	

	long parentId = id;
	double max = 0;
	long answerId = -1;
	char *data = getPostDate(post);

	void* info[4] = {&parentId, &max, &answerId, data};

	g_tree_foreach(com_post, (GTraverseFunc)bestAnswer, info);

	free(data);

	RESULT(
		printf("ID melhor resposta: %ld\n", answerId);
	)
	
	return answerId;
}
