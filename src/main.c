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

				new->n_respostas=0;
				new->n_perguntas=0;			 
   				

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


	   			int* idOwner = malloc(sizeof(int));
	   			int* idPost = malloc(sizeof(int));
	   			int* idParent = malloc(sizeof(int));
	   			int* idType = malloc(sizeof(int));
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

				// Count questions and answers
				
				struct User* user = malloc(sizeof(struct User));
				user = (struct User*)g_hash_table_lookup(com->user, idOwner);
				if (user!=NULL) {
					if (atoi((const char*)post_type_id) == 1) (user->n_perguntas)++;
					else if (atoi((const char*)post_type_id) == 2) (user->n_respostas)++;
				}
								
	   			
	   			// Tags   = "<tag><tag>"  
	   			if(tags){
	   				new->tags = malloc(strlen((const char*)tags) + 1);
	   				strcpy(new->tags, (const char*)tags);
	   			}
	   			else new->tags = "";
				

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

void insertionSort (gpointer id, gpointer u, gpointer info){
	struct User* user = (struct User*) u;
	int *ids = ((int**)info)[0];
	int *nposts = ((int**)info)[1];
	int *tam = ((int**)info)[2];
	int i,j;
	if (user!=NULL) {
		int num=(user->n_respostas)+(user->n_perguntas);
		for (i=0;i<(*tam);i++) {
			if (num>nposts[i]) {
				for (j=(*tam);j>i;j--){
					ids[j]=ids[j-1];
					nposts[j]=nposts[j-1];
				}
				ids[i]=user->id;
				nposts[i]=num;
				break;			
			}
		}
	}
	// DEBUGGING: for (int i=0;i<(*tam);i++) printf("id[%d]: %d, num[%d]: %d\n",i,ids[i],i,nposts[i]);
}


LONG_list top_most_active(TAD_community com, int N) {
	
	LONG_list res = create_list(N);	
	
	int *size=malloc(sizeof(int));
	*size=N;
	int id[N];
	int num_posts[N];
	for (int i=0;i<N;i++) {
		id[i]=0; num_posts[i]=0;
	}
	
	void* info[3] = {id,num_posts,size};

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
	LONG_pair totalPost= create_long_pair(*numQuestions,*numAnswers);

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
			g_tree_insert(tree, (gpointer)post->data, (gpointer)id);	// será que é necessária a estrutura post ou basta o id?			
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
USER get_user_info(TAD_community com, long id){
	//struct User* user = malloc(sizeof(struct User));
	
	//user = (struct User*)g_hash_table_lookup(com->user, &id);


	// return create_user(user->bio, user->last_10_post_id);

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

	LONG_list new3 = top_most_active(teste,10);
	for (int it=0;it<10;it++) 
		printf("%dº: %li\n",(it+1),get_list(new3,it));

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


