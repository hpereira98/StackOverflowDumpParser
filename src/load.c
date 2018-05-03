#include <load.h>

TAD_community load (TAD_community com, char* dump_path){

	char* users = "Users.xml";
	char* users_path = malloc(strlen(dump_path)+strlen(users) + 1);
	strcpy(users_path, dump_path);
	strcat(users_path, users);

	char* posts = "Posts.xml";
	char* posts_path = malloc(strlen(dump_path)+strlen(posts) + 1);
	strcpy(posts_path, dump_path);
	strcat(posts_path, posts);
	
	char* tags = "Tags.xml";
	char* tags_path = malloc(strlen(dump_path)+strlen(tags)+1);
	strcpy(tags_path, dump_path);
	strcat(tags_path, tags);
		
	char* xml_docs_path[3] = {users_path, tags_path, posts_path};

	
	for(int i=0; i<3; i++){

		DEBUG(clock_t doc_begin = clock());
		xmlDocPtr xml_doc = xmlParseFile(xml_docs_path[i]);
		if(!xml_doc){
			printf("Document at %s not parsed successfully\n", xml_docs_path[i]);
		}
		DEBUG(clock_t doc_opened = clock());	
	
		xmlNodePtr doc_root = xmlDocGetRootElement(xml_doc);

		if(!doc_root){
			printf("Empty Document -> %s \n", xml_docs_path[i]);
			xmlFreeDoc(xml_doc);
		}
		else	
			switch(i){

				case 0 :
					usersXmlToTAD(com, doc_root);
					break;

				case 1 :
					tagsXmlToTAD(com, doc_root);
					break;

				case 2 :
					postsXmlToTAD(com, doc_root);
					break;
					

			}

		DEBUG( clock_t doc_end = clock() ); 
		DEBUG( printf("Tempo abrir %s' = %f\n", xml_docs_path[i] , (double)(doc_opened-doc_begin)/CLOCKS_PER_SEC));
		DEBUG( printf("Tempo processar %s' = %f\n",  xml_docs_path[i], (double)(doc_end-doc_opened)/CLOCKS_PER_SEC));

		xmlFreeDoc(xml_doc);
	}

	free(users_path);
	free(posts_path);
	free(tags_path);
	
	return com;	
}
