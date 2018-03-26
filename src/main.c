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
	int id;
	char* display_name;
	//int rep;
	int n_perguntas;
	int n_respostas;
	//Date data_posts[];
	//Date data_respostas[];
	//char* títulos[];
	char* short_bio;
};

struct Post{
	int id;
	char* titulo;
	int owner_id;
	char* owner_display_name;
	int type_id;
	int parent_id;
	Date data;
	char* tags;
	int score;
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
   			xmlChar* name = xmlGetProp(cur, (const xmlChar *)"DisplayName");
			xmlChar* bio = xmlGetProp(cur, (const xmlChar *)"AboutMe");

   			if(id != NULL){
   				int* idUser = malloc(sizeof(int));
				
   				struct User* new = g_new(struct User, 1);//forma de fazer malloc
   				
   				// Nome
   				new->display_name = malloc(strlen((const char*)name) + 1);
   				strcpy(new->display_name,(const char*)name);

   				// ID
   				sscanf((const char*)id, "%d", idUser); 
   				new->id = *idUser;
				
				// Nº perguntas/respostas
				new->n_perguntas=0;
				new->n_respostas=0;

				// Bio
				if(bio){
					new->short_bio = malloc(strlen((const char*)bio) + 1);
					strcpy(new->short_bio, (const char*)bio);
				}
				else new->short_bio = "";
			 
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


	   			int* idOwner = malloc(sizeof(int));
	   			int* idPost = malloc(sizeof(int));
	   			int* idParent = malloc(sizeof(int));
	   			int* idType = malloc(sizeof(int));
	   			int* score = malloc(sizeof(int));
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

				// Count User's questions and answers 			
				struct User* user = (struct User*)g_hash_table_lookup(com->user, idOwner);
				if (user!=NULL) {
					if (*idType == 1) (user->n_perguntas)++;
					else if (*idType == 2) (user->n_respostas)++;
				}
								
	   			
	   			// Tags   = "<tag><tag>"  
	   			if(tags){
	   				new->tags = malloc(strlen((const char*)tags) + 1);
	   				strcpy(new->tags, (const char*)tags);
	   			}
	   			else new->tags = "";

	   			// Score
				sscanf((const char*)score_xml, "%d", score); 
	   			new->score = *score;

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
	printf("inseriu em %d\n",pos );
	for(int j = 0; j<20;j++)
		printf("%d ",array[j] ); printf("E\n");
	return pos;
}

void insereId(int* v, int x, int i, int n){

	for(n=n-1; n>i; n--){
		v[n] = v[n-1];
	}

	v[i] = x;
}


// QUERY 1

STR_pair info_from_post(TAD_community com, int id){
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

	int total,pos;
	int *idArray = ((int**)info)[0];
	int *countArray = ((int**)info)[1];
	int size = *((int**)info)[2];
	int *ocupados = ((int**)info)[3];
	
	total = user->n_respostas + user->n_perguntas;

	// insere no array caso nao esteja ainda cheio, ou se estiver, total maior que o menor elemento do array
	if( (*ocupados < size) || ( (*ocupados == size) && (total > countArray[(size)-1]) ) ){

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
		if(strstr(post->tags, tag) != NULL){ // str contains
			g_tree_insert(tree, (gpointer)post->data, (gpointer)id);			
		}
	}

}


void addToLongList(gpointer key_pointer, gpointer id_pointer, gpointer info){ // info = {lista, ocupados}
	//struct Post* post = (struct Post*) post_pointer;
	int* id = (int*) id_pointer;
	int* ocupados = ((int**)(info))[1]; 
	LONG_list lista = ((LONG_list*)(info))[0]; 

	set_list(lista, *ocupados, *id);
	(*ocupados)++;
}


LONG_list questions_with_tag(TAD_community com, char* tag, Date begin, Date end){ 

	GTree* tree = g_tree_new((GCompareFunc)comparaDatas);
	void* info[4] = {(void*)tree, (void*)tag, (void*)begin, (void*)end};

	// Constroi a tree com os posts com a tag e dentro da data
	/* Debugging */ clock_t begin1 = clock();
	g_hash_table_foreach(com->post, (GHFunc)adicionaComTag, (gpointer)info);
	/* Debugging */ clock_t end1 = clock();

	/* Debugging */ clock_t begin3 = clock();
	gint tam = g_tree_nnodes(tree); 

	LONG_list r = create_list(tam);
	/* Debugging */ clock_t end3 = clock();
	int* i = malloc(sizeof(int));
	*i = 0;
	void* lista[2] = {r, i};

	// Constroi a lista resultado (r)
	/* Debugging */ clock_t begin2 = clock();
	g_tree_foreach(tree, (GTraverseFunc)addToLongList, (gpointer)lista);
	/* Debugging */ clock_t end2 = clock();

	/* Debugging */ printf("Tempo de construir a arvore = %f\n", (double)(end1-begin1)/CLOCKS_PER_SEC);
	/* Debugging */ printf("Tempo de percorrer a arvore e criar a lista = %f\n", (double)(end3-begin3)/CLOCKS_PER_SEC);
	/* Debugging */ printf("Tempo de construir a lista = %f\n", (double)(end2-begin2)/CLOCKS_PER_SEC);
	
	return r;
}


// QUERY 5

/*
	criar variavel int[10] last_10_post_id -> no parser dos posts: - ir buscar o user do autor do post e last_10_post_id
																   - ir buscar a data dum post do array e comparar com a data do post que estamos a introduzir
																   - introduzir no array o id puxando o resto para a frente


	Dentro da função -> - criar array auxiliar
						- percorrer todos os posts da hash
						- inserir ordenadamente quando o post for do user em questao


*/
/*USER get_user_info(TAD_community com, long id){
	//struct User* user = malloc(sizeof(struct User));
	
	//user = (struct User*)g_hash_table_lookup(com->user, &id);


	// return create_user(user->bio, user->last_10_post_id);

}
*/


// QUERY 6

void func(gpointer key_pointer, gpointer post_pointer, gpointer info){
	struct Post* post = (struct Post*) post_pointer;
	int* ids = ((int**)info)[0];
	Date begin = ((Date*)info)[1];
	Date end = ((Date*)info)[2];
	int *ocupados = ((int**)info)[3];
	int* score = ((int**)info)[4];
	int *size = ((int**)info)[5];

	if(comparaDatas(begin, post->data) == -1 && comparaDatas(post->data, end) == -1){
		if( (*ocupados+1 != *size) || (*ocupados+1 == *size && post->score > score[*ocupados]) ){ // neste momento já sei que vai ser inserido
			int pos = insert(score, post->score, *size);
			if(pos != -1){
				insereId(ids, post->id, pos, *size);
				if(*ocupados < *size - 1) (*ocupados)++;
			}
		}
	}

}


LONG_list most_voted_answers(TAD_community com, int N, Date begin, Date end){
	int* ids = malloc(sizeof(int)*N);
	int* score = malloc(sizeof(int)*N);
	int *ocupados = 0;
	int i;

	for(i = 0; i<N; i++){
		ids[i] = 0;
		score[i] = 0;
	}

	void* info[6] = {(void*)ids, (void*)begin, (void*)end, (void*)ocupados, (void*)score, (void*)&N};

	g_hash_table_foreach(com->post, func, info);

	LONG_list r = create_list(N);	
	for(i = 0; i<N; i++) set_list(r, i, ids[i]);

	return r;
}
// QUERY 8

void insertByDate(struct Post* posts[],struct Post* post, int N, int* used){ //resultado: data mais recente para mais antiga
	int i = 0;
	int pos = -1;

	for(i = 0; i < *used && pos==-1; i++){
		if(comparaDatas(post->data,(posts[i])->data)==1) 
			pos = i;
			if(*used < N) (*used)++;
	}

	for(i = N-1; i>pos; i--){
		posts[i] = posts[i-1];
	}

	posts[pos] = post;	

}



void word_lookup(gpointer key_pointer, gpointer post_pointer, gpointer info){
	struct Post* post = (struct Post*)post_pointer;

	if(post->type_id==1){

		struct Post** postArray = ((struct Post***)info)[0];
		char* word = ((char**)info)[1]; 
		int size = *((int**)info)[2];
		int* ocupados = ((int**)info)[3];
		struct Post* last = postArray[size-1];

		if(strstr(post->titulo,word)&&(*ocupados < size||((*ocupados == size)&&(comparaDatas(post->data,last->data)==1)))){
			insertByDate(postArray,post,size,ocupados); 
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
	for(i = 0; i<N; i++) set_list(r, i, (postArray[i])->id);

	return r;	
}


/* Funcao para Debugging de PostHashT */
void printPostHT(gpointer key, gpointer value, gpointer user_data){
	struct Post* aux = (struct Post*)value;
	//printf("Alocou memoria para post\n");
	int* keyId = (int* )key;
	printf("%d ",*keyId);
	printf("%d ",aux->id);
	printf("%d ",aux->type_id);
	printf("%d ",aux->owner_id);
	printf("%s ",aux->owner_display_name);
	printf("%d ",aux->parent_id);
	printf("%s\n",aux->titulo);
	free(aux);
}

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
	
	clock_t begin3 = clock();
	LONG_pair new1 = total_posts(teste,inicio,fim);
	//printf("%ld %ld\n",get_fst_long(new1),get_snd_long(new1));
	clock_t end3 = clock();

	printf("Tempo '3 - total_posts' = %f\n", (double)(end3-begin3)/CLOCKS_PER_SEC);

	clock_t begin4 = clock();
	LONG_list new2 = questions_with_tag(teste, "android", inicio, fim); printf("%ld\n", get_list(new2, 0));
	clock_t end4 = clock();

	printf("Tempo '4 - questions_with_tag' = %f\n", (double)(end4-begin4)/CLOCKS_PER_SEC);

	clock_t begin5 = clock();
	LONG_list new3 = top_most_active(teste,500);
	for (int it=0;it<500;it++) {
		printf("%dº: %li ",(it+1),get_list(new3,it));
		int *aux = malloc(sizeof(int));
		*aux = get_list(new3,it);
		struct User* user = g_hash_table_lookup(teste->user,aux);
		if(user) printf("%d\n",user->n_perguntas+user->n_respostas);
	}
	clock_t end5 = clock();

	printf("Tempo '2 - top_most_active' = %f\n", (double)(end5-begin5)/CLOCKS_PER_SEC);

	// QUERY 8 TESTE LONG_list new8 = contains_word(teste,"supports",10);
	//QUERY 8 TESTE for(int aux=0;aux<10;aux++) printf("%d",get_list(new8,aux));
	

/* Funcao para Debugging da Q3:
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


