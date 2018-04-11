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

	for(i=0; i<array->len; i++){
		Tag tag = g_array_index(array, Tag, i);

		if(g_strcmp0(name, getTagName(tag))==0) return i;
	}
	
	return -1;
}

void adicionaTag(GArray* array, GArray* tags, GHashTable* com_tags){
	int x;
	Tag tag;

	for(int i=0; i<tags->len; i++){
		char* name = g_array_index(tags, char*, i);

		if((x = elemTag(array, name)) != -1){
			tag = g_array_index(array, Tag, x); 
			setTagOcor(tag, getTagOcor(tag) + 1);
		}
		else{
			tag = g_hash_table_lookup(com_tags, name); 
			Tag new_tag = createTag(name, getTagID(tag), 1); 
			g_array_append_val(array, new_tag);					
		}	
	}	
	
}


LONG_list most_used_best_rep_aux(GHashTable* com_user, GHashTable* com_tags, int N, Date begin, Date end){
	GArray* users = g_array_new(FALSE,FALSE,sizeof(User));

	void* info = (void*)users;
	
	// Filtra os melhores N users por reputação
	g_hash_table_foreach(com_user, insereUsers, info); 

 	g_array_sort(users, (GCompareFunc)sortByRep);

	GArray* tags = g_array_new(FALSE, TRUE,sizeof(Tag));

	for(int i = 0; i<N; i++){ 
		User user = g_array_index(users, User, i);	
		GArray* user_posts = getUserPosts(user);

		for(int j = 0; j<user_posts->len; j++){
			Post post = g_array_index(user_posts, Post, j);			
			Date data = getPostSimpleDate(post);
			// Debugging  printf("Data: %d-%d-%d\n", get_day(data), get_month(data), get_year(data));
			//  Debugging  printf("6 %d %d\n", i, j);
			if(comparaDatas(begin, end, data) == 0){
				adicionaTag(tags, getPostTags(post), com_tags);	
				// Debugging printf("7\n");	
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

	for(int i=0; i<size; i++){
		Tag tag = g_array_index(tags, Tag, i);
		printf("%li %d\n", getTagID(tag), getTagOcor(tag)); //para verificar se esta a correto o resultado
		set_list(r, i, getTagID(tag));	
	} 

	return r;

}

