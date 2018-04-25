#include "structs.h"

struct user{
	long id; // user id
	char* display_name; // username
	int n_perguntas; // número de perguntas
	int n_respostas; // número de respostas
	int n_posts; // número total de posts
	int reputacao; // reputacao
	char* short_bio; // descrição do user
	GArray* userPosts;

};

struct post{
	long id;
	char* titulo;
	long owner_id;
	int owner_rep;
	int type_id;
	long parent_id;
	char* data;
	GArray* tags;
	int score;
	int n_comments;
	int n_respostas;
	// int accepted_answer; // testar q10 - POR EM COMENTARIO QUANDO NAO FOR NECESSARIO
};

struct postAux{
	int n_upvotes;
	int n_downvotes;
	char* data;
};

struct tag{
	char* name;
	long id;
	int ocorrencias;
};

struct postKey{
	char* data;
	long id;
};

struct TCD_community{
	GHashTable* user;
	GTree* post;
	GHashTable* postAux;
	GHashTable* tags;	
};



// QUERIES

TAD_community init(){
	struct TCD_community* new = malloc(sizeof(struct TCD_community));

  	GHashTable* new_user_hash = g_hash_table_new(g_int_hash, g_int_equal);
  	GTree* new_post_tree = g_tree_new((GCompareFunc)cmpTreeKey);
  	GHashTable* new_postAux_hash = g_hash_table_new(g_int_hash, g_int_equal);
	GHashTable* new_tags_hash = g_hash_table_new(g_str_hash, g_str_equal);
  	
  	new->user = new_user_hash;
  	new->post = new_post_tree;
  	new->postAux = new_postAux_hash;
  	new->tags = new_tags_hash;	

  	return new;
}


// Funcoes auxiliares ao load. Transformam cada doc_xml em dados inseridos na estrutura.
// Recebem a root do documento e procedem ao processamento dos nodos.

// USERS 

void usersXmlToTAD(TAD_community com, xmlNodePtr doc_root){
	xmlNodePtr cur = doc_root->xmlChildrenNode; 
	/* Debuggin */ int i = 0;

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
   			g_hash_table_insert(com->user, idUser, new); i++;			
   		}

		xmlFree(id);
		xmlFree(name);
		xmlFree(rep);
		xmlFree(bio);

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
	   		User user = (User)g_hash_table_lookup(com->user,idOwner);
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

	   		// Data
	   		setPostDate(newPost, (char*)data);
	   		setPostAuxDate(newPostAux,(char*)data);
	   		
	   		// Tags   = "<tag><tag>" 
	   		if(tags){ 
		   		int j = 0;
		   		GArray* new = g_array_new(FALSE, FALSE, sizeof(char*));
				while(tags[j]!='\0'){
		   			char* next_tag = mystrdup(nextTag((char*)tags, &j));	   			
					if(next_tag[0]!='\0'){
						g_array_append_val(new, next_tag);
						//DEBUG(printf("%s\n", next_tag););
					}
		   		}
		   		setPostTags(newPost, new);
		   	}
		   	else setPostTags(newPost, NULL);
	   		
	   			
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

			PostKey key = createPostKey( (char*)data, *idPost);
				
	   		g_tree_insert(com->post, key, newPost);
	   		g_hash_table_insert(com->postAux,idPost,newPostAux);
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
	/*Debugging*/ printf("Posts: %d\n", i);
}

// TAGS 

void tagsXmlToTAD(TAD_community com, xmlNodePtr doc_root){
	xmlNodePtr cur = doc_root->xmlChildrenNode; 
	/* Debugging */ int i = 0;

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

	   		// Inserir conforme Tag Name

	   		g_hash_table_insert(com->tags, tag_name, new);
				
			i++;
				
		}

		xmlFree(tag_id);
 
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


// Hash PostAux para Post 

Post getPost(GTree* com_post, GHashTable* com_postAux, long id){
	Post post  = NULL;

	PostAux postAux = (PostAux)g_hash_table_lookup(com_postAux, &id);

	/* Debugging */ //if(!postAux) printf("PostAux with ID: %ld not found\n",id);
	
	if(postAux){

		char* postDate = getPostAuxDate(postAux);
	
		char  postID[50]; 
		sprintf (postID, "%lu", id);

		PostKey key = createPostKey( postDate, id);

		/* Debugging */ // printf("%s %s\n",get_fst_str(postKey),get_snd_str(postKey) );

		post = (Post)g_tree_lookup(com_post, key);

		/* Debugging */ if(!post) printf("Post %ld - %s not found\n", id, postDate);
	}

	return post;
}



// USERS

// Inits

User initUser(){
	User new = malloc(sizeof(struct user));
	return new;
}

void initUserPosts(User user){
	user->userPosts = g_array_new (FALSE,TRUE,sizeof(struct post*));
}


// Getters

long getUserID(User user){
	return user->id;
}

char* getUserDisplayName(User user){
	return mystrdup(user->display_name);
}

int getUserReputacao(User user){
	return user->reputacao;
}

int getUserNPerguntas(User user){
	return user->n_perguntas;
}

int getUserNRespostas(User user){
	return user->n_respostas;
}

int getUserNPosts(User user){
	return user->n_posts;
}

char* getUserShortBio(User user){
	return mystrdup(user->short_bio);
}

GArray* getUserPosts(User user){ // copiar todos para um novo?
	return user->userPosts;
}

