#include "query_11.h"

void ordenaUsers(gpointer key_pointer, gpointer user_pointer, gpointer info){
	int* ids = ((int**)info)[0];
	int* rep = ((int**)info)[1];
	int *ocupados = ((int**)info)[2];
	int size = ((int*)info)[3];
	User user = (User)user_pointer;

	if( (*ocupados != size) || (*ocupados == size && getUserReputacao(user) > rep[size-1]) ){
		int pos = insert(rep, getUserReputacao(user), size);
		insereId(ids, getUserID(user), pos, size);
		if(*ocupados < size) (*ocupados)++;
	}
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
	

	return 0;
}

void adicionaTag(GArray* array, char* tags, TAD_community com){
	int x;
	Tag tag;

	for(int i=0; tags[i]!='\0'; i++){
		char* name = nextTag(tags, &i);
		if(name){
			if((x = elemTag(array, name))){
				tag = g_array_index(array, Tag, x);
				setTagOcor(tag, getTagOcor(tag) + 1);
			}
			else{
				tag = g_hash_table_lookup(com->tags, name);
				Tag new_tag = createTag(name, getTagID(tag), 1);
				g_array_append_val(array, new_tag);
			}
		}
	}
}


LONG_list most_used_best_rep(TAD_community com, int N, Date begin, Date end){
	int* top_users_ids = malloc(sizeof(int)*N);
	int* rep_users = malloc(sizeof(int)*N);
	
	int *ocupados = 0;
	void* info[4] = {top_users_ids, rep_users, ocupados, &N};

	// Filtra os melhores N users por reputação
	g_hash_table_foreach(com->user, ordenaUsers, info);


	GArray* tags = g_array_new(FALSE, TRUE, (guint)sizeof(Tag));

	for(int i = 0; i<N; i++){
		User user = g_hash_table_lookup(com->user, &(top_users_ids[i]));
		GArray* posts_ids = (GArray*)getUserPosts(user);

		for(int j = 0; j<posts_ids->len; j++){
			Post post = g_hash_table_lookup(com->post, &(posts_ids[j]));
			Date data = getPostDate(post);

			if(comparaDatas(begin, data) == -1 && comparaDatas(data, end) == -1){
				adicionaTag(tags, getPostTags(post), com);
			}
		}
	}

	//ordena(tags);
	//copiaNTags();


}
