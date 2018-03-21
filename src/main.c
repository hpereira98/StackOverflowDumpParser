#include <date.h>
#include <stdio.h>
#include <interface.h>
#include <libxml/parser.h>
#include <gmodule.h>
#include <glib.h>
#include <string.h>


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
	//int n_perguntas;
	//int n_respostas;
	//Date data_posts[];
	//Date data_respostas[];
	//char* títulos[];
	//char* short_bio[];
};

struct Post{
	int id;
	char* titulo;
	int owner_id;
	int type_id;
	int parent_id;
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
	int i=0;
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
   			xmlChar* id = xmlGetProp(cur, (const xmlChar *)"AccountId");
   			xmlChar* name = xmlGetProp(cur, (const xmlChar *)"DisplayName");

   			if(id != NULL){
   				int* idUser = malloc(sizeof(int));
   				struct User* new = g_new(struct User, 1);//forma de fazer malloc
   				
   				new->display_name = malloc(strlen((const char*)name) + 1);
   				strcpy(new->display_name,(const char*)name);

   				sscanf((const char*)id, "%d", idUser); 
   				new->id = *idUser;			 
   				
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

	/*Debugging*/ printf("Abriu Posts.xml\n");

	cur = xmlDocGetRootElement(doc_posts);
	if(!cur){
		printf("Empty Document\n");
		xmlFreeDoc(doc_posts);
	}
	else{		
		cur = cur->xmlChildrenNode;
		while(cur){
			xmlChar* post_type_id = xmlGetProp(cur, (const xmlChar *)"PostTypeId");

			/*Debugging*/ printf("Verificou o PostTypeId = %s\n", (char*)post_type_id); // está a dar null e para o programa. Porque??
			
			if(post_type_id!=NULL && strcmp((char*)post_type_id, "1") == 0){

				/*Debugging*/ printf("Comparou o PostTypeId\n");
	   			
	   			xmlChar* post_id = xmlGetProp(cur, (const xmlChar *)"Id");printf("1\n");
	   			xmlChar* user_id = xmlGetProp(cur, (const xmlChar *)"OwnerUserId");printf("2\n");
	   			xmlChar* titulo = xmlGetProp(cur, (const xmlChar *)"Title");printf("3\n");
	   			xmlChar* parent_id = xmlGetProp(cur, (const xmlChar *)"ParentId");

	   			if(post_id != NULL){printf("4\n");
	   				int* idOwner = malloc(sizeof(int));printf("4\n");
	   				int* idPost = malloc(sizeof(int));printf("5\n");
	   				int* idParent = malloc(sizeof(int));
	   				int* idType = malloc(sizeof(int));
	   				struct Post* new = g_new(struct Post, 1);printf("6\n");
	   				
	   				// Titulo
	   				new->titulo = malloc(strlen((const char*)titulo) + 1);printf("7\n");
	   				strcpy(new->titulo,(const char*)titulo);printf("8\n");

	   				// Owner ID
	   				printf("Ola\n");if(user_id)sscanf((const char*)user_id, "%d", idOwner);else(printf("nao tem owner(?)\n")); printf("9\n");
	   				new->owner_id = *idOwner;printf("10\n");

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
	   				else new->parent_id = 0;

	   				/*Debugging*/ printf("A inserir %d\n", i);

	   				// Inserir conforme o Post ID
	   				g_hash_table_insert(com->post, idPost, new);
	   				
	   				/*Debugging*/ printf("Inserido %d\n", i);
	   				i++;

	   			}
				xmlFree(post_id);
				xmlFree(user_id);
				xmlFree(titulo);
			}
			/*Debugging*/ else printf("Verificou o PostTypeId e não é do tipo 1\n");
			xmlFree(post_type_id);
			cur = cur->next;
		}
	}
	printf("Posts: %d\n", i);
	xmlFreeDoc(doc_posts);
	
	return(com);		
}



STR_pair info_from_post(TAD_community com, int id){
	
	/* Debugging */ printf("A executar info_from_post\n");

	struct Post* post = malloc(sizeof(struct Post));
	post = (struct Post*)g_hash_table_lookup(com->post, &id);
	
	/* Debugging */ printf("Alocou memória para a estrutura Post\n");
	/* Debugging */ printf("%d\n", post->parent_id); // ERRO AO ACEDER A POST->PARENT_ID
	if(post->parent_id != 0){
		post = (struct Post*)g_hash_table_lookup(com->post, &post->parent_id);
	}

	struct User* user = malloc(sizeof(struct User));
	user = (struct User*)g_hash_table_lookup(com->user, &post->owner_id); 

	/* Debugging */ printf("Alocou memória para a estrutura User\n");

	STR_pair new = create_str_pair(post->titulo, user->display_name);
	
	return new;
}

/* INTERROGAÇÃO 2 - Protótipo:

int get_min (int lista[],int tam) {
	int min=0,i;	
	if (lista!=NULL) {
		min=lista[0];
		for (i=1;i<tam;i++)
			if (lista[i]<min) min=lista[i];
	}
	return min;
}

int get_min_pos (int lista[],int tam) {
	int min=0,pos=0,i;	
	if (lista!=NULL) {
		min=lista[0];
		for (i=1;i<tam;i++)
			if (lista[i]<min) {
				min=lista[i];
				pos=i;
			}
	}
	return pos;
}

LONG_list top_most_active(TAD community com, int N) { 

	struct User* user = malloc(sizeof(struct User));
	int iU;
	int min-1;
	int pos=0;
	int minPos=0;
	int nPosts;
	int listaAux[N];
	LONG_list res = create_list(N);	
	
	for (iU=-1;iU<=245699;iU++) { // preencher as N posições da lista

		user = (struct User*)g_hash_table_lookup(com->user, GINT_TO_POINTER(iU));		

		if (user!=NULL) {

			nPosts=user.n_respostas + user.n_perguntas;			
			if(min==-1) min=nPosts;  // inicializar min com o primeiro nPosts
			else if (nPosts < min) {
				min=nPosts; // atualizar min nas primeiras N inserções
				minPos=pos; // atualizar posição do mínimo no array auxiliar
			set_list(res,pos,user.id); // colocar userId na lista res
			listaAux[pos]=nPosts; // colocar o nPosts na listaAux
			pos++;
		}
		
		if (pos==N) break;
	}								
	
	for (;iU<=245699;iU++) { // preencher a lista com os N user com mais posts

		user = (struct User*)g_hash_table_lookup(com->user, GINT_TO_POINTER(iU));

		if (user!=NULL) {			

			nPosts = user.n_respostas + user.n_perguntas;
			if (nPosts > min) {
				set_list(res,minPos,user.id); // colocar na lista

				min=get_min(listaAux,N); // atualiza o menos nPosts
				minPos=get_min_pos(listaAux,N); // atualiza a posição do menor nPosts
			}
		}
	}	
	
	free(listaAux);
	return res;
}		

*/

/* Funcao para Debugging de PostHashT */
void printPostHT(gpointer key, gpointer value, gpointer user_data){
	struct Post* aux = (struct Post*)value;
	int* keyId = (int* )key;
	printf(user_data,*keyId, aux->id, aux->owner_id,aux->titulo);
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

int main(){
	struct TCD_community* teste = init();
	char* path = "../../dumpexemplo/android/";
	
	load(teste, path);
/* Funcao para Debugging de UserHashT*/
	//g_hash_table_foreach(teste->user,(GHFunc)printUserHT,"%d %d %s\n");
	//testeAcessoUserHT(teste,4980640);
/* Funcao para Debugging de PostHashT */
	//g_hash_table_foreach(teste->post,(GHFunc)printPostHT,"%d %d %d %s\n"); 

	/*GList* new = g_hash_table_get_keys(teste->user);
	g_list_foreach(new,print,NULL);*/
	STR_pair new ;
	new = info_from_post(teste,9);
	printf("\nPERGUNTA:\n%s \n%s\n\n",get_fst_str(new),get_snd_str(new));

	new = info_from_post(teste,7);
	printf("\nRESPOSTA À PERGUNTA:\n%s \n%s\n\n",get_fst_str(new),get_snd_str(new));
   	//printf("Tamanho hash: %d\n",g_hash_table_size(teste->user));
  	
  	return 0;
} 


/*	PARA O NOOB DO HPEREIRA98

void ordena (gpointer id, gpointer user, gpointer v){

}


blablabla querry2(TCD com, int N){
	int* v = malloc(sizeof(N));
	long_list l = create;

	g_hash_table_foreach(com->user, ordena, v);

	for(i=0; i<N; i++) set_list(l, i, v[i]);

	return l;
}


*/