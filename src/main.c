#include <date.h>
#include <stdio.h>
#include <interface.h>
#include <libxml/parser.h>
#include <gmodule.h>
#include <glib.h>
#include <string.h>
#include <time.h>
#include "my_date.h"

/*NOTAS:
&#xA - \n codificado
&quot - "
&apos - '
&lt - <
&gt - >
&amp - &
*/



struct User{
	int id; // user id
	char* display_name; // username
	int rep; // reputação
	int n_perguntas; // número de perguntas
	int n_respostas; // número de respostas
	int n_posts; // número total de posts
	int reputacao;
	//Date data_posts[];
	//Date data_respostas[];
	//char* títulos[];
	char* short_bio; // descrição do user
	GArray* userPosts;

};

struct Post{
	int id;
	char* titulo;
	int owner_id;
	char* owner_display_name;
	int owner_rep;
	int type_id;
	int parent_id;
	Date data;
	char* tags;
	int score;
	int n_comments;
	int n_upvotes;
	int n_downvotes;
	int n_respostas;
	int accepted_answer; // testar q10 - POR EM COMENTARIO QUANDO NAO FOR NECESSARIO
};


struct TCD_community{
	GHashTable* user;
	GHashTable* post;	
};



TAD_community init(){
	struct TCD_community* new = malloc(sizeof(struct TCD_community));
  	GHashTable* newUserHash = g_hash_table_new(g_int_hash, g_int_equal);
  	GHashTable* newPostHash = g_hash_table_new(g_int_hash, g_int_equal);

  	new->user = newUserHash;
  	new->post = newPostHash;

  	return new;
}


TAD_community load(TAD_community com, char* dump_path){
	int i = 0;
	char* users = "Users.xml";
	char* users_path = malloc(strlen(dump_path)+strlen(users) + 1);
	strcpy(users_path,dump_path);
	strcat(users_path,users);
	

	char* posts = "Posts.xml";
	char* posts_path = malloc(strlen(dump_path)+strlen(posts) + 1);
	strcpy(posts_path,dump_path);
	strcat(posts_path,posts);

	char* votes = "Votes.xml";
	char* votes_path = malloc(strlen(dump_path)+strlen(votes)+1);
	strcpy(votes_path,dump_path);
	strcat(votes_path,votes);
	


	// USERS

	xmlDocPtr doc_users = xmlParseFile(users_path);
	if(!doc_users){
		printf("Document not parsed successfully\n");
	}

	xmlNodePtr cur = xmlDocGetRootElement(doc_users);
	if(!cur){
		printf("Empty Document\n");
		xmlFreeDoc(doc_users);
	}
	else{		
		cur = cur->xmlChildrenNode;
		while(cur){
   			xmlChar* id = xmlGetProp(cur, (const xmlChar *)"Id");
   			xmlChar* rep = xmlGetProp(cur, (const xmlChar *)"Reputation");
   			xmlChar* name = xmlGetProp(cur, (const xmlChar *)"DisplayName");
			xmlChar* bio = xmlGetProp(cur, (const xmlChar *)"AboutMe");

   			if(id != NULL){
   				int* idUser = malloc(sizeof(int));
   				int* repUser = malloc(sizeof(int));
				
   				struct User* new = g_new(struct User, 1);//forma de fazer malloc
   				
   				// Nome
   				new->display_name = malloc(strlen((const char*)name) + 1);
   				strcpy(new->display_name,(const char*)name);

   				// ID
   				sscanf((const char*)id, "%d", idUser); 
   				new->id = *idUser;

   				// Reputação
   				sscanf((const char*)rep,"%d", repUser);
   				new->reputacao = *repUser;
				
				// Nº perguntas/respostas
				new->n_perguntas = 0;
				new->n_respostas = 0;
				new->n_posts = 0;

				// Bio
				if(bio){
					new->short_bio = malloc(strlen((const char*)bio) + 1);
					strcpy(new->short_bio, (const char*)bio);
				}
				else new->short_bio = "";

				// User's Posts 
				new->userPosts = g_array_new (FALSE,TRUE,1);//(elemento no fim a 0,inicilizar a 0,tamnho em bytes dos elems)
			 
   				// Inserir conforme o ID
   				g_hash_table_insert(com->user, idUser, new); i++;
				
   			}
			xmlFree(id);
			xmlFree(name);
			cur = cur->next;
		}
	}
	printf("Users: %d\n", i);
	xmlFreeDoc(doc_users);

	// POSTS
	i = 0;

	xmlDocPtr doc_posts = xmlParseFile(posts_path);
	if(!doc_posts){
		printf("Document not parsed successfully\n");
	}

	cur = xmlDocGetRootElement(doc_posts);
	if(!cur){
		printf("Empty Document\n");
		xmlFreeDoc(doc_posts);
	}
	else{		
		cur = cur->xmlChildrenNode;
		while(cur){
			xmlChar* post_type_id = xmlGetProp(cur, (const xmlChar *)"PostTypeId");		
			if(post_type_id!=NULL){

	   			xmlChar* post_id = xmlGetProp(cur, (const xmlChar *)"Id");
	   			xmlChar* user_id = xmlGetProp(cur, (const xmlChar *)"OwnerUserId");
	   			xmlChar* user_display_name = xmlGetProp(cur, (const xmlChar *)"OwnerDisplayName");
	   			xmlChar* titulo = xmlGetProp(cur, (const xmlChar *)"Title");
	   			xmlChar* parent_id = xmlGetProp(cur, (const xmlChar *)"ParentId");
				xmlChar* data = xmlGetProp(cur, (const xmlChar *)"CreationDate");
				xmlChar* tags = xmlGetProp(cur, (const xmlChar *)"Tags");
				xmlChar* score_xml = xmlGetProp(cur, (const xmlChar *)"Score");
				xmlChar* comments = xmlGetProp(cur, (const xmlChar *)"CommentCount");


	   			int* idOwner = malloc(sizeof(int));
	   			int* idPost = malloc(sizeof(int));
	   			int* idParent = malloc(sizeof(int));
	   			int* idType = malloc(sizeof(int));
	   			int* score = malloc(sizeof(int));
	   			int* n_comms = malloc(sizeof(int));

	   			struct Post* new = g_new(struct Post, 1);
	   				
	   			// Titulo
	   			if(titulo){
	   				new->titulo = malloc(strlen((const char*)titulo) + 1);
	   				strcpy(new->titulo,(const char*)titulo);
	   			}
	   			else new->titulo="";

	   			// Owner ID
	   			if(user_id){
	   				sscanf((const char*)user_id, "%d", idOwner);
	   				new->owner_id = *idOwner;
	   			} 
	   			else new->owner_id = -2;

	   			// Owner Reputation
	   			struct User* user = (struct User*)g_hash_table_lookup(com->user,idOwner);
	   			if (user!=NULL)
	   				new->owner_rep=user->reputacao;

	   			// Count User's questions and answers 			
				if (user!=NULL) {
					if (*idType == 1) (user->n_perguntas)++;
					else if (*idType == 2) (user->n_respostas)++;
					(user->n_posts)++;
				}

				// Add Post to User
				if (user!=NULL){
					g_array_append_val(user->userPosts,new);
				}

	   			// Post ID
				sscanf((const char*)post_id, "%d", idPost); 
	   			new->id = *idPost;

	   			// Type ID
	   			sscanf((const char*)post_type_id, "%d", idType); 
	   			new->type_id = *idType;

	   			// Parent ID
	   			if(parent_id) {
	   				sscanf((const char*)parent_id, "%d", idParent); 
	   				new->parent_id = *idParent;
	   			}
	   			else new->parent_id = -2;

	   			// Owner Display Name
	   			if(user_display_name){
	   				new->owner_display_name = malloc(strlen((const char*)user_display_name) + 1);
	   				strcpy(new->owner_display_name,(const char*)user_display_name);
	   			}
	   			else new->owner_display_name = "";

	   			// Data
	   			new->data = atribuiData((char*) data);				
	   			
	   			// Tags   = "<tag><tag>"  
	   			if(tags){
	   				new->tags = malloc(strlen((const char*)tags) + 1);
	   				strcpy(new->tags, (const char*)tags);
	   			}
	   			else new->tags = "";

	   			// Score
				sscanf((const char*)score_xml, "%d", score); 
	   			new->score = *score;

	   			// Nº Upvotes
	   			new->n_upvotes=0;

	   			// Nº Downvotes
	   			new->n_downvotes=0;

	   			// Nº Comments
	   			sscanf((const char*)comments,"%d", n_comms);
	   			new->n_comments = *n_comms;

	   			// Nº Respostas
	   			if(new->type_id == 1){
	   				xmlChar* answercount = xmlGetProp(cur, (const xmlChar *)"AnswerCount");
	   				int* awnsers = malloc(sizeof(int));

	   				sscanf((const char*)answercount, "%d", awnsers); 
	   				new->n_respostas = *awnsers;
	   			}
	   			else new->n_respostas = -1;

	   			// Accepted answer - debugging q10 : COLOCAR EM COMENTÁRIO QUANDO NÃO FOR NECESSÁRIO!! 
	   			/*
	   			if (new->type_id==1) {
	   				xmlChar* answer = xmlGetProp(cur, (const xmlChar *)"AcceptedAnswerId");
					int* a_answer = malloc(sizeof(int));

	   				sscanf((const char*)answer,"%d", a_answer);
	   				new->accepted_answer = *a_answer;
	   			}
	   			else new->accepted_answer=-2;
	   			*/
	   			// Inserir conforme o Post ID
	   			g_hash_table_insert(com->post, idPost, new);
	   			
	   			/*Debugging*/ //printf("Inserido %d\n", i);
	   			i++;

	   			
				xmlFree(post_id);
				xmlFree(user_id);
				xmlFree(titulo);
				xmlFree(parent_id);
			}
			xmlFree(post_type_id);
			cur = cur->next;
		}
	}
	printf("Posts: %d\n", i);
	xmlFreeDoc(doc_posts);

	// VOTES

	i = 0;

	xmlDocPtr doc_votes = xmlParseFile(votes_path);
	if(!doc_votes){
		printf("Document not parsed successfully\n");
	}

	cur = xmlDocGetRootElement(doc_votes);
	if(!cur){
		printf("Empty Document\n");
		xmlFreeDoc(doc_votes);
	}
	else{		
		cur = cur->xmlChildrenNode;
		while(cur){

			xmlChar* id_post = xmlGetProp(cur, (const xmlChar *)"PostId");
			xmlChar* vote_type = xmlGetProp(cur, (const xmlChar *)"VoteTypeId");

			if(id_post && vote_type){
			
				int* postID = malloc(sizeof(int));
				int* votetype = malloc(sizeof(int));

				sscanf((const char*)id_post, "%d", postID);
				sscanf((const char*)vote_type,"%d", votetype);

				struct Post* post = (struct Post*)g_hash_table_lookup(com->post, postID);

				if (post && *votetype == 2) (post->n_upvotes)++;
				else if (post && *votetype == 3) (post->n_downvotes)++;

				i++;
			}
			xmlFree(id_post);
			xmlFree(vote_type);
			cur = cur->next;
		}
	}

	printf("Votes: %d\n", i);
	xmlFreeDoc(doc_votes);

	return(com);		
}
// FUNCAO AUXILIAR DE INSERCAO, DEPOIS REMOVER DO main

