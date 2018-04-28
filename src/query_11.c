#include <query_11.h>

void freeMSet(LONG_pair* aux){
	free_long_pair(*aux);
}

GArray* tagsIdToMSet(GArray* tagsId){
	GArray* mSetTagsID = g_array_new(FALSE, FALSE, sizeof(LONG_pair));
	g_array_set_clear_func(mSetTagsID, (GDestroyNotify)freeMSet);

	long id;
	int count, i=0;

	while(i< tagsId->len){
		count = 1;
		id = g_array_index(tagsId, long, i);

		while( id == g_array_index(tagsId, long,++i) )
			count++;
		

		LONG_pair new = create_long_pair(id,count);
		g_array_append_val(mSetTagsID,new);
	}
	printf("TAMANHO mset %d\n", mSetTagsID->len);
	return mSetTagsID;
}


void addTagId(GArray* tagsId, GArray* postTags, GHashTable* com_tags){
	long id;
	Tag tag;

	for(int i = 0; i<postTags->len; i++){
		char* next_tag = g_array_index(postTags, char*, i);
		//printf("Tag usada : %s\n",next_tag );
		tag = g_hash_table_lookup(com_tags, next_tag); 
		
		if(tag){
			id = getTagID(tag);			
			g_array_append_val(tagsId, id);	
		}
										
	}		

}


LONG_list most_used_best_rep_aux(GHashTable* com_user, GHashTable* com_tags, int N, Date begin, Date end){
	int n_Users, size;

	char* date_begin = dateToString(begin);
	char* date_end = dateToString(end);

	GArray* users = usersHashToGArray(com_user);
	
 	g_array_sort(users, (GCompareFunc)sortByRep);

	GArray* tagsId = g_array_new(TRUE, FALSE, sizeof(long));

	if(users->len < N) n_Users = users->len;
	else n_Users = N;
	
	for(int i = 0; i< n_Users; i++){ 
		User user = g_array_index(users, User, i);	
		GArray* user_posts = getUserPosts(user);
		/*********************/// printf("%ld %d %d\n", getUserID(user), getUserReputacao(user),getUserNPosts(user));

		for(int j = 0; j<user_posts->len; j++){
			Post post = g_array_index(user_posts, Post, j);			
			char* data = getPostSimpleDate(post);
			//printf("%s\n",data );

			if(comparaDatas(date_begin, date_end, data) == 0){
				GArray* post_tags = getPostTags(post);
				if(post_tags != NULL) addTagId(tagsId, post_tags, com_tags);		
			}
			free(data);
		}
		//g_array_free(user_posts, TRUE);
	}

	g_array_sort(tagsId, (GCompareFunc)cmpInt);

	GArray* mSetTagsId = tagsIdToMSet(tagsId);
	g_array_sort(mSetTagsId, (GCompareFunc)sortMSet);

	size = selectSize(mSetTagsId->len, N);

	LONG_list r = create_list(size); 	

	for(int i=0; i<size; i++){
		LONG_pair aux = g_array_index(mSetTagsId, LONG_pair, i);	
		set_list(r, i, get_fst_long(aux));	
		/* debugging */ //printf("Pos: %d tagId: %ld numVezesUsada: %ld\n",i,get_fst_long(aux),get_snd_long(aux));
	}
	
	free(date_begin);
	free(date_end);
	g_array_free(users, TRUE);
	g_array_free(tagsId, TRUE);
	g_array_free(mSetTagsId, TRUE);

	//DEBUG(printf("SIZE = %d\n", size));

	return r;

}

