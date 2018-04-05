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

int ordenaTags(Tag* a, Tag* b){
	int ocor_a = getTagOcor(*a);
	int ocor_b = getTagOcor(*b);

	return ocor_b - ocor_a;
}


char* nextTag(char* tags, int *i){
	char* new_tag = malloc(strlen(tags));
	int j = 0;
	int k = (*i);

	if(tags[k] == '<') k++;
	for(j=j; tags[k]!= '>'; j++, k++){
		new_tag[j] = tags[k];
	}
	new_tag[j] = '\0';

	(*i) += j+1;

	return new_tag;
}

int elemTag(GArray* array, char* name){
	int i;

	for(i=0; i<array->len; i++){
		Tag tag = g_array_index(array, Tag, i);

		if(strcmp(name, getTagName(tag))==0) return i;
	}
	
	return -1;
}

void adicionaTag(GArray* array, char* tags, GHashTable* com_tags){
	int x;
	Tag tag;

	if(tags){
		for(int i=0; tags[i]!='\0'; i++){
			char* name = nextTag(tags, &i);  
			if(name){
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
	}
}


LONG_list most_used_best_rep_aux(GHashTable* com_user,GHashTable* com_tags, int N, Date begin, Date end){
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
			Date data = getPostDate(post);

			if(comparaDatas(begin, data) == -1 && comparaDatas(data, end) == -1)
				adicionaTag(tags, getPostTags(post), com_tags);		
			
		}
	}
	
	// Ordena GArray por ocorrencias
	g_array_sort(tags, (GCompareFunc)ordenaTags);



	// Copia tags
	int size;

	if(tags->len < N)
		size = tags->len; 
	else 
		size = N;

	LONG_list r = create_list(size);

	for (int i=0; i<size; i++){
		Tag tag = g_array_index(tags, Tag, i);
		printf("%d %d\n",getTagID(tag),getTagOcor(tag)); //para verificar se esta a correto o resultado
		set_list(r,i, getTagID(tag));	
	} 

	return r;

}
