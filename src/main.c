#include <date.h>
#include <stdio.h>
#include <interface.h>
#include <libxml/parser.h>
#include <gmodule.h>
#include <glib.h>
#include <string.h>

// teste: passar para um array de inteiros os primeiros 50 id's presentes em Users.xml


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
};



struct TCD_community{
	GHashTable* user;
	GHashTable* post;
};


TAD_community init(){
	struct TCD_community* new = malloc(sizeof(struct TCD_community));
  	GHashTable* newUserHash = g_hash_table_new(g_direct_hash, g_direct_equal);
  	GHashTable* newPostHash = g_hash_table_new(g_int_hash, g_int_equal);

  	new->user = newUserHash;
  	new->post = newPostHash;

  	return new;
}

TAD_community load(TAD_community com, char* dump_path){
	xmlChar* id; 
	xmlChar* name; 
	int i=0;//so para comparar tamanho da hashT com numero insercoes
;

	xmlDocPtr doc = xmlParseFile(dump_path);
	if(!doc){
		printf("Document not parsed successfully\n");
	}

	xmlNodePtr cur = xmlDocGetRootElement(doc);
	if(!cur){
		printf("Empty Document\n");
		xmlFreeDoc(doc);
	}
	else{		
		cur = cur->xmlChildrenNode;
		while(cur){
   			id = xmlGetProp(cur, (const xmlChar *)"Id");
   			name = xmlGetProp(cur, (const xmlChar *)"DisplayName");
   			if(id != NULL){
   				int* idUser=malloc(sizeof(int));
   				struct User* new = g_new(struct User,1);//forma de fazer malloc
   				new->display_name = malloc(strlen((const char*)name));
   				
   				sscanf((const char*)id, "%d",idUser); 
   				new->id = *idUser;			 
   				strcpy(new->display_name,(const char*)name);

   				g_hash_table_insert(com->user, (gpointer*)idUser, new); i++;
   				
   				

   				//printf("Teste: %d %s\n", new->id, new->display_name); 
				
   			}
			xmlFree(id);
			xmlFree(name);
			cur = cur->next;
		;
		}
	}
	printf("Num insercoes: %d\n",i );
	xmlFreeDoc(doc);

	return(com);		
}


/*
STR_pair info_from_post(TAD_community com, int id){
}
*/


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
	char* path = "../../dumpexemplo/android/Users.xml";
	
	load(teste, path);
	
	//g_hash_table_foreach(teste->user,(GHFunc)iterator,"%d %d %s\n");//imprimir id e display_name

	GList* new = g_hash_table_get_keys(teste->user);
	g_list_foreach(new,print,NULL);

   	printf("Tamanho hash: %d\n",g_hash_table_size(teste->user));
  	return 0;
} 
