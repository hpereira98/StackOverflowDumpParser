#include <query_9.h>

int sortByDate(Post a, Post b){
	char* date_a = getPostDate(a);
	char* date_b = getPostDate(b);

	return strcmp(date_b, date_a);
}


void swapAnswerPID (GTree* com_post, GHashTable* com_postAux, GArray* posts) {

	for (int i=0; i<posts->len; i++){
		Post post = g_array_index(posts, Post, i);
		if (getPostTypeID(post)==2){
			long pid = getPostParentID(post);
			Post newPost = getPost(com_post, com_postAux, pid);

			g_array_insert_val(posts, i, newPost); // acho que assim os postsAux não encontrados são mais
			g_array_remove_index(posts, i+1); // temos a certeza que existe i+1 porque foi o que fizemos shift
		}
	}
}

LONG_list both_participated_aux(GHashTable* com_user, GTree* com_post, GHashTable* com_postAux, long id1, long id2, int N){
	
	User user1 = g_hash_table_lookup(com_user, &id1); 
	User user2 = g_hash_table_lookup(com_user, &id2);

	GArray *posts1 = getClonedUserPosts(user1);
	GArray *posts2 = getClonedUserPosts(user2);
	
	swapAnswerPID(com_post, com_postAux, posts1);
	swapAnswerPID(com_post, com_postAux, posts2);

	for(int i = 0; i < posts1->len; i++){ // dá segf ao aceder a um post
		Post post = g_array_index(posts1, Post, i);

		printf("%ld\n", getPostID(post));
	}

	/* Debugging */ printf("Acabou swaps\n");
	g_array_sort(posts1, (GCompareFunc)sortByDate);
	//g_array_sort(posts2, ordena);

	/* Debugging */ printf("Acabou ordenação\n");
	GArray* aux = g_array_new(FALSE, FALSE, sizeof(long));

	for (int i=0; i < posts1->len; i++) {
		Post post1 = g_array_index(posts1, Post, i);
		for (int j=0; j < posts2->len; j++) {
			Post post2 = g_array_index(posts2, Post, j);
			if (getPostID(post1) == getPostID(post2)){
				long id = getPostID(post1);
				g_array_append_val(aux, id);
				g_array_remove_index(posts2, j); // remover do segundo array para não voltar a passar por ele
			}
		}
	}

	/* Debugging */ printf("Acabou interseção\n");
	LONG_list r = create_list(aux->len);
	for(int i=0; i<aux->len; i++){
		long id = g_array_index(aux, long, i);

		set_list(r, i, id);
	}

	return r;

} 