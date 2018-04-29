#include "structs.h"

struct TCD_community{
	GHashTable* user;
	GTree* post;
	GHashTable* postAux;
	GHashTable* tags;	
};
void freeIdKey(long* id){
	free(id);
}

void freeTagKey(char* tagName){
	free(tagName);
}



// QUERIES

TAD_community init(){
	struct TCD_community* new = malloc(sizeof(struct TCD_community));
 
  	new->user = g_hash_table_new_full(g_int_hash, g_int_equal, free, (GDestroyNotify)freeUser);
  	new->post = g_tree_new_full((GCompareDataFunc)cmpTreeKey, NULL, (GDestroyNotify)freePostKey, (GDestroyNotify)freePost);
  	new->postAux = g_hash_table_new_full(g_int_hash, g_int_equal, (GDestroyNotify)free, (GDestroyNotify)free);
  	new->tags = g_hash_table_new_full(g_str_hash, g_str_equal, (GDestroyNotify)free, (GDestroyNotify)freeTags);
  		

  	return new;
}


// Funcoes auxiliares ao load. Transformam cada doc_xml em dados inseridos na estrutura.
// Recebem a root do documento e procedem ao processamento dos nodos.

// USERS 

void usersXmlToTAD(TAD_community com, xmlNodePtr doc_root){
	xmlNodePtr cur = doc_root->xmlChildrenNode; 
	/* Debuggin */ int i = 0;

	while(cur){

		if(!xmlStrcmp(cur->name, (const xmlChar*)"row")){

   			xmlChar* id = xmlGetProp(cur, (const xmlChar *)"Id");
   			xmlChar* rep = xmlGetProp(cur, (const xmlChar *)"Reputation");
   			xmlChar* name = xmlGetProp(cur, (const xmlChar *)"DisplayName");
			xmlChar* bio = xmlGetProp(cur, (const xmlChar *)"AboutMe");

   			long* idUser = malloc(sizeof(long));
   			int repUser;
				
   			User new = initUser();  
   				
   			// Nome
   			setUserDisplayName(new, (char*)name); 

   			// ID
   			sscanf((const char*)id, "%li", idUser); 
   			setUserID(new,*idUser);
   			
   			// Reputação
   			sscanf((const char*)rep,"%d", &repUser);
   			setUserReputation(new, repUser);

			// Bio			
			setUserShortBio(new,(char*)bio); 
			 
   			// Inserir conforme o ID
   			g_hash_table_insert(com->user, idUser, new); i++;

   			xmlFree(id);
			xmlFree(name);
			xmlFree(rep);
			xmlFree(bio);
			
   		}
		cur = cur->next;
	}
	long id_aux = -1;
	g_hash_table_remove(com->user, &id_aux);
	/* Debuggin */ printf("Users: %d\n", i);
}

// POSTS

void postsXmlToTAD(TAD_community com, xmlNodePtr doc_root){
	xmlNodePtr cur = doc_root->xmlChildrenNode; 
	/* Debuggin */ int i = 0;

	while(cur){
		
		if(!xmlStrcmp(cur->name, (const xmlChar*)"row")){

			xmlChar* post_type_id = xmlGetProp(cur, (const xmlChar *)"PostTypeId");	
	   		xmlChar* post_id = xmlGetProp(cur, (const xmlChar *)"Id");
	   		xmlChar* user_id = xmlGetProp(cur, (const xmlChar *)"OwnerUserId");
	   		xmlChar* user_display_name = xmlGetProp(cur, (const xmlChar *)"OwnerDisplayName");
	   		xmlChar* titulo = xmlGetProp(cur, (const xmlChar *)"Title");
	   		xmlChar* parent_id = xmlGetProp(cur, (const xmlChar *)"ParentId");
			xmlChar* data = xmlGetProp(cur, (const xmlChar *)"CreationDate");
			xmlChar* tags = xmlGetProp(cur, (const xmlChar *)"Tags");
			xmlChar* score_xml = xmlGetProp(cur, (const xmlChar *)"Score");
			xmlChar* comments = xmlGetProp(cur, (const xmlChar *)"CommentCount");
			xmlChar* answer = xmlGetProp(cur, (const xmlChar *)"AcceptedAnswerId");
			xmlChar* answer_count = xmlGetProp(cur, (const xmlChar *)"AnswerCount");

	   		long* idPost = malloc(sizeof(long));
	   		long idOwner;
	   		long idParent;
	   		int idType = 0;
	   		int score;
	   		int n_comments;
	   		int awnsers;
	   		
	   		Post newPost = initPost();

	   		// Post ID 
			sscanf((const char*)post_id, "%li", idPost); 
			setPostID(newPost, *idPost);
	   				
	   		// Titulo
	   		setPostTitle(newPost, (char*)titulo);

	   		// Owner ID 
	   		sscanf((const char*)user_id, "%li", &idOwner);
	   		setPostOwnerID(newPost, idOwner);

	   		// Type ID
	   		sscanf((const char*)post_type_id, "%d", &idType); 
	   		setPostTypeID(newPost, idType);

	   		// Parent ID
	   		if(parent_id) {
	   			sscanf((const char*)parent_id, "%li", &idParent); 
	   			setPostParentID(newPost, idParent);	   				
	   		}

	   		// Data
	   		setPostDate(newPost, (char*)data);
	   		
	   		// Tags  
	   		setPostTags(newPost, (char*) tags);
		   		   		
	   			
	   		// Score
			sscanf((const char*)score_xml, "%d", &score); 
	   		setPostScore(newPost, score);	   			

	   		// Nº Comments
	   		sscanf((const char*)comments,"%d", &n_comments);
	   		setPostNComments(newPost, n_comments);

	   		// Nº Respostas
	   		if(answer_count){
	   			sscanf((const char*)answer_count, "%d", &awnsers); 
	   			setPostNRespostas(newPost, awnsers);
	   		}				   			

	   		// Owner Reputation && Add Post to User
	   		User user = getUser(com->user, idOwner);

	   		if(user){
	   			int owner_rep = getUserReputation(user);
	   			setPostOwnerRep(newPost, owner_rep);

	   			addUserPost(user, newPost);
	   		}
			
			PostKey key = createPostKey( (char*)data, *idPost);
				
	   		g_tree_insert(com->post, key, newPost);
	   		g_hash_table_insert(com->postAux, idPost, mystrdup((char*) data));
	   		/*Debugging*/ //printf("Inserido %d\n", i);
	   		i++;

	   		xmlFree(post_type_id);	
			xmlFree(post_id);
			xmlFree(user_id);
			xmlFree(titulo);
			xmlFree(parent_id);
			xmlFree(data);
			xmlFree(tags);
			xmlFree(score_xml);
			xmlFree(comments);
			xmlFree(answer);
			xmlFree(user_display_name);
			xmlFree(answer_count);
		}
		cur = cur->next;
	}
	/*Debugging*/ printf("Posts: %d\n", i);
}