int insert(int* array, int elem, int size){
	int i = 0;
	int pos = -1;

	for(i = 0; i<size && pos==-1; i++){
		if(array[i]<elem) pos = i;
	}
	for(i = size-1; i>pos; i--){
		array[i] = array[i-1];
	}

	array[pos] = elem;
	/*printf("inseriu em %d\n",pos );
	for(int j = 0; j<20;j++)
		printf("%d ",array[j] ); printf("E\n"); */
	return pos;
}

void insereId(int* v, int x, int i, int n){

	for(n=n-1; n>i; n--){
		v[n] = v[n-1];
	}

	v[i] = x;
}


// QUERY 1

STR_pair info_from_post(TAD_community com, long id){
	STR_pair new = create_str_pair(NULL, NULL);

	struct Post* post = malloc(sizeof(struct Post));
	post = (struct Post*)g_hash_table_lookup(com->post, &id);
	
	if (!post) printf("Post not found...\n");
	else { 
		if(post->parent_id != -2){ //caso seja uma resposta...
			post = (struct Post*)g_hash_table_lookup(com->post, &post->parent_id);
		}

		if(*(post->owner_display_name)=='\0'){
			struct User* user = malloc(sizeof(struct User));
			user = (struct User*)g_hash_table_lookup(com->user, &post->owner_id); 
			new = create_str_pair(post->titulo, user->display_name); // não estamos a alocar 2 vezes memoria assim? usar sets??
		}
		else new = create_str_pair(post->titulo, post->owner_display_name);
	}	

	return new;
}

// QUERY 2

void insertionSort (gpointer key, gpointer user_pointer, gpointer info){
	struct User* user = (struct User*) user_pointer;

	int pos;
	int *idArray = ((int**)info)[0];
	int *countArray = ((int**)info)[1];
	int size = *((int**)info)[2];
	int *ocupados = ((int**)info)[3];
	int total = user->n_posts;

	// insere no array caso nao esteja ainda cheio, ou se estiver, n_posts maior que o menor elemento do array
	if( (*ocupados < size) || ( (*ocupados == size) && ( (user->n_posts) > countArray[(size)-1]) ) ){

		pos = insert(countArray,total,size);
		insereId(idArray,user->id,pos,size);

		if(*ocupados < (size)) (*ocupados)++;	

	}
	
}


