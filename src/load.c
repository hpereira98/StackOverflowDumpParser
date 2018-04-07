#include <load.h>



void load_aux(GHashTable* com_user, GTree* com_post, GHashTable* com_postAux, GHashTable* com_tags, char* dump_path){
	int i = 0;

	char* users = "Users.xml";
	char* users_path = malloc(strlen(dump_path)+strlen(users) + 1);
	strcpy(users_path, dump_path);
	strcat(users_path, users);

	char* posts = "Posts.xml";
	char* posts_path = malloc(strlen(dump_path)+strlen(posts) + 1);
	strcpy(posts_path, dump_path);
	strcat(posts_path, posts);

	char* votes = "Votes.xml";
	char* votes_path = malloc(strlen(dump_path)+strlen(votes)+1);
	strcpy(votes_path, dump_path);
	strcat(votes_path, votes);
	
	char* tags = "Tags.xml";
	char* tags_path = malloc(strlen(dump_path)+strlen(tags)+1);
	strcpy(tags_path, dump_path);
	strcat(tags_path, tags);
		


	// USERS

	/*Debugging*/ clock_t users_begin = clock();

	xmlDocPtr doc_users = xmlParseFile(users_path);
	if(!doc_users){
		printf("Document not parsed successfully\n");
	}

	/*Debugging*/ clock_t users_opened = clock();	
	

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
   				long* idUser = malloc(sizeof(long));
   				int* repUser = malloc(sizeof(int));
				
   				User new = initUser(); 
   				
   				// Nome
   				setUserDisplayName(new, (char*)name); 

   				// ID
   				sscanf((const char*)id, "%li", idUser); 
   				setUserID(new,*idUser);
   			
   				// Reputação
   				sscanf((const char*)rep,"%d", repUser); 
   				setUserReputacao(new,*repUser); 	
				
				// Nº perguntas/respostas
				setUserNRespostas(new,0);
				setUserNPosts(new,0);
				setUserNPerguntas(new,0);

				// Bio			
				setUserShortBio(new,(char*)bio); 
				
				// User's Posts 
				initUserPosts(new);
			 
   				// Inserir conforme o ID
   				g_hash_table_insert(com_user, idUser, new); i++;
				
   			}
			xmlFree(id);
			xmlFree(name);
			xmlFree(rep);
			xmlFree(bio);
			cur = cur->next;
		}
	}
	printf("Users: %d\n", i);
	/*Debugging*/ clock_t users_end = clock(); 
	/*Debugging*/ printf("Tempo abrir xmlUsers' = %f\n", (double)(users_opened-users_begin)/CLOCKS_PER_SEC);
	/*Debugging*/ printf("Tempo processar Users' = %f\n", (double)(users_end-users_opened)/CLOCKS_PER_SEC);

	xmlFreeDoc(doc_users);

	// POSTS
	i=0;
	/*Debugging*/ clock_t posts_begin = clock();

	xmlDocPtr doc_posts = xmlParseFile(posts_path);
	if(!doc_posts){
		printf("Document not parsed successfully\n");
	}

	/*Debugging*/ clock_t posts_opened = clock();	
	

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
				xmlChar* answer = xmlGetProp(cur, (const xmlChar *)"AcceptedAnswerId");


	   			long* idOwner = malloc(sizeof(long));
	   			long* idPost = malloc(sizeof(long));
	   			long* idParent = malloc(sizeof(long));
	   			int* idType = malloc(sizeof(int));
	   			int* score = malloc(sizeof(int));
	   			int* n_comms = malloc(sizeof(int));

	   			Post newPost = initPost();
	   			PostAux newPostAux = initPostAux();
	   				
	   			// Titulo
	   			setPostTitle(newPost,(char*)titulo);

	   			// Owner ID 
	   			sscanf((const char*)user_id, "%li", idOwner);
	   			setPostOwnerID(newPost,*idOwner);
	   			

	   			// Owner Reputation
	   			User user = (User)g_hash_table_lookup(com_user,idOwner);
	   			if (user!=NULL)
	   				setPostOwnerRep(newPost,getUserReputacao(user));

	   			// Count User's questions and answers 			
				if (user!=NULL) {
					if (*idType == 1) setUserNPerguntas(user,getUserNPerguntas(user)+1);
					else if (*idType == 2) setUserNRespostas(user,getUserNRespostas(user)+1);
					setUserNPosts(user,getUserNPosts(user)+1);
				}

	   			// Post ID 
				sscanf((const char*)post_id, "%li", idPost); 
				setPostID(newPost,*idPost);

	   			

	   			// Type ID
	   			sscanf((const char*)post_type_id, "%d", idType); 
	   			setPostTypeID(newPost,*idType);
	   			

	   			// Parent ID
	   			if(parent_id) {
	   				sscanf((const char*)parent_id, "%li", idParent); 
	   				setPostParentID(newPost,*idParent);
	   				
	   			}
	   			else setPostParentID(newPost,-2);

	   			// Owner Display Name
	   			setPostOwnerDisplayName(newPost,(char*)user_display_name);

	   			// Data
	   			setPostDate(newPost, (char*)data);
	   			setPostAuxDate(newPostAux,(char*)data);

				// Accepted answer - debugging q10 : COLOCAR EM COMENTÁRIO QUANDO NÃO FOR NECESSÁRIO!! 
	   			/*
	   			if (answer && new->type_id==1) {
	   				sscanf((const char*)answer,"%d", acptd);
	   				new->accepted_answer = *acptd;
	   			}
	   			else new->accepted_answer=-2;	
	   			*/

	   			// Tags   = "<tag><tag>"  
	   			setPostTags(newPost,(char*)tags);
	   			
	   			// Score
				sscanf((const char*)score_xml, "%d", score); 
	   			setPostScore(newPost,*score);
	   			

	   			// Nº Upvotes
	   			setPostAuxNUpVotes(newPostAux,0);

	   			// Nº Downvotes
	   			setPostAuxNDownVotes(newPostAux,0);

	   			// Nº Comments
	   			sscanf((const char*)comments,"%d", n_comms);
	   			setPostNComments(newPost,*n_comms);

	   			// Nº Respostas
	   			if(getPostTypeID(newPost)==1){
	   				xmlChar* answercount = xmlGetProp(cur, (const xmlChar *)"AnswerCount");
	   				int* awnsers = malloc(sizeof(int));

	   				sscanf((const char*)answercount, "%d", awnsers); 
	   				setPostNRespostas(newPost,*awnsers);
	   			}
	   			else setPostNRespostas(newPost,-1);

	   			// Add Post to User !! ver se ao aplicar encapsulamento nao compensa passar apenas os ids
				if (user!=NULL){
					g_array_append_val(getUserPosts(user),newPost);
				}

				char* keyDate = mystrdup((char*)data);
				char* keyID = mystrdup((char*)post_id);

	   			STR_pair key = create_str_pair(keyDate,keyID);
				
	   			// Inserir conforme a Data
	   			g_tree_insert(com_post, key, newPost);
	   			g_hash_table_insert(com_postAux,idPost,newPostAux);
	   			/*Debugging*/ //printf("Inserido %d\n", i);
	   			i++;

	   			
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
			}
			xmlFree(post_type_id);
			cur = cur->next;
		}
	}

	/*Debugging*/ printf("Posts: %d\n", i);

	/*Debugging*/ clock_t posts_end = clock(); 
	/*Debugging*/ printf("Tempo abrir xmlPost' = %f\n", (double)(posts_opened-posts_begin)/CLOCKS_PER_SEC);
	/*Debugging*/ printf("Tempo processar posts' = %f\n", (double)(posts_end-posts_opened)/CLOCKS_PER_SEC);
	
	/*Debugging*/ i=0;
	/*Debugging*/// g_tree_foreach(com_post,printPostTree,&i);
	/*Debugging*/ //g_hash_table_foreach(com_postAux,printPostAuxHT,&i);

	xmlFreeDoc(doc_posts);

	// VOTES

	i = 0;

	/*Debugging*/ clock_t votes_begin = clock();

	xmlDocPtr doc_votes = xmlParseFile(votes_path);
	if(!doc_votes){
		printf("Document not parsed successfully\n");
	}

	/*Debugging*/ clock_t votes_opened = clock();	

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
			
				long* postID = malloc(sizeof(long));
				int* votetype = malloc(sizeof(int));

				sscanf((const char*)id_post, "%li", postID);
				sscanf((const char*)vote_type,"%d", votetype);

				PostAux postAux = (PostAux) g_hash_table_lookup(com_postAux,postID);
				if (postAux && *votetype == 2) setPostAuxNUpVotes(postAux,getPostAuxNUpVotes(postAux)+1);
				else if (postAux && *votetype == 3) setPostAuxNDownVotes(postAux,getPostAuxNDownVotes(postAux)+1);

				i++;
			}
			xmlFree(id_post);
			xmlFree(vote_type);
			cur = cur->next;
		}
	}

	printf("Votes: %d\n", i);
	/*Debugging*/ clock_t votes_end = clock(); 
	/*Debugging*/ printf("Tempo abrir xmlVotes' = %f\n", (double)(votes_opened-votes_begin)/CLOCKS_PER_SEC);
	/*Debugging*/ printf("Tempo processar Votes' = %f\n", (double)(votes_end-votes_opened)/CLOCKS_PER_SEC);

	xmlFreeDoc(doc_votes);

	// TAGS

	i = 0;

	/*Debugging*/ clock_t tags_begin = clock();

	xmlDocPtr doc_tags = xmlParseFile(tags_path);
	if(!doc_tags){
		printf("Document not parsed successfully\n");
	}

	/*Debugging*/ clock_t tags_opened = clock();	
	

	cur = xmlDocGetRootElement(doc_tags);
	if(!cur){
		printf("Empty Document\n");
		xmlFreeDoc(doc_tags);
	}
	else{		
		cur = cur->xmlChildrenNode;
		while(cur){


			xmlChar* tag_id = xmlGetProp(cur, (const xmlChar *)"Id");

	   		if(tag_id){
	   			xmlChar* tag_name = xmlGetProp(cur, (const xmlChar *)"TagName");
		   		Tag new = initTag();

		   		// ID		
				long* tagID = malloc(sizeof(long));
				sscanf((const char*)tag_id, "%li", tagID);
				
				setTagID(new, *tagID);

				// Name
				setTagName(new, (char*)tag_name);

				// Ocorrencias
				setTagOcor(new, 0);

	   			// Inserir conforme a Tag ID
	   			g_hash_table_insert(com_tags, tag_name, new);
				
				i++;
				
			}

			xmlFree(tag_id);
 
			cur = cur->next;
		}
	}

	printf("Tags: %d\n", i);
	/*Debugging*/ clock_t tags_end = clock(); 
	/*Debugging*/ printf("Tempo abrir xmlTags' = %f\n", (double)(tags_opened-tags_begin)/CLOCKS_PER_SEC);
	/*Debugging*/ printf("Tempo processar Tags' = %f\n", (double)(tags_end-tags_opened)/CLOCKS_PER_SEC);

	xmlFreeDoc(doc_tags);

		
}
