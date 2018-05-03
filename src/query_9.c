#include <query_9.h>

/*
 Função que insere a informação contida num GArray de Posts numa tabela de Hash cuja chave é o ID de um post
 (ou parentID caso seja uma resposta) e o valor é um apontador sem significado, que apenas permite identificar
 a existência da chave aquando da procura na tabela de Hash resultado.
*/
GHashTable* gArrayToHash(GArray* toConvert){
	long id; 
	Post post;
	GHashTable* result = g_hash_table_new_full(g_direct_hash, g_direct_equal, NULL, free);
	
	for(int i=0; i < toConvert->len; i++){		
		post = g_array_index(toConvert, Post, i);

		int* value = malloc(sizeof(int));
		*value = 1;

		if(getPostTypeID(post)==2)
			id = getPostParentID(post);
		else 
			id = getPostID(post);

		g_hash_table_insert(result, (gpointer)id, value);
	}
	return result;	
}

/*
 Função que percorre o GArray de Posts de um User e troca todas as ocorrências de respostas
 pela respetiva pergunta.
*/
void swapAnswerPID(GTree* com_post, GHashTable* com_postAux, GArray* posts) {
	Post post, newPost; 
	long parentId;

	for (int i=0; i<posts->len; i++){
		post = g_array_index(posts, Post, i);
		if (getPostTypeID(post)==2){
			parentId = getPostParentID(post);
			newPost = getPost(com_post, com_postAux, parentId);

			g_array_remove_index(posts, i);
			if(newPost != NULL) g_array_insert_val(posts, i, newPost); 
		}
	}
}

LONG_list both_participated_aux(GHashTable* com_user, GTree* com_post, GHashTable* com_postAux, long id1, long id2, int N){	
	Post post;
	GArray* toConvert;
	GArray* toTraverse;
	long id; 
	int size;

	User user1 = getUser(com_user, id1); 
	User user2 = getUser(com_user, id2); 

	if(!user1 || !user2) return NULL;

	GArray* posts1 = getClonedUserPosts(user1);

	if(!posts1) return NULL;

	GArray* posts2 = getClonedUserPosts(user2);
	
	if(!posts2){ 
		g_array_free(posts1, TRUE);
		return NULL;
	}

	if(posts1->len < posts2->len){
		toConvert = posts2;
		toTraverse = posts1;
	}
	else{
		toConvert = posts1;
		toTraverse = posts2;
	}
	
	swapAnswerPID(com_post, com_postAux, toTraverse);
	g_array_sort(toTraverse, (GCompareFunc)sortByDate);

	GHashTable* toSearch = gArrayToHash(toConvert);

	GArray* result_aux = g_array_new(FALSE, FALSE, sizeof(long));

	for (int i=0; i < toTraverse->len; i++) {
		post = g_array_index(posts1, Post, i);
		id = getPostID(post);
		
		int* check = g_hash_table_lookup(toSearch, (gpointer)id);

		if(check)
			g_array_append_val(result_aux,id);
	}

	size = selectSize(result_aux->len,N);

	LONG_list result = create_list(size);

	for(int i=0; i<size; i++){
		id = g_array_index(result_aux, long, i);
		set_list(result, i, id);

		SHOW_RESULT(
			printf("%d --  postId: %ld\n", i+1, id);
		)	
	}

	g_array_free(result_aux, TRUE);	
	g_array_free(posts1, TRUE);
	g_array_free(posts2, TRUE);
	g_hash_table_destroy(toSearch);

	return result;

}
