#include <load.h>

TAD_community init(){
	struct TCD_community* new = malloc(sizeof(struct TCD_community));

  	GHashTable* new_user_hash = g_hash_table_new(g_int_hash, g_int_equal);
  	GHashTable* new_post_hash = g_hash_table_new(g_int_hash, g_int_equal);
	GHashTable* new_tags_hash = g_hash_table_new(g_str_hash, g_str_equal);
  	
  	new->user = new_user_hash; 
  	new->post = new_post_hash;
  	new->tags = new_tags_hash;

  	return new;
}

TAD_community load(TAD_community com, char* dump_path){
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
				
   				User new = initUser(); 
   				
   				// Nome
   				setUserDisplayName(new, (char*)name); 

   				// ID
   				sscanf((const char*)id, "%d", idUser); 
   				setUserID(new,*idUser);
   				//sscanf((const char*)id, "%d", idUser); 
   				//new->id = *idUser;

   				// Reputação
   				sscanf((const char*)rep,"%d", repUser); 
   				setUserReputacao(new,*repUser); 
   				//sscanf((const char*)rep,"%d", repUser);
   				//new->reputacao = *repUser;
				
				// Nº perguntas/respostas
				setUserNRespostas(new,0);
				setUserNPosts(new,0);
				setUserNPerguntas(new,0);

				// Bio
				
				setUserShortBio(new,(char*)bio); // ter atencao e ver se nao rebenta por ser null
				/*									   // pricipalmente em futuras evocacoes da funcao getUserShortBio
				if(bio){
					new->short_bio = malloc(strlen((const char*)bio) + 1);
					strcpy(new->short_bio, (const char*)bio);
				}
				else new->short_bio = "";
				*/

				// User's Posts 
				initUserPosts(new);
				//new->userPosts = g_array_new (FALSE,TRUE,sizeof(struct Post*));//(elemento no fim a 0,inicilizar a 0,tamnho em bytes dos elems)
			 
   				// Inserir conforme o ID
   				g_hash_table_insert(com->user, idUser, new); i++;
				
   			}
			xmlFree(id);
			xmlFree(name);
			xmlFree(rep);
			xmlFree(bio);
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
				xmlChar* answer = xmlGetProp(cur, (const xmlChar *)"AcceptedAnswerId");


	   			int* idOwner = malloc(sizeof(int));
	   			int* idPost = malloc(sizeof(int));
	   			int* idParent = malloc(sizeof(int));
	   			int* idType = malloc(sizeof(int));
	   			int* score = malloc(sizeof(int));
	   			int* n_comms = malloc(sizeof(int));
				int* acptd = malloc(sizeof(int));

	   			Post new = initPost();
	   				
	   			// Titulo
	   			setPostTitle(new,(char*)titulo);
	   			/*
	   			if(titulo){
	   				new->titulo = malloc(strlen((const char*)titulo) + 1);
	   				strcpy(new->titulo,(const char*)titulo);
	   			}
	   			else new->titulo="";
				*/

	   			// Owner ID - averiguar se novo dump tem posts sem owner id ou nao 
	   			if(user_id){
	   				sscanf((const char*)user_id, "%d", idOwner);
	   				setPostOwnerID(new,*idOwner);
	   			} 
	   			else setPostOwnerID(new,-2);

	   			// Owner Reputation
	   			User user = (User)g_hash_table_lookup(com->user,idOwner);
	   			if (user!=NULL)
	   				setPostOwnerRep(new,getUserReputacao(user));

	   			// Count User's questions and answers 			
				if (user!=NULL) {
					if (*idType == 1) setUserNPerguntas(user,getUserNPerguntas(user)+1);
					else if (*idType == 2) setUserNRespostas(user,getUserNRespostas(user)+1);
					setUserNPosts(user,getUserNPosts(user)+1);
				}

	   			// Post ID
				sscanf((const char*)post_id, "%d", idPost); 
				setPostID(new,*idPost);
	   			//new->id = *idPost;

	   			

	   			// Type ID
	   			sscanf((const char*)post_type_id, "%d", idType); 
	   			setPostTypeID(new,*idType);
	   			//new->type_id = *idType;

	   			// Parent ID
	   			if(parent_id) {
	   				sscanf((const char*)parent_id, "%d", idParent); 
	   				setPostParentID(new,*idParent);
	   				//new->parent_id = *idParent;
	   			}
	   			else setPostParentID(new,-2);

	   			// Owner Display Name
	   			setPostOwnerDisplayName(new,(char*)user_display_name);
	   			/*
	   			if(user_display_name){
	   				new->owner_display_name = malloc(strlen((const char*)user_display_name) + 1);
	   				strcpy(new->owner_display_name,(const char*)user_display_name);
	   			}
	   			else new->owner_display_name = "";
	   			*/

	   			// Data
	   			Date dataPost = atribuiData((char*) data);
	   			setPostDate(new,dataPost);

				// Accepted answer - debugging q10 : COLOCAR EM COMENTÁRIO QUANDO NÃO FOR NECESSÁRIO!! 
	   			/*
	   			if (answer && new->type_id==1) {
	   				sscanf((const char*)answer,"%d", acptd);
	   				new->accepted_answer = *acptd;
	   			}
	   			else new->accepted_answer=-2;	
	   			*/

	   			// Tags   = "<tag><tag>"  
	   			setPostTags(new,(char*)tags);
	   			/*
	   			if(tags){
	   				new->tags = malloc(strlen((const char*)tags) + 1);
	   				strcpy(new->tags, (const char*)tags);
	   			}
	   			else new->tags = "";
				*/
	   			// Score
				sscanf((const char*)score_xml, "%d", score); 
	   			setPostScore(new,*score);
	   			//new->score = *score;

	   			// Nº Upvotes
	   			setPostNUpVotes(new,0);

	   			// Nº Downvotes
	   			setPostNDownVotes(new,0);

	   			// Nº Comments
	   			sscanf((const char*)comments,"%d", n_comms);
	   			setPostNComments(new,*n_comms);
	   			//new->n_comments = *n_comms;

	   			// Nº Respostas
	   			if(getPostTypeID(new)==1){
	   				xmlChar* answercount = xmlGetProp(cur, (const xmlChar *)"AnswerCount");
	   				int* awnsers = malloc(sizeof(int));

	   				sscanf((const char*)answercount, "%d", awnsers); 
	   				setPostNRespostas(new,*awnsers);
	   				//new->n_respostas = *awnsers;
	   			}
	   			else setPostNRespostas(new,-1);

	   			// Add Post to User
				if (user!=NULL){
					g_array_append_val(getUserPosts(user),new);
				}
	   			
	   			// Inserir conforme o Post ID
	   			g_hash_table_insert(com->post, idPost, new);
	   			
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

				Post post = (Post) g_hash_table_lookup(com->post, postID);

				if (post && *votetype == 2) setPostNUpVotes(post,getPostNUpVotes(post)+1);
				else if (post && *votetype == 3) setPostNDownVotes(post,getPostNDownVotes(post)+1);

				i++;
			}
			xmlFree(id_post);
			xmlFree(vote_type);
			cur = cur->next;
		}
	}

	printf("Votes: %d\n", i);
	xmlFreeDoc(doc_votes);

	// TAGS

	i = 0;

	xmlDocPtr doc_tags = xmlParseFile(tags_path);
	if(!doc_tags){
		printf("Document not parsed successfully\n");
	}

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
				int* tagID = malloc(sizeof(int));
				sscanf((const char*)tag_id, "%d", tagID);
				
				setTagID(new, *tagID);

				// Name
				setTagName(new, (char*)tag_name);

				// Ocorrencias
				setTagOcor(new, 0);

	   			// Inserir conforme a Tag ID
	   			g_hash_table_insert(com->tags, tag_name, new);
				
				i++;
				
			}

			xmlFree(tag_id);
 
			cur = cur->next;
		}
	}

	printf("Tags: %d\n", i);
	xmlFreeDoc(doc_tags);

	return(com);		
}
