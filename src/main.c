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
	char* owner_display_name;
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
   			xmlChar* id = xmlGetProp(cur, (const xmlChar *)"Id");
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
			if(post_type_id!=NULL){

	   			xmlChar* post_id = xmlGetProp(cur, (const xmlChar *)"Id");
	   			xmlChar* user_id = xmlGetProp(cur, (const xmlChar *)"OwnerUserId");
	   			xmlChar* user_display_name = xmlGetProp(cur, (const xmlChar *)"OwnerDisplayName");
	   			xmlChar* titulo = xmlGetProp(cur, (const xmlChar *)"Title");
	   			xmlChar* parent_id = xmlGetProp(cur, (const xmlChar *)"ParentId");

	   		

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
			new = create_str_pair(post->titulo, user->display_name);
		}
		else new = create_str_pair(post->titulo, post->owner_display_name);
	}
	return new;
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

int main(){
	struct TCD_community* teste = init();
	char* path = "../../dumpexemplo/android/";
	
	load(teste, path);
/* Funcao para Debugging de UserHashT*/
	//g_hash_table_foreach(teste->user,(GHFunc)printUserHT,"%d %d %s\n");
	//testeAcessoUserHT(teste,4980640);
/* Funcao para Debugging de PostHashT */
	//g_hash_table_foreach(teste->post,(GHFunc)printPostHT,NULL); 


	STR_pair new ;
	new = info_from_post(teste,199);// 199 nao tem owner id apenas owner display name
	printf("\nPERGUNTA:\n%s \n%s\n\n",get_fst_str(new),get_snd_str(new));

	new = info_from_post(teste,7);
	printf("\nRESPOSTA À PERGUNTA:\n%s \n%s\n\n",get_fst_str(new),get_snd_str(new));
   	printf("Tamanho hash: %d\n",g_hash_table_size(teste->user));
  	
  	return 0;
} 

/* INTERROGAÇÃO 2 - Protótipo:

struct pairlist{
	int size;
	LONG_pair *list;
} *PAIR_list;

void insertionSort (gpointer id, gpointer u, gpointer l){
	struct User* user = (User*) u;
	PAIR_list lista = (PAIR_list) l;
		
	int numPosts[];
	int posts = n_respostas+n_perguntas;
	for (int i; i<lista->size; i++) {
		
}


LONG_list top_most_active(TAD community com, int N) {

	PAIR_list lista;
	lista->size=N;
	inicializar lista a 0's.

	LONG_list res=create_list(N);

	g_hash_table_foreach(com->user, insertionSort, lista);
	
	for (int i=0;i<N;i++) 
		set_list(res,i,get_fst_long(lista->list[i]);

	return res;
}


*/
