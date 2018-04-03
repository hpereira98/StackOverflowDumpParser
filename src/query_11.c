#include "query_11.h"

void ordenaUsers(gpointer key_pointer, gpointer user_pointer, gpointer info){
	int* ids = ((int**)info)[0];
	int* rep = ((int**)info)[1];
	int *ocupados = ((int**)info)[2];
	int size = *((int**)info)[3];
	User user = (User)user_pointer;
	int user_rep = getUserReputacao(user);

	if( (*ocupados != size) || (*ocupados == size && user_rep > rep[size-1]) ){
		int pos = insert(rep, user_rep, size);
		insereId(ids, getUserID(user), pos, size);
		if(*ocupados < size) (*ocupados)++;
	}
}

int ordenaTags(Tag a, Tag b){
	int ocor_a = getTagOcor(a);
	int ocor_b = getTagOcor(b);

	if(ocor_a < ocor_b) return 1;
	if(ocor_a > ocor_b) return -1;

	return 0;
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

		if(strcmp(name, getTagName(tag))) return i;
	}

	return -1;
}

void adicionaTag(GArray* array, char* tags, TAD_community com){
	int x;
	Tag tag;

	for(int i=0; tags[i]!='\0'; i++){
		char* name = nextTag(tags, &i);
		if(name){
			if((x = elemTag(array, name)) != -1){
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
	
	for(int i = 0; i<N; i++){ // estas declarações e inicializações acho que podem ser apenas 'int top_users_ids[N] = {-2};'
		top_users_ids[i] = -2;
		rep_users[i] = -2;
	}

	int *ocupados = malloc(sizeof(int)); *ocupados = 0;
	void* info[4] = {(void*)top_users_ids, (void*)rep_users, (void*)ocupados, (void*)&N};
	/* Debugging */ printf("0\n");
	// Filtra os melhores N users por reputação
	g_hash_table_foreach(com->user, ordenaUsers, info); // se existir diferença nos anos das datas para logo aqui. wtf?! ou será por pormos createDate(1,1,2000) em vez de (01,01,2000)?

	/* Debugging */ printf("1\n"); 
	GArray* tags = g_array_new(FALSE, TRUE, (guint)sizeof(Tag));

	/* Debugging */ printf("2\n");
	for(int i = 0, k=0; i<N; i++){ // k para debug
		User user = (User)g_hash_table_lookup(com->user, &(top_users_ids[i]));
		GArray* user_posts = getUserPosts(user);
		
		for(int j = 0; j<user_posts->len; j++, k++){
			Post post = (Post)g_array_index(user_posts, Post, j); // este post nunca pode ser nulo por isso não é necessario if(post){...}
			/* Debugging */ printf("Post ID = %d\n%d\n", getPostID(post),k);
			Date data = getPostDate(post);

			if(comparaDatas(begin, data) == -1 && comparaDatas(data, end) == -1){
				adicionaTag(tags, getPostTags(post), com);
				/* Debugging */ printf("Tags contabilizadas\n"); // nunca imprime isto - talvez pelo intervalo das datas entao nunca adiciona
			}
		}
	}
	/* Debugging */ printf("3\n");

	// Ordena GArray por ocorrencias
	g_array_sort(tags, (GCompareFunc)ordenaTags);
	
	/* Debugging */ printf("4\n");

	// Copia N tags
	LONG_list r = create_list(N);

	for (int i=0; i<N; i++){
		Tag tag = g_array_index(tags, Tag, i);

		set_list(r,i, getTagID(tag));	
	} 

	return r;

}
