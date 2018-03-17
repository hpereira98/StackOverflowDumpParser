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
	//int n_posts;
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
};


struct TCD_community{
	GHashTable* user;
	GHashTable* post;	
};


TAD_community init(){
	struct TCD_community* new = malloc(sizeof(struct TCD_community));
  	GHashTable* newUserHash = g_hash_table_new(g_direct_hash, g_direct_equal);
  	GHashTable* newPostHash = g_hash_table_new(g_direct_hash, g_direct_equal);

  	new->user = newUserHash;
  	new->post = newPostHash;

  	return new;
}

TAD_community load(TAD_community com, char* dump_path){
	int i=0;
	char users[10] = "Users.xml";
	char* users_path = malloc(strlen(dump_path)+strlen(users));
	strcpy(users_path,dump_path);
	strcat(users_path,users);
	

	char posts[10] = "Posts.xml";
	char* posts_path = malloc(strlen(dump_path)+strlen(posts));
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
   				
   				new->display_name = malloc(strlen((const char*)name));
   				strcpy(new->display_name,(const char*)name);

   				sscanf((const char*)id, "%d", idUser); 
   				new->id = *idUser;			 
   				
   				g_hash_table_insert(com->user, (gpointer*)idUser, new); i++;
				
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

	   			if(post_id != NULL){printf("4\n");
	   				int* idOwner = malloc(sizeof(int));printf("4\n");
	   				int* idPost = malloc(sizeof(int));printf("5\n");
	   				struct Post* new = g_new(struct Post, 1);printf("6\n");
	   				
	   				// Titulo
	   				new->titulo = malloc(strlen((const char*)titulo));printf("7\n");
	   				strcpy(new->titulo,(const char*)titulo);printf("8\n");

	   				// Owner ID
	   				printf("Ola\n");if(user_id)sscanf((const char*)user_id, "%d", idOwner);else(printf("nao tem owner(?)\n")); printf("9\n");
	   				new->owner_id = *idOwner;printf("10\n");

	   				// Post ID
					sscanf((const char*)post_id, "%d", idPost); 
	   				new->id = *idPost;

	   				/*Debugging*/ printf("A inserir %d\n", i);

	   				// Inserir conforme o Post ID
	   				g_hash_table_insert(com->post, (gpointer*)idPost, new);
	   				
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
	printf("ola\n");
	struct Post* post = (struct Post*)g_hash_table_lookup(com->post, GINT_TO_POINTER(id));
	
	char* titulo = post->titulo;
	gint user_id = post->owner_id;
	
	struct User* user = (struct User*)g_hash_table_lookup(com->user, GINT_TO_POINTER(user_id));

	char* nome = user->display_name;

	STR_pair new = create_str_pair(titulo, nome);

	return new;
}



void iterator(gpointer key, gpointer value, gpointer user_data){
	struct User* aux = (struct User*)value;
	int* keyId = (int* )key;
	printf(user_data,*keyId, aux->id, aux->display_name);
}

void print(gpointer data, gpointer user_data){
	int* aux = (int*)data;
	printf("%d\n",*aux);
}

int main(){
	struct TCD_community* teste = init();
	char* path = "../../dumpexemplo/android/";
	
	load(teste, path);
	
	//g_hash_table_foreach(teste->user,(GHFunc)iterator,"%d %d %s\n"); // imprimir id e display_name

	/*GList* new = g_hash_table_get_keys(teste->user);
	g_list_foreach(new,print,NULL);*/
	STR_pair new ;
	new = info_from_post(teste,9);printf("dd\n");
	printf("%s %s\n",get_fst_str(new),get_fst_str(new));
   	//printf("Tamanho hash: %d\n",g_hash_table_size(teste->user));
  	
  	return 0;
} 