GArray* getClonedUserPosts(User user){
	int size = (user->userPosts)->len;
	Post aux;
	GArray * new = g_array_new(FALSE,TRUE,sizeof(struct post*));

	for(int i=0; i<size;i++){
		aux = g_array_index(user->userPosts,Post,i);
		g_array_append_val(new,aux);
	}

	return new;
}


// Setters

void setUserID(User user, long id){
	user->id = id;
}

void setUserDisplayName(User user, char* display_name){
	user->display_name = mystrdup(display_name);
}

void setUserReputacao(User user, int reputacao){
	user->reputacao = reputacao;
}

void setUserNPerguntas(User user, int n_perguntas){
	user->n_perguntas = n_perguntas;
}

void setUserNRespostas(User user,int n_respostas){
	user->n_respostas = n_respostas;
}

void setUserNPosts(User user, int n_posts){
	user->n_posts = n_posts;
}

void setUserShortBio(User user, char* short_bio){
	 user->short_bio = mystrdup(short_bio);
}


// Cleaner

void freeUser (User user) {
	free(user->display_name);
	free(user->short_bio);
	g_array_free(user->userPosts,TRUE);
	free(user);
}

// POSTS

// Init

Post initPost(){
	Post new = malloc(sizeof(struct post));
	return new;
}


// Getters

long getPostID(Post post){
	return post->id;
}

char* getPostTitle(Post post){
	return mystrdup(post->titulo);
}

long getPostOwnerID(Post post){
	if(post->owner_id != -2) return post->owner_id;
	else return post->id;
}

int getPostOwnerRep(Post post){
	return post->owner_rep;
}

int getPostTypeID(Post post){
	return post->type_id;
}

long getPostParentID(Post post){
	return post->parent_id;
}

char* getPostDate(Post post){
	return mystrdup(post->data);
}

char* getPostSimpleDate(Post post){ // "AAAA-MM-DD"
	char* date = getPostDate(post);
	return g_strndup(date,10);
}


GArray* getPostTags(Post post){
	return post->tags;
}

int getPostScore(Post post){
	return post->score;
}

int getPostNComments(Post post){
	return post->n_comments;
}

int getPostNRespostas(Post post){
	return post->n_respostas;
}

// Setters

void setPostID(Post post, long id){
	post->id = id;
}

void setPostTitle(Post post, char* titulo){
	post->titulo = mystrdup(titulo); 
}

void setPostOwnerID(Post post, long owner_id){
	post->owner_id = owner_id; 		
}

void setPostOwnerRep(Post post, int owner_rep){
	post->owner_rep = owner_rep; 
}

void setPostTypeID(Post post, int type_id){
	post->type_id = type_id;
}

void setPostParentID(Post post, long parent_id){
	post->parent_id = parent_id; 
}

void setPostDate(Post post, char* data){
	post->data = mystrdup(data);
}

void setPostTags(Post post, GArray* tags){
	post->tags = tags; 
}


void setPostScore(Post post, int score){
	post->score = score;
}

void setPostNComments(Post post, int n_comments){
	post->n_comments =  n_comments;
}


void setPostNRespostas(Post post, int n_respostas){
	post->n_respostas = n_respostas;
}

// Cleaner

void freePost (Post post) {
	free(post->titulo);
	free(post->data);
	free(post->tags);
	free(post);	
}


// PostKey

// Init

PostKey initPostKey(){
	PostKey new = malloc(sizeof(struct postKey));

	return new;
}

PostKey createPostKey(char* data, long id){
	PostKey new = initPostKey();

	setPostKeyDate(new, data);
	setPostKeyID(new, id);

	return new;
}


// Getters

char* getPostKeyDate(PostKey post_key){
	return mystrdup(post_key->data);
}

long getPostKeyID(PostKey post_key){
	return post_key->id;
}

// Setters

void setPostKeyDate(PostKey post_key, char* data){
	post_key->data = mystrdup(data);
}

void setPostKeyID(PostKey post_key, long id){
	post_key->id = id;
}



// PostAux

// Init

PostAux initPostAux(){
	PostAux new = malloc(sizeof(struct postAux));
	return new;
}

// Getters

char* getPostAuxDate(PostAux postAux){
	return mystrdup(postAux->data);
}

int getPostAuxNDownVotes(PostAux postAux){
	return postAux->n_downvotes;
}

int getPostAuxNUpVotes(PostAux postAux){
	return postAux->n_upvotes;
}


// Setters

void setPostAuxDate(PostAux postAux, char* data){
	postAux->data = mystrdup(data);
}

void setPostAuxNDownVotes(PostAux postAux, int n_downvotes){
	postAux->n_downvotes = n_downvotes; 
}

void setPostAuxNUpVotes(PostAux postAux, int n_upvotes){
	postAux->n_upvotes = n_upvotes; 
}

// Tags

// Init 

Tag initTag(){
	Tag new = malloc(sizeof(struct tag));
	return new;
}

Tag createTag(char* name, long id, int ocorrencias){
	Tag new = initTag();

	setTagName(new, name);
	setTagID(new, id);
	setTagOcor(new, ocorrencias);

	return new;
}

// Getters

char* getTagName(Tag tag){
	return mystrdup(tag->name);
}

long getTagID(Tag tag){
	return tag->id;
}

int getTagOcor(Tag tag){
	return tag->ocorrencias;
}

// Setters 

void setTagName(Tag tag, char* name){
	tag->name = mystrdup(name); 
}

void setTagID(Tag tag, long id){
	tag->id = id;
}

void setTagOcor(Tag tag, int ocor){
	tag->ocorrencias = ocor;
}

// Cleaner

void freeTags (Tag tag) {
	free(tag->name);
	free(tag);
} 


