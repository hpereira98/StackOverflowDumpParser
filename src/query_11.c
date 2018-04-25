#include <query_11.h>

int cmpInt(long *a, long* b){
	return *a - *b;
}

int sortMSet(LONG_pair* a, LONG_pair* b){
	long ocur_a = get_snd_long(*a);
	long ocur_b = get_snd_long(*b);

	return (-1) * cmpInt(&ocur_a, &ocur_b);
}

int sortByRep(User* a,User *b){
	int rep_a = getUserReputacao(*a);
	int rep_b = getUserReputacao(*b);
	
	return rep_b - rep_a;
}

void insereUsers(gpointer key_pointer, gpointer user_pointer, gpointer info){
	User user = (User)user_pointer;
	GArray* users = (GArray*)info;

	g_array_append_val(users, user);

}

GArray* tagsIdToMSet(GArray* tagsId){
	GArray* mSetTagsID = g_array_new(FALSE, FALSE, sizeof(LONG_pair));
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

	return mSetTagsID;
}


void addTagId(GArray* tagsId, GArray* postTags, GHashTable* com_tags){
	long id;
	Tag tag;

	for(int i = 0; i<postTags->len; i++){
		char* next_tag = g_array_index(postTags, char*, i);
		printf("Tag usada : %s\n",next_tag );
		tag = g_hash_table_lookup(com_tags, next_tag); 
		
		if(tag){
			id = getTagID(tag);			
			g_array_append_val(tagsId, id);	
		}
										
	}		

}


LONG_list most_used_best_rep_aux(GHashTable* com_user, GHashTable* com_tags, int N, Date begin, Date end){
	GArray* users = g_array_new(FALSE, FALSE, sizeof(User));
	int n_Users, size;

	char* date_begin = dateToString(begin);
	char* date_end = dateToString(end);

	void* info = (void*)users;
	g_hash_table_foreach(com_user, insereUsers, info); 
	
 	g_array_sort(users, (GCompareFunc)sortByRep);

	GArray* tagsId = g_array_new(TRUE, FALSE, sizeof(long));

	if(users->len < N) n_Users = users->len;
	else n_Users = N;
	
	for(int i = 0; i< n_Users; i++){ 
		User user = g_array_index(users, User, i);	
		GArray* user_posts = getUserPosts(user);

		for(int j = 0; j<user_posts->len; j++){
			Post post = g_array_index(user_posts, Post, j);			
			char* data = getPostSimpleDate(post);

			if(comparaDatas(date_begin, date_end, data) == 0){
				GArray* post_tags = getPostTags(post);
				if(post_tags != NULL) addTagId(tagsId, post_tags, com_tags);
				
			}
		}
	}

	g_array_sort(tagsId, (GCompareFunc)cmpInt);

	GArray* mSetTagsId = tagsIdToMSet(tagsId);
	g_array_sort(mSetTagsId, (GCompareFunc)sortMSet);

	if(mSetTagsId->len < N)
		size = mSetTagsId->len; 
	else 
		size = N;

	LONG_list r = create_list(size);

	for(int i=0; i<size; i++){
		LONG_pair aux = g_array_index(mSetTagsId, LONG_pair, i);	
		set_list(r, i, get_fst_long(aux));	
		/* debugging */ printf("Pos: %d tagId: %ld numVezesUsada: %ld\n",i,get_fst_long(aux),get_snd_long(aux));
	}
	

	DEBUG(printf("SIZE = %d\n", size));

	return r;

}