LONG_list top_most_active(TAD_community com, int N) {
	
	LONG_list res = create_list(N);	
	
	int *ocupados = malloc(sizeof(int)); *ocupados=0;
	int id[N];
	int num_posts[N];

	for (int i=0;i<N;i++) {
		id[i] = num_posts[i]=-1;
	}
	
	void* info[4] = {id,num_posts,&N,ocupados};

	g_hash_table_foreach(com->user, insertionSort, info);

	for (int i=0;i<N;i++)
		set_list(res,i,(long)id[i]);

	return res;

}

// QUERY 3

void posts_count(gpointer key, gpointer post_pointer, gpointer info){
	
	struct Post* post = (struct Post*) post_pointer;
	Date post_date = post->data;

	Date begin = ((Date*)(info))[0];
	Date end = ((Date*)(info))[1];

	int* numQuestions = ((int**)(info))[2];
	int* numAnswers = ((int**)(info))[3];
	
	if(comparaDatas(post_date,begin)==1 && comparaDatas(end,post_date)==1){
		if(post->type_id==1) (*numQuestions)++;
			else (*numAnswers)++;
	}
}


LONG_pair total_posts(TAD_community com, Date begin, Date end){

	int *numQuestions = malloc(sizeof(int));
	int *numAnswers = malloc(sizeof(int));
	*numQuestions = *numAnswers = 0;

	void* info[4] = {begin, end, numQuestions, numAnswers};
	
	g_hash_table_foreach(com->post,posts_count,info);
	LONG_pair totalPost = create_long_pair(*numQuestions,*numAnswers);

	return totalPost;
}


// QUERY 4

void adicionaComTag(gpointer key_pointer, gpointer post_pointer, gpointer info){ // info = {tree, tag, inicio, fim}
	struct Post* post = (struct Post*) post_pointer;
	char* tag = malloc(strlen(((char**)info)[1] + 1)); strcpy(tag, ((char**)info)[1]);
	Date begin = ((Date*)(info))[2];
	Date end = ((Date*)(info))[3]; 
	GTree* tree = ((GTree**)(info))[0]; 
	int* id = &(post->id);

	if(comparaDatas(begin, post->data) == 1 && comparaDatas(post->data, end) == -1){  
		if(strstr(post->tags, tag) != NULL){
			g_tree_insert(tree, (gpointer)post->data, (gpointer)id);			
		}
	}

}


void addToLongList(gpointer key_pointer, gpointer id_pointer, gpointer info){ // info = {lista, ocupados}
	int* id = (int*) id_pointer;
	int* ocupados = ((int**)(info))[1]; 
	LONG_list lista = ((LONG_list*)(info))[0]; 

	set_list(lista, *ocupados, *id);
	(*ocupados)++;
}


LONG_list questions_with_tag(TAD_community com, char* tag, Date begin, Date end){ // PERGUNTAR AO STOR O TIPO DA TAG: "<TAG>" OU "TAG" !!!!!!!!!!!!!!!!!!!!!!!!!!!!

	GTree* tree = g_tree_new((GCompareFunc)comparaDatas);
	void* info[4] = {(void*)tree, (void*)tag, (void*)begin, (void*)end};

	// Constroi a tree com os posts com a tag e dentro da data
	g_hash_table_foreach(com->post, (GHFunc)adicionaComTag, (gpointer)info);

	gint tam = g_tree_nnodes(tree); 

	LONG_list r = create_list(tam);

	int* i = malloc(sizeof(int));
	*i = 0;
	void* lista[2] = {r, i};

	// Constroi a lista resultado (r)
	g_tree_foreach(tree, (GTraverseFunc)addToLongList, (gpointer)lista);

	return r;
}

// QUERY 5 ainda com erros

int ordena(gconstpointer a,gconstpointer b){
	int* a1 = (int*)a; int* b2 = (int*)b;
	if(*a1 == 0) return 1;
	if(*b2 == 0) return -1; 
	struct Post* post1 = (struct Post*)a;
	struct Post* post2 = (struct Post*)b;
	return comparaDatas(post1->data,post2->data) *(-1);
}

USER get_user_info(TAD_community com, long id){
	struct User* user = (struct User*)g_hash_table_lookup(com->user,&id);
	int i; long posts[10];
	USER res = NULL;
	if(user!=NULL){
		g_array_sort (user->userPosts,ordena);
		for(i=0;i<10;i++){
				struct Post* post = g_array_index(user->userPosts,struct Post*,i);
				if(post!=NULL)
					posts[i] = (long)post->id;
				else posts[i] = -2;
		}
		res = create_user(user->short_bio,posts);
	}
	return res;
}	

// QUERY 6

void ordenaScores(gpointer key_pointer, gpointer post_pointer, gpointer info){ // info = {ids, begin, end, ocupados, scores, N}
	struct Post* post = (struct Post*) post_pointer;

	if(post->type_id == 2){
		int pos;
		int* ids = ((int**)info)[0]; 
		Date begin = ((Date*)info)[1]; 
		Date end = ((Date*)info)[2]; 
		int *ocupados = ((int**)info)[3]; 
		int* scores = ((int**)info)[4]; 
		int size = *((int**)info)[5];

		int score = (post->n_upvotes)-(post->n_downvotes);

		if(comparaDatas(begin, post->data) == -1 && comparaDatas(post->data, end) == -1){
			if( (*ocupados != size) || (*ocupados == size && score > scores[size-1]) ){ // neste momento já sei que vai ser inserido
				pos = insert(scores, score, size);
				insereId(ids, post->id, pos, size);
				if(*ocupados < size) (*ocupados)++;
			}
		}	
	}

}


LONG_list most_voted_answers(TAD_community com, int N, Date begin, Date end){
	int* ids = malloc(sizeof(int)*N);
	int* scores = malloc(sizeof(int)*N);
	int* ocupados = malloc(sizeof(int)); *ocupados=0;
	int i;

	for(i = 0; i<N; i++){
		ids[i] = -2;
		scores[i] = -2;
	}

	void* info[6] = {(void*)ids, (void*)begin, (void*)end, (void*)ocupados, (void*)scores, (void*)&N};

	g_hash_table_foreach(com->post, ordenaScores, info);

	LONG_list r = create_list(N);	
	for(i = 0; i<N; i++) set_list(r, i, ids[i]);

	return r;
}

// QUERY 7

void ordenaNRespostas(gpointer key_pointer, gpointer post_pointer, gpointer info){ // info = {ids, begin, end, ocupados, n_respostas, N}
	struct Post* post = (struct Post*) post_pointer;

	if(post->type_id == 1){
		int pos;
		int* ids = ((int**)info)[0];
		Date begin = ((Date*)info)[1];
		Date end = ((Date*)info)[2];
		int *ocupados = ((int**)info)[3];
		int* n_respostas = ((int**)info)[4];
		int size = *((int**)info)[5];

		if(comparaDatas(begin, post->data) == -1 && comparaDatas(post->data, end) == -1){
			if( (*ocupados != size) || (*ocupados == size && post->n_respostas > n_respostas[size-1]) ){ // neste momento já sei que vai ser inserido
				pos = insert(n_respostas, post->n_respostas, size);
				insereId(ids, post->id, pos, size);
				if(*ocupados < size) (*ocupados)++;
			}
		}
	}

}

LONG_list most_answered_questions(TAD_community com, int N, Date begin, Date end){
	int* ids = malloc(sizeof(int)*N);
	int* n_respostas = malloc(sizeof(int)*N);
	int *ocupados = malloc(sizeof(int)); *ocupados=0;
	int i;

	for(i = 0; i<N; i++){
		ids[i] = -2;
		n_respostas[i] = -2;
	}

	void* info[6] = {(void*)ids, (void*)begin, (void*)end, (void*)ocupados, (void*)n_respostas, (void*)&N};
	
	g_hash_table_foreach(com->post, ordenaNRespostas, info);

	LONG_list r = create_list(N);	
	for(i = 0; i<N; i++) set_list(r, i, ids[i]);

	return r;
}


// QUERY 8

void printPostHT(struct Post* aux){
	if(aux!=NULL){
	printf("%d ",aux->id);
	printf("%d ",aux->type_id);
	printf("%d ",aux->owner_id);
	printf("%s ",aux->owner_display_name);
	printf("%d ",aux->parent_id);
	printf("%s\n",aux->titulo);
	} 
	else printf("null\n");
}

