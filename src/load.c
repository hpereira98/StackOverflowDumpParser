#include <load.h>

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

	char* votes = "Votes.xml";
	char* votes_path = malloc(strlen(dump_path)+strlen(votes)+1);
	strcpy(votes_path,dump_path);
	strcat(votes_path,votes);
	


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
   			xmlChar* rep = xmlGetProp(cur, (const xmlChar *)"Reputation");
   			xmlChar* name = xmlGetProp(cur, (const xmlChar *)"DisplayName");
			xmlChar* bio = xmlGetProp(cur, (const xmlChar *)"AboutMe");

   			if(id != NULL){
   				int* idUser = malloc(sizeof(int));
   				int* repUser = malloc(sizeof(int));
				
   				struct User* new = g_new(struct User, 1);//forma de fazer malloc
   				
   				// Nome
   				new->display_name = malloc(strlen((const char*)name) + 1);
   				strcpy(new->display_name,(const char*)name);

   				// ID
   				sscanf((const char*)id, "%d", idUser); 
   				new->id = *idUser;

   				// Reputação
   				sscanf((const char*)rep,"%d", repUser);
   				new->reputacao = *repUser;
				
				// Nº perguntas/respostas
				new->n_perguntas = 0;
				new->n_respostas = 0;
				new->n_posts = 0;

				// Bio
				if(bio){
					new->short_bio = malloc(strlen((const char*)bio) + 1);
					strcpy(new->short_bio, (const char*)bio);
				}
				else new->short_bio = "";

				// User's Posts 
				new->userPosts = g_array_new (FALSE,TRUE,sizeof(struct Post*));//(elemento no fim a 0,inicilizar a 0,tamnho em bytes dos elems)
			 
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
				xmlChar* comments = xmlGetProp(cur, (const xmlChar *)"CommentCount");


	   			int* idOwner = malloc(sizeof(int));
	   			int* idPost = malloc(sizeof(int));
	   			int* idParent = malloc(sizeof(int));
	   			int* idType = malloc(sizeof(int));
	   			int* score = malloc(sizeof(int));
	   			int* n_comms = malloc(sizeof(int));

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

	   			// Owner Reputation
	   			struct User* user = (struct User*)g_hash_table_lookup(com->user,idOwner);
	   			if (user!=NULL)
	   				new->owner_rep=user->reputacao;

	   			// Count User's questions and answers 			
				if (user!=NULL) {
					if (*idType == 1) (user->n_perguntas)++;
					else if (*idType == 2) (user->n_respostas)++;
					(user->n_posts)++;
				}

				

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
	   			
	   			// Tags   = "<tag><tag>"  
	   			if(tags){
	   				new->tags = malloc(strlen((const char*)tags) + 1);
	   				strcpy(new->tags, (const char*)tags);
	   			}
	   			else new->tags = "";

	   			// Score
				sscanf((const char*)score_xml, "%d", score); 
	   			new->score = *score;

	   			// Nº Upvotes
	   			new->n_upvotes=0;

	   			// Nº Downvotes
	   			new->n_downvotes=0;

	   			// Nº Comments
	   			sscanf((const char*)comments,"%d", n_comms);
	   			new->n_comments = *n_comms;

	   			// Nº Respostas
	   			if(new->type_id == 1){
	   				xmlChar* answercount = xmlGetProp(cur, (const xmlChar *)"AnswerCount");
	   				int* awnsers = malloc(sizeof(int));

	   				sscanf((const char*)answercount, "%d", awnsers); 
	   				new->n_respostas = *awnsers;
	   			}
	   			else new->n_respostas = -1;

	   			// Add Post to User
				if (user!=NULL){
					g_array_append_val(user->userPosts,new);
				}

	   			// Accepted answer - debugging q10 : COLOCAR EM COMENTÁRIO QUANDO NÃO FOR NECESSÁRIO!! 
	   			/*
	   			if (new->type_id==1) {
	   				xmlChar* answer = xmlGetProp(cur, (const xmlChar *)"AcceptedAnswerId");
					int* a_answer = malloc(sizeof(int));

	   				sscanf((const char*)answer,"%d", a_answer);
	   				new->accepted_answer = *a_answer;
	   			}
	   			else new->accepted_answer=-2;
	   			*/
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

	// VOTES

	i = 0;

	xmlDocPtr doc_votes = xmlParseFile(votes_path);
	if(!doc_votes){
		printf("Document not parsed successfully\n");
	}

	cur = xmlDocGetRootElement(doc_votes);
	if(!cur){
		printf("Empty Document\n");
		xmlFreeDoc(doc_votes);
	}
	else{		
		cur = cur->xmlChildrenNode;
		while(cur){

			xmlChar* id_post = xmlGetProp(cur, (const xmlChar *)"PostId");
			xmlChar* vote_type = xmlGetProp(cur, (const xmlChar *)"VoteTypeId");

			if(id_post && vote_type){
			
				int* postID = malloc(sizeof(int));
				int* votetype = malloc(sizeof(int));

				sscanf((const char*)id_post, "%d", postID);
				sscanf((const char*)vote_type,"%d", votetype);

				struct Post* post = (struct Post*)g_hash_table_lookup(com->post, postID);

				if (post && *votetype == 2) (post->n_upvotes)++;
				else if (post && *votetype == 3) (post->n_downvotes)++;

				i++;
			}
			xmlFree(id_post);
			xmlFree(vote_type);
			cur = cur->next;
		}
	}

	printf("Votes: %d\n", i);
	xmlFreeDoc(doc_votes);

	return(com);		
}