#include <query_11.h>


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

int sortByTagOcor(Tag* a, Tag* b){
	int ocor_a = getTagOcor(*a);
	int ocor_b = getTagOcor(*b);

	return ocor_b - ocor_a;
}

int elemTag(GArray* array, char* name){
	int i;
	DEBUG(printf("%s\n", name));

	for(i=0; i<array->len; i++){
		Tag tag = g_array_index(array, Tag, i);

		DEBUG(printf("%s - %s\n", name, getTagName(tag)));
		if(g_strcmp0(name, getTagName(tag))==0) return i;
	}
	
	return -1;
}

void adicionaTag(GArray* array, GArray* tags, GHashTable* com_tags){
	int x;
	Tag tag;

	for(int i = 0; i<tags->len; i++){
		char* next_tag = g_array_index(tags, char*, i);
		//DEBUG(printf("Para contabilizar - %s\n", next_tag));
		x = elemTag(array, next_tag);
		//DEBUG(printf("%d\n", x));			
		if(x != -1){
			//DEBUG(printf("A adicionar na posição %d\n", x));

			tag = g_array_index(array, Tag, x); 
			setTagOcor(tag, getTagOcor(tag) + 1);
		}
		else{
			//DEBUG(printf("A contabilizar - %d\n", x));

			tag = g_hash_table_lookup(com_tags, next_tag); 
			//DEBUG(printf("HASHTAG: %s - %ld - %d\n", getTagName(tag), getTagID(tag), getTagOcor(tag))); 

			if(tag){
				Tag new_tag = createTag(next_tag, getTagID(tag), 1);
				DEBUG(printf("TAG: %s - %ld - %d\n", getTagName(new_tag), getTagID(new_tag), getTagOcor(new_tag))); 
				g_array_append_val(array, new_tag);	
			}
							
		}
		//DEBUG(printf("Contabilizado\n"));
	}		

}


LONG_list most_used_best_rep_aux(GHashTable* com_user, GHashTable* com_tags, int N, Date begin, Date end){
	GArray* users = g_array_new(FALSE, FALSE, sizeof(User));
	int n_Users;

	void* info = (void*)users;
	
	// Filtra os melhores N users por reputação
	g_hash_table_foreach(com_user, insereUsers, info); 
	
	DEBUG(
		printf("Vai procurar\n");
		Tag new_tag_ = g_hash_table_lookup(com_tags, "ruu"); 
		printf("TAG: %s - %ld - %d\n", getTagName(new_tag_), getTagID(new_tag_), getTagOcor(new_tag_));

	);

 	g_array_sort(users, (GCompareFunc)sortByRep);

	GArray* tags = g_array_new(FALSE, FALSE, sizeof(Tag));

	if(users->len < N) n_Users = users->len;
	else n_Users = N;
	
	for(int i = 0; i< n_Users; i++){ 
		User user = g_array_index(users, User, i);	
		GArray* user_posts = getUserPosts(user);

		for(int j = 0; j<user_posts->len; j++){
			Post post = g_array_index(user_posts, Post, j);			
			Date data = getPostSimpleDate(post);

			if(comparaDatas(begin, end, data) == 0){
				GArray* post_tags = getPostTags(post);
				if(post_tags != NULL) adicionaTag(tags, post_tags, com_tags);
			}
		}
	}

	// Ordena GArray por ocorrencias
	g_array_sort(tags, (GCompareFunc)sortByTagOcor);



	// Copia tags
	int size;

	if(tags->len < N)
		size = tags->len; 
	else 
		size = N;

	LONG_list r = create_list(size);

	DEBUG(
		for(int i=0; i<size; i++){
			Tag tag = g_array_index(tags, Tag, i);
			printf("%s %li %d\n", getTagName(tag), getTagID(tag), getTagOcor(tag)); //para verificar se esta a correto o resultado
			set_list(r, i, getTagID(tag));	
		}
	);

	DEBUG(printf("SIZE = %d\n", size));

	return r;

}

