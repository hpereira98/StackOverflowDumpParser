#include <query_11.h>

/* 
 Função para libertar o espaco alocado no GArray de LONG_pairs.
*/
void freeMSet(LONG_pair* aux){
	free_long_pair(*aux);
}

/* 
 Função para adicionar um LONG_pair (tagID, num_ocorrências) a um GArray.
*/
void addToMSet(long tagID, int* ocur, GArray* mSetTagsID){

	LONG_pair new = create_long_pair(tagID, *ocur);

	g_array_append_val(mSetTagsID,new);
}

/*
 Função que percorre um GArray de tagsID ordenado e devolve um GArray composto por pares da forma 
 (tagID,numOcorrencias).
*/
GArray* tagsIdToMSet(GHashTable* tagsId){
	GArray* mSetTagsID = g_array_new(FALSE, FALSE, sizeof(LONG_pair));
	g_array_set_clear_func(mSetTagsID, (GDestroyNotify)freeMSet);

	g_hash_table_foreach(tagsId, (GHFunc)addToMSet, mSetTagsID);

	return mSetTagsID;
}

/*
 Função que adiciona o ID das tags usadas num posts a um GArray
*/
void addTagId(GHashTable* tagsId, GArray* postTags, GHashTable* com_tags){

	for(int i = 0; i<postTags->len; i++){
		long next_tag = g_array_index(postTags, long, i);

		int* num_ocor =	g_hash_table_lookup(tagsId , (gpointer)next_tag);

		if(!num_ocor) {
			int* ocor = malloc(sizeof(int));
			*ocor = 1;

			g_hash_table_insert(tagsId, (gpointer)next_tag, ocor);
		}
		else (*num_ocor)++; 
	}
										
}		




LONG_list most_used_best_rep_aux(GHashTable* com_user, GHashTable* com_tags, int N, Date begin, Date end){
	int n_Users, size, i, j;

	char* date_begin = dateToString(begin);
	char* date_end = dateToString(end);

	GArray* users = usersHashToGArray(com_user);

	if(users->len <= N) 
		n_Users = users->len;
	else{
		n_Users = N;
		g_array_sort(users, (GCompareFunc)sortByRep);
	}

 	GHashTable* tagN_Ocur = g_hash_table_new_full(g_direct_hash,g_direct_equal, NULL, free);
	
	for( i = 0; i < n_Users; i++){ 
		User user = g_array_index(users, User, i);
		GArray* user_posts = getUserPosts(user);

		if(user_posts){
			for( j = 0; j < user_posts->len; j++){
				Post post = g_array_index(user_posts, Post, j);			
				char* data = getPostSimpleDate(post);

				if(comparaDatas(date_begin, date_end, data) == 0){
					GArray* post_tags = getPostTags(post);
					if(post_tags != NULL) addTagId(tagN_Ocur, post_tags, com_tags);		
				}
				free(data);
			}
		}
	}

	GArray* mSetTagsId = tagsIdToMSet(tagN_Ocur);
	g_array_sort(mSetTagsId, (GCompareFunc)sortMSet);

	size = selectSize(mSetTagsId->len, N);

	LONG_list result = create_list(size); 	

	for( i=0; i<size; i++){
		LONG_pair aux = g_array_index(mSetTagsId, LONG_pair, i);	
		set_list(result, i, get_fst_long(aux));	

		RESULT(
			printf("%d -- tagId: %ld numVezesUsada: %ld\n", i, get_fst_long(aux), get_snd_long(aux));
		)
	}
	
	free(date_begin);
	free(date_end);

	g_array_free(users, TRUE);
	g_array_free(mSetTagsId, TRUE);
	
	g_hash_table_destroy(tagN_Ocur);
	

	return result;

}

