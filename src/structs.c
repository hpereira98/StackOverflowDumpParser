#include "structs.h"

struct user{
	long id; // user id
	char* display_name; // username
	int n_perguntas; // número de perguntas
	int n_respostas; // número de respostas
	int n_posts; // número total de posts
	int reputacao; // reputacao
	//Date data_posts[];
	//Date data_respostas[];
	//char* títulos[];
	char* short_bio; // descrição do user
	GArray* userPosts;

};

struct post{
	long id;
	char* titulo;
	long owner_id;
	char* owner_display_name;
	int owner_rep;
	int type_id;
	long parent_id;
	char* data;
	char* tags;
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
  	GTree* new_post_tree = g_tree_new((GCompareFunc)cmpIsoDate);
  	GHashTable* new_postAux_hash = g_hash_table_new(g_int_hash, g_int_equal);
	GHashTable* new_tags_hash = g_hash_table_new(g_str_hash, g_str_equal);
  	
  	new->user = new_user_hash;
  	new->post = new_post_tree;
  	new->postAux = new_postAux_hash;
  	new->tags = new_tags_hash;	

  	return new;
}


TAD_community load(TAD_community com, char* dump_path){
	load_aux(com->user,com->post,com->postAux,com->tags,dump_path);
	return com;
}  
/*
// query 1
STR_pair info_from_post(TAD_community com, long id){
	return info_from_post_aux(com->post, com->postAux, com->user, id);
} 
*/ 
/*
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
*/
/*
// query 6
LONG_list most_voted_answers(TAD_community com, int N, Date begin, Date end){
	return most_voted_answers_aux(com->post,N,begin,end);
}

// query 7
LONG_list most_answered_questions(TAD_community com, int N, Date begin, Date end){
	return most_answered_questions_aux(com->post,N,begin,end);
}
*/
/*
// query 8
LONG_list contains_word(TAD_community com, char* word, int N){
	return contains_word_aux(com->post,word,N);
}

// query 9
LONG_list both_participated(TAD_community com, long id1, long id2, int N){
	return both_participated_aux(com->user, com->post,id1,id2,N);
}

// query 10
long better_answer(TAD_community com, long id){
	return better_answer_aux(com->post,id);
}

// query 11
LONG_list most_used_best_rep(TAD_community com, int N, Date begin, Date end){
	return most_used_best_rep_aux(com->user,com->tags,N,begin,end);
}
*/

// Hash PostAux para Post 

Post getPost(GTree* com_post, GHashTable* com_postAux,long id){

	PostAux postAux = (PostAux)g_hash_table_lookup(com_postAux, &id);

	/* Debugging */ if(!postAux) printf("Post not found\n");
	
	char* postDate = getPostAuxDate(postAux);
	
	char  postID[50]; 
	sprintf (postID, "%lu", id);

	STR_pair postKey = create_str_pair(postDate,postID);

	Post post = (Post)g_tree_search(com_post,(GCompareFunc)postTreeSearch,postKey);
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

char* getPostOwnerDisplayName(Post post){
	return mystrdup(post->owner_display_name);
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

Date getPostSimpleDate(Post post){ // "AAAA-MM-DD"
	char* date = getPostDate(post);

	char* ano_str = malloc(5);
	char* mes_str = malloc(3);
	char* dia_str = malloc(3);
	int ano, mes, dia;

	strncpy(ano_str, date, 4);
	ano_str[4]='\0';
	strncpy(mes_str, date+5, 2);
	mes_str[2]='\0';
	strncpy(dia_str, date+8, 2);
	dia_str[2]='\0';

	ano=atoi(ano_str);
	mes=atoi(mes_str);
	dia=atoi(dia_str);

	return (createDate(dia, mes, ano));
}


char* getPostTags(Post post){
	return mystrdup(post->tags);
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

void setPostOwnerDisplayName(Post post, char* owner_display_name){
	 post->owner_display_name = mystrdup(owner_display_name);
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

void setPostTags(Post post, char* tags){
	post->tags = mystrdup(tags); 
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
	free(post->owner_display_name);
	free(post->data);
	free(post->tags);
	free(post);	
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