void insertByDate(struct Post* posts[],struct Post* post, int N, int* used){ //resultado: data mais recente para mais antiga
	int i = 0;
	int pos = 0;
	
	printf("%d",*used);
	for(i = 0; i < *used && pos==0; i++){
		printf("A comparar %d %d %d com %d %d %d\n",get_day(post->data),get_month(post->data),get_year(post->data),get_day(posts[i]->data),get_month(posts[i]->data),get_year(posts[i]->data));
		printf("%d\n",comparaDatas(post->data,(posts[i])->data));
		if(comparaDatas(post->data,(posts[i])->data)==1)
			break;		
	}

	pos = i;

	for(i = N-1; i>pos; i--){
		posts[i] = posts[i-1];
	}

	if(*used < N) (*used)++;
	posts[pos] = post;	

}



void word_lookup(gpointer key_pointer, gpointer post_pointer, gpointer info){
	struct Post* post = (struct Post*)post_pointer ; int i=0;
	if(post->type_id==1){
		
		char* titulo = malloc(strlen(post->titulo)+1);
		strcpy(titulo, post->titulo);

		char* word = malloc(strlen(((char**)info)[1])+1);
		strcpy(word,((char**)info)[1]);

		struct Post** postArray = ((struct Post***)info)[0];
	
		int size = *((int**)info)[2];
		
		int* ocupados = ((int**)info)[3];
	
		struct Post* last = postArray[size-1];// null ou endereço de um post
		printf("%d\n",*ocupados);
		printPostHT(post);

		if(strstr(titulo,word)!=NULL && ((*ocupados<size) || ((*ocupados == size) && (comparaDatas(post->data,last->data)==1)))){
			 insertByDate(postArray,post,size,ocupados);
			 printf("inseriu %dº\n",++i);
			 for(int aux=0;aux<10;aux++) if(postArray[aux]!=NULL)printf("%d\n",((struct Post*)(postArray[aux]))->id );
		}
	}
}

LONG_list contains_word(TAD_community com, char* word, int N){
	struct Post* postArray[N]; int i;

	for(i=0;i<N;i++) postArray[i]=NULL;

	int* ocupados = malloc(sizeof(int)); *ocupados=0;

	void* info[4] ={postArray,word,&N,ocupados};

	g_hash_table_foreach(com->post, word_lookup, info);

	LONG_list r = create_list(N);

	for(i = 0; i<N; i++) 
		if(postArray[i]!=NULL) 
			set_list(r, i, (postArray[i])->id);
		else 
			set_list(r,i,-2);


	return r;	
}

// QUERY 9

