#include <date.h>
#include <stdio.h>
#include <interface.h>
#include <libxml/parser.h>

// teste: passar para um array de inteiros os primeiros 50 id's presentes em Users.xml
// !!!!! prototipo load() alterado

struct TCD_community {
	int* info;
};


TAD_community init(){
  	struct TCD_community* new = malloc(sizeof(struct TCD_community));
  	new->info = malloc(sizeof(int)*100);
  	return new;
}

void load(TAD_community com){

	xmlChar* id; 
	int i=0;

	xmlDocPtr doc = xmlParseFile("/Users/pedroferreira/Desktop/Li3/dumpExemplo/android/Users.xml");
	if(!doc){
		printf("Document not parsed successfully\n");
	}

	xmlNodePtr cur = xmlDocGetRootElement(doc);
	if(!cur){
		printf("Empty Document\n");
		xmlFreeDoc(doc);
	}

	else {		
			cur = cur->xmlChildrenNode;
			while(cur && i<50){
		   			id = xmlGetProp(cur, (const xmlChar *)"Id");
		   			if(id!=NULL) sscanf((const char*)id, "%d", &(com->info)[i++]);
					xmlFree(id);
					cur = cur->next;
			}
		}

	xmlFreeDoc(doc);		
}




int main(){
  struct TCD_community* teste = init();
  load(teste);
  for(int i=0;i<50;i++)
  	printf("%d\n", (teste->info)[i]);
  return 0;
} 
