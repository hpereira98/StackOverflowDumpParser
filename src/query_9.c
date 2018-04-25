#include <query_9.h>


int sortByDate(Post* a, Post* b){
	char* date_a = getPostDate(*a);
	char* date_b = getPostDate(*b);
	
	return strcmp(date_b, date_a);
}

void swapAnswerPID (GTree* com_post, GHashTable* com_postAux, GArray* posts) {
	Post post, newPost; 
	/* Debugging */ int nao_encontrados = 0;

	for (int i=0; i<posts->len; i++){
		post = g_array_index(posts, Post, i);
		if (getPostTypeID(post)==2){
			long pid = getPostParentID(post);
			newPost = getPost(com_post, com_postAux, pid);

			g_array_remove_index(posts, i);
			if(newPost != NULL) g_array_insert_val(posts, i, newPost); // acho que assim os postsAux não encontrados são mais
			else nao_encontrados++;
		}
	}
	/* Debugging */ printf("Num respostas sem pergunta: %d\n",nao_encontrados );
}

LONG_list both_participated_aux(GHashTable* com_user, GTree* com_post, GHashTable* com_postAux, long id1, long id2, int N){
	GArray* aux = g_array_new(FALSE, FALSE, sizeof(long));
	Post post1, post2;
	long id; 
	int size;

	User user1 = g_hash_table_lookup(com_user, &id1); 
	User user2 = g_hash_table_lookup(com_user, &id2);

	if(!user1 || !user2) return NULL;

	GArray *posts1 = getClonedUserPosts(user1);
	GArray *posts2 = getClonedUserPosts(user2);
	
	swapAnswerPID(com_post, com_postAux, posts1);
	swapAnswerPID(com_post, com_postAux, posts2);

	g_array_sort(posts1, (GCompareFunc)sortByDate);

	for (int i=0; i < posts1->len; i++) {
		post1 = g_array_index(posts1, Post, i);
		for (int j=0; j < posts2->len; j++) {
			post2 = g_array_index(posts2, Post, j);
			if (getPostID(post1) == getPostID(post2)){
				id = getPostID(post1);
				g_array_append_val(aux, id);
				g_array_remove_index(posts2, j); // remover do segundo array para não voltar a passar por ele
			}
		}
	}

	if(aux->len < N) size = aux->len;
	else size = N;

	LONG_list result = create_list(size);

	for(int i=0; i<size; i++){
		id = g_array_index(aux, long, i);
		set_list(result, i, id); 
		/**********/ printf("Post: %d postID: %ld Data: %s\n",i,id, getPostDate(getPost(com_post, com_postAux, id)));
	}

	return result;

}