/* PRIMEIRA MANEIRA: sem utilizar o GArray dos posts

void isId (gpointer key_pointer, gpointer post_pointer, gpointer info) { // VERIFICAR SE ID1 PARTICIPA NA PERGUNTA
	struct Post* post = (struct Post*)post_pointer;
	int* ids = ((int**)info)[0]; // array fstId
	int* id1 = ((int**)info)[2];

	if (post->type_id==1 && post->owner_id==id1) { 
		//adicionar id1 a ids[];
	}
	else if (post->type_id==2 && post->owner_id==id1) {
		//adicionar post->parent_id a ids[];
	}
}

void isSndId (gpointer key_pointer, gpointer post_pointer, gpointer info) { // VERIFICAR SE ID2 PARTICIPA NAS PERGUNTAS OD ID1 PARTICIPA
	struct Post* post = (struct Post*)post_pointer;
	int* isFst = ((int**)info)[0];
	int* ids = ((int**)info)[1]; // array bothIds
	int* id2 = ((int**)info)[3]; // id2

	if (post->type_id==1 && post->owner_id==id2) {
		//for(int i;i<SIZE;i++) { if(isFst[i] == post->owner_id) {adicionar id2 a ids[];break;} }
	}
	else if (post->type_id==2 && post->owner_id==id2) {
		//for(int i;i<SIZE;i++) { if(isFst[i] == post->owner_id) {adicionar post->parent_id a ids[];break;} }
	}
}

LONG_list both_participated(TAD_community com, long id1, long id2, int N){
	int* isFstId = ... // FAZER ARRAY DINÂMICO
	int* bothIds = ... // FAZER ARRAY DINÂMICO
	int* fstId = malloc(sizeof(int));
	*fstId = id1;
	int* sndId = malloc(sizeof(int));
	*sndId = id2;

	void* info[] = {(void*)isFstId,(void*)bothIds,(void*)fstId,(void*)sndId};

	g_hash_table_foreach(com->post,isId,info); // colocar num array o id das perguntas em q id1 participa
	g_hash_table_foreach(com->post,isSndId,info); // colocar num array o id das perguntas em q id1 e id2 participam

	// FALTA ORDENAR E INSERIR NOS ARRAYS

		//1) percorrer hash posts para ver o id das perguntas onde aparece o id1 e adicionar a um array

		//2) percorrer hash posts para ver o id das perguntas onde aparece o id2 e adicionar apenas as que estão no outro array

		//3) ordenar o ultimo array por datas - pouco eficiente porque precisa do lookup e assim??
	
}


// SEGUNDA MANEIRA: utilizando o GArray dos posts
LONG_list both_participated(TAD_community com, long id1, long id2, int N){
	
	struct User* user1 = malloc(sizeof(struct User));
	user1 = g_hash_table_lookup(com->user,&id1); 
	struct User* user2 = malloc(sizeof(struct User));
	user2 = g_hash_table_lookup(com->user,&id2);

	int *ids = malloc(sizeof(int)*N);
	Date *datas = malloc(sizeof(int)*N);
	
	if (user1!=NULL && user2!=NULL) {
		for (int i=0;i<user1->n_posts;i++) {
			struct Post* post1 = g_array_index(user1->userPosts,struct Post*,i);

			if (post1!=NULL) {
				for (int j=i<user2->n_posts;i++) {
					
					struct Post* post2 = g_array_index(user2->userPosts,struct Post*,j);             //     dateInsertionSort NÃO DEFINIDA
				
					if (post2!=NULL) {
						if (post1->type_id == 1 && post2->type_id == 2 && post2->parent_id == post1->id) dateInsertionSort(); // post1 pergunta e post2 resposta: verificar se o pai do post2 é o post1
						else if (post1->type_id == 2 && post2->type_id == 1 && post1->parent_id == post2->id) dateInsertionSort(); // post1 resposta e post2 pergunta: verificar se o pai do post1 é o post2
						else if (post1->type_id == 2 && pos2->type_id == 2 && post1->parent_id == post2->parent_id) dateIinsertionSort(); // post1 e post2 respostas: verificar se têm o mm pai
					}
				}
			}
		}
	}
	
	LONG_list r = create_list(N);
	for (int i=0,i<N;i++) set_list(r,i,ids[i]);
	return r;

}

*/

// QUERY 10

double answer_score (int score, int rep, int favs, int comments) {
	return ( (score*0.45)+(rep*0.25)+(favs*0.2)+(comments*0.1));
}

void bestAnswer (gpointer key_pointer, gpointer post_pointer, gpointer info) {
	struct Post* post = (struct Post*)post_pointer;
	int* parentId = ((int**)info)[0];
	double* max = ((double**)info)[1];
	int* answerId = ((int**)info)[2];
	double score;

	if (post->type_id == 2 && post->parent_id == *parentId) {
		score=answer_score(post->score, post->owner_rep, (post->n_upvotes)-(post->n_downvotes), post->n_comments);
		if (score>(*max)) {
			*max=score;
			*answerId=post->id;
		}
	}
}

long better_answer(TAD_community com, long id) {

	int* parentId = malloc(sizeof(int));
	*parentId=id;

	int *max = malloc(sizeof(int));
	*max=0;

	int *answerId = malloc(sizeof(int));

	void* info[3] = {(void*)parentId, (void*)max, (void*)answerId};

	g_hash_table_foreach(com->post, bestAnswer, info);



	return (long)*answerId;
}

// QUERY 11




/* Funcao para Debugging de PostHashT */


/* Funcao para Debugging de UserHashT */
void printUserHT(gpointer key, gpointer value, gpointer user_data){
	struct User* aux = (struct User*)value;
	int* keyId = (int* )key;
	printf(user_data,*keyId, aux->id, aux->display_name);
}

/* Funcao para verificar procura na UserHashT */ 
void testeAcessoUserHT(TAD_community com, int id){
	int* aux = malloc(sizeof(int));
	*aux=id;
	struct User* user = malloc(sizeof(struct User));
	user = (struct User*)g_hash_table_lookup(com->user, aux);
	if(user) printf("%d %s\n",user->id,user->display_name);
	 else printf("user not found\n");
}

// Função para verificar contagem do nº posts
void ver_num (gpointer key, gpointer value, gpointer user_data){
	struct User* aux = (struct User*)value;
	int* keyId = (int* )key;
	printf(user_data,*keyId, aux->n_respostas,aux->n_perguntas);
}

// Função para seleção da melhor resposta
void ver_melhor_resposta (gpointer key, gpointer post, gpointer user_data){
	struct Post* aux = (struct Post*)post;
	int* keyId = (int* )key;
	if (aux->type_id==1) printf(user_data,*keyId, aux->accepted_answer);
}

