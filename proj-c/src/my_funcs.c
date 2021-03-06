#include <my_funcs.h>

// Funcoes sobre Posts 

Post getPost (GTree* com_post, GHashTable* com_postAux, long id){
	Post post  = NULL;

	char* postDate = g_hash_table_lookup(com_postAux, (gpointer)id);
	
	if(postDate){

		PostKey key = createPostKey( postDate, id);

		post = (Post)g_tree_lookup(com_post, key);

		freePostKey(key);
	}

	return post;
}


/*
 Função que verifica se uma pergunta ou uma resposta, conforme valor passado como parâmetro, pertence a um intervalo de 
 datas, e, caso pertença, adiciona o post em causa a um GArray.
*/
gboolean addPostsToGArray (PostKey postKey, Post post, gpointer info){
	int* typeId = ((int**)info)[3];

	if(getPostTypeID(post) == *typeId){
		char* begin = ((char**)info)[0]; 
		char* end = ((char**)info)[1]; 
		char* post_date = getPostSimpleDate(post);
		GArray* posts = ((GArray**)info)[2];

		int dateCheck = comparaDatas(begin, end, post_date);

		free(post_date);

		if(dateCheck == -1) return TRUE;

		if(dateCheck == 0) g_array_append_val(posts, post);
	}	

	return FALSE;
}

GArray* filterPostsByTypeID (GTree* com_post, char* date_begin, char* date_end, int typeId){
	GArray* posts = g_array_new(FALSE, FALSE, sizeof(Post));

	void* info[4] = {date_begin, date_end, posts, &typeId};

	g_tree_foreach(com_post, (GTraverseFunc)addPostsToGArray, info);

	return posts;
}


// Funções sobre Hash dos User 

User getUser (GHashTable* com_user, long id){
	long userId = id;

	return  g_hash_table_lookup(com_user, (gpointer)userId );
}

/*
 Função que adiciona um User a um GArray.
*/
void appendUserToArray (long userId, User user, GArray* users){	
	g_array_append_val(users,user);
}

GArray* usersHashToGArray (GHashTable* com_user){
	GArray* users = g_array_new(FALSE,FALSE,sizeof(User));

	g_hash_table_foreach(com_user, (GHFunc)appendUserToArray, users);

	return users;
}

// Funcao sobre hash das Tags

Tag getTag (GHashTable* com_tags, char* tag){

	return g_hash_table_lookup(com_tags, tag); 
}



// Funções para ordenação 

int sortByNPosts (User* a,User *b){
	int nposts1 = getUserNPosts(*a);
	int nposts2 = getUserNPosts(*b);

	int result = nposts2-nposts1;
	
	return result? result : getUserID(*a) - getUserID(*b);
}

int sortByRep (User* a,User *b){
	int rep_a = getUserReputation(*a);
	int rep_b = getUserReputation(*b);
	
	int result = rep_b-rep_a;
	
	return result? result : getUserID(*a) - getUserID(*b);
}

int sortByScore (Post *a, Post *b){
	int score_a = getPostScore(*a);
	int score_b = getPostScore(*b);

	return score_b - score_a;
}

int sortByNAnswers (Post* a, Post *b){
	int n_resp_a = getPostNAnswers(*a);
	int n_resp_b = getPostNAnswers(*b);
	
	return n_resp_b - n_resp_a;
}

int sortByDate (Post* a, Post* b){
	char* date_a = getPostDate(*a);
	char* date_b = getPostDate(*b);
	
	int result =  strcmp(date_b, date_a);
	
	free(date_a);
	free(date_b);
	
	return result;

}

int sortMSet (LONG_pair* a, LONG_pair* b){
	long ocur_a = get_snd_long(*a);
	long ocur_b = get_snd_long(*b);
	long tagId_a = get_fst_long(*a);
	long tagId_b = get_fst_long(*b);

	int result = ocur_b - ocur_a;

	return result? result : tagId_a - tagId_b;
}



// Datas

char* dateToString (Date date){

	int year = get_year(date);
	int month = get_month(date);
	int day = get_day(date);

	GDateTime* date_aux = g_date_time_new_utc(year,month,day,0,0,0);
	char* date_res = g_date_time_format(date_aux,"%F");
	g_date_time_unref(date_aux);

	return date_res;
}

int comparaDatas (char* begin, char* end, char* post_date){ 

	if(strcmp(post_date,end)>0) 
		return 1; // ainda nao entrou no intervalo de tempo (na travessia)
	if(strcmp(begin,post_date)>0) 
		return -1; // dataPost fora do limite inferior(Return True na travessia)
	else 
		return 0; // esta dentro do intervalo 
}


// Funções auxiliares para processamento das tags

char* nextTag (char* tags, int *i){
	int j = (*i); 
	int tagSize=0;

	while(tags[j] != '>') {
		tagSize++;  j++; 
	}
	
	char* new_tag = g_strndup(tags + (*i), tagSize);

	new_tag[tagSize] = '\0';

	int newPosition = (*i) + tagSize + 2;

	if ( newPosition <  strlen(tags) ) // avanca >< e posiciona no inicio da nova tag
		*i = newPosition;
	else 
		*i = strlen(tags);

	return new_tag;
}


// Função para determinar tamanho da LONG_list a devolver 

int selectSize (int garraySize, int n){
	int size;

	if(garraySize > n) 
		size = n;
	else 
		size = garraySize;	

	return size;
}
