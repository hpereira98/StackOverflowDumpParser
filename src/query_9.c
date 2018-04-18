#include <query_9.h>

void swapAnswerPID (GTree* com_post, GHashTable* com_postAux, GArray* posts) {
	/*Debugging */ printf("SWAP:\n");
	for (int i=0; i<posts->len; i++){
		Post post = g_array_index(posts, Post, i);
		if (getPostTypeID(post)==2){
			long pid = getPostParentID(post);
			
			Post newPost = getPost(com_post, com_postAux, pid);
			/* Debugging */ //printf("Procurou\n");
			g_array_append_val(posts, newPost);
			g_array_remove_index(posts, i);
			i--;
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

	g_array_sort(posts1, ordena);
	g_array_sort(posts2, ordena);
	
	GArray* aux = g_array_new(FALSE, FALSE, sizeof(long));

	for (int i=0; i < posts1->len; i++) {
		Post post1 = g_array_index(posts1, Post, i);
		for (int j=0; j < posts2->len; j++) {
			Post post2 = g_array_index(posts2, Post, j);
			if (getPostID(post1) == getPostID(post2)){
				long id = getPostID(post1);
				g_array_append_val(aux, id);
			}
		}
	}
	/* Debugging */ printf("Acabou interseção\n");
	LONG_list r = create_list(aux->len);
	for(int i=0; i<aux->len; i++){
		Post post = g_array_index(aux, long, i);
		long id = getPostID(post);

		set_list(r, i, id);
	}

	return r;

}
