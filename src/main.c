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
  	GHashTable* newUserHash = g_hash_table_new(g_int_hash, g_int_equal);
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
   				
   				g_hash_table_insert(com->user, idUser, new); i++;
				
   			}
			xmlFree(id);
			xmlFree(name);
			cur = cur->next;
		}
	}
	printf("Users: %d\n", i);
	xmlFreeDoc(doc_users);

	
	
	return(com);		
}



STR_pair info_from_post(TAD_community com, int id){
	
	/* Debugging */ printf("A executar info_from_post\n");

	struct Post* post = malloc(sizeof(struct Post));
	post = (struct Post*)g_hash_table_lookup(com->post, GINT_TO_POINTER(id));
	
	/* Debugging */ printf("Alocou memória para a estrutura Post\n");

	//gint user_id = (gint)post->owner_id; // O PROBLEMA ESTÁ AQUI

	/* Debugging */ printf("Atribuiu o valor a user_id\n");

	struct User* user = malloc(sizeof(struct User));
	user = (struct User*)g_hash_table_lookup(com->user, GINT_TO_POINTER(17)); // substituir por 17 o user_id

	/* Debugging */ printf("Alocou memória para a estrutura User\n");

	/* Debugging */ printf("%s - %s", post->titulo, user->display_name); // não chega aqui caso esteja 17

	STR_pair new = create_str_pair(post->titulo, user->display_name);

	/* Debugging */ printf("%s %s\n", get_fst_str(new), get_fst_str(new));
	
	return new;
}


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
	g_hash_table_foreach(teste->user,(GHFunc)printUserHT,"%d %d %s\n");
	testeAcessoUserHT(teste,4980640);
/* Funcao para Debugging de PostHashT */
	//g_hash_table_foreach(teste->post,(GHFunc)printPostHT,"%d %d %d %s\n"); 

	/*GList* new = g_hash_table_get_keys(teste->user);
	g_list_foreach(new,print,NULL);*/
	//STR_pair new ;
	//new = info_from_post(teste,9);printf("dd\n");
	//printf("%s %s\n",get_fst_str(new),get_fst_str(new));
   	//printf("Tamanho hash: %d\n",g_hash_table_size(teste->user));
  	
  	return 0;
} 