int main(){
	struct TCD_community* teste = init();
	char* path = "../../dumpexemplo/android/";
	Date inicio = createDate(12,9,2010);
	Date fim = createDate(14,9,2010);

	clock_t begin = clock();
	load(teste, path);
	clock_t end = clock();

	printf("Tempo '0 - load' = %f\n", (double)(end-begin)/CLOCKS_PER_SEC);

	clock_t begin1 = clock();
	STR_pair new = info_from_post(teste,199);
	clock_t end1 = clock();

	printf("Tempo '1 - info_from_post' = %f\n", (double)(end1-begin1)/CLOCKS_PER_SEC);
	
	clock_t begin5 = clock();
	LONG_list new3 = top_most_active(teste,500);
	/*for (int it=0;it<500;it++) {
		printf("%dº: %li ",(it+1),get_list(new3,it));
		int *aux = malloc(sizeof(int));
		*aux = get_list(new3,it);
		struct User* user = g_hash_table_lookup(teste->user,aux);
		if(user) printf("%d\n",user->n_perguntas+user->n_respostas);
	}*/
	clock_t end5 = clock();

	printf("Tempo '2 - top_most_active' = %f\n", (double)(end5-begin5)/CLOCKS_PER_SEC);

	clock_t begin3 = clock();
	LONG_pair new1 = total_posts(teste,inicio,fim);
	//printf("%ld %ld\n",get_fst_long(new1),get_snd_long(new1));
	clock_t end3 = clock();

	printf("Tempo '3 - total_posts' = %f\n", (double)(end3-begin3)/CLOCKS_PER_SEC);

	clock_t begin4 = clock();
	LONG_list new2 = questions_with_tag(teste, "android", inicio, fim);
	clock_t end4 = clock();

	printf("Tempo '4 - questions_with_tag' = %f\n", (double)(end4-begin4)/CLOCKS_PER_SEC);

	clock_t begin6 = clock();
	LONG_list new4 = most_voted_answers(teste, 100, inicio, fim);
	//for(int i=0;i<100;i++) printf("%ld\n",get_list(new4, i));
	clock_t end6 = clock();

	printf("Tempo '6 - most_voted_answers' = %f\n", (double)(end6-begin6)/CLOCKS_PER_SEC);

	clock_t begin7 = clock();
	LONG_list new5 = most_answered_questions(teste, 100, inicio, fim);
	//for(int i=0;i<100;i++) printf("%ld\n",get_list(new5, i));
	clock_t end7 = clock();

	printf("Tempo '7 - most_answered_questions' = %f\n", (double)(end7-begin7)/CLOCKS_PER_SEC);



	LONG_list new8 = contains_word(teste,"there",10);
	for(int aux=0;aux<10;aux++) printf("%ld ",get_list(new8,aux));
	printf("\n");



	//clock_t begin8 = clock();
	//LONG_list new10 = better_answer(teste,76); //escolher id para teste e verificar pelos prints em baixo
	//clock_t end8 = clock();

	/* Função para Debugging da Q10 */
	//g_hash_table_foreach(teste->post,(GHFunc)ver_melhor_resposta,"Post:%d,Best Answer:%d\n");

	//printf("Tempo '10 - better_answer' = %f\n", (double)(end8-begin8)/CLOCKS_PER_SEC);


/* Funcao para Debugging da Q2:
g_hash_table_foreach(teste->user,(GHFunc)ver_num,"UserId:%d, Nº Perguntas:%d, Nº Respostas:%d\n");
*/

/* Funcao para Debugging de UserHashT*/
	//g_hash_table_foreach(teste->user,(GHFunc)printUserHT,"%d %d %s\n");
	//testeAcessoUserHT(teste,4980640);
/* Funcao para Debugging de PostHashT */
	//g_hash_table_foreach(teste->post,(GHFunc)printPostHT,NULL); 


	/*STR_pair new ;
	new = info_from_post(teste,199);// 199 nao tem owner id apenas owner display name
	printf("\nPERGUNTA:\n%s \n%s\n\n",get_fst_str(new),get_snd_str(new));*/

	/*
	new = info_from_post(teste,7);
	printf("\nRESPOSTA À PERGUNTA:\n%s \n%s\n\n",get_fst_str(new),get_snd_str(new));
   	printf("Tamanho hash: %d\n",g_hash_table_size(teste->user)); */
  	
  	return 0;
} 