// TAGS 

void tagsXmlToTAD(TAD_community com, xmlNodePtr doc_root){
	xmlNodePtr cur = doc_root->xmlChildrenNode; 
	/* Debugging */ int i = 0;

	while(cur){

		if(!xmlStrcmp(cur->name, (const xmlChar*)"row")){

			xmlChar* tag_id = xmlGetProp(cur, (const xmlChar *)"Id");
	   		xmlChar* tag_name = xmlGetProp(cur, (const xmlChar *)"TagName");

		   	Tag new = initTag();

		   	// ID		
			long tagID;
			sscanf((const char*)tag_id, "%li", &tagID);
				
			setTagID(new, tagID);

			// Name
			setTagName(new, (char*)tag_name);

	   		// Inserir conforme Tag Name
	   		g_hash_table_insert(com->tags, mystrdup((char*)tag_name), new);
				
			i++;

			xmlFree(tag_name);
			xmlFree(tag_id);
				
		}
		cur = cur->next;
	}
	/* Debugging */ printf("Tags: %d\n", i);

}



// query 1
STR_pair info_from_post(TAD_community com, long id){
	return info_from_post_aux(com->post, com->postAux, com->user, id);
} 
 

// query 2
LONG_list top_most_active(TAD_community com, int N){
	return top_most_active_aux(com->user,N);
}


// query 3
LONG_pair total_posts(TAD_community com, Date begin, Date end){
	return total_posts_aux(com->post,begin,end);
}


// query 4
LONG_list questions_with_tag(TAD_community com, char* tag, Date begin, Date end){
	return questions_with_tag_aux(com->post,tag,begin,end);
}


// query 5
USER get_user_info(TAD_community com, long id){
	return get_user_info_aux(com->user,id);
}


// query 6
LONG_list most_voted_answers(TAD_community com, int N, Date begin, Date end){
	return most_voted_answers_aux(com->post,N,begin,end);
}


// query 7
LONG_list most_answered_questions(TAD_community com, int N, Date begin, Date end){
	return most_answered_questions_aux(com->post,N,begin,end);
}


// query 8
LONG_list contains_word(TAD_community com, char* word, int N){
	return contains_word_aux(com->post,word,N);
}


// query 9
LONG_list both_participated(TAD_community com, long id1, long id2, int N){
	return both_participated_aux(com->user, com->post, com->postAux, id1, id2, N);
}


// query 10
long better_answer(TAD_community com, long id){
	return better_answer_aux(com->post,com->postAux,id);
}


// query 11
LONG_list most_used_best_rep(TAD_community com, int N, Date begin, Date end){
	return most_used_best_rep_aux(com->user, com->tags, N, begin, end);
}

// Clean

TAD_community clean(TAD_community com){
	g_hash_table_destroy(com->user);
	g_hash_table_destroy(com->postAux);
	g_tree_destroy(com->post);
	g_hash_table_destroy(com->tags);
	free(com);
	return NULL;
}






