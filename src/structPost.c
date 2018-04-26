#include "structPost.h"

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
};

struct postAux{
	char* data;
};

struct postKey{
	char* data;
	long id;
};


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
	g_array_free(post->tags, TRUE);
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

void freePostKey(PostKey post_key){
	free(post_key->data);
	free(post_key);
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

// Função para comparação de dois PostKeys

int cmpTreeKey(PostKey a, PostKey b){

	if(getPostKeyID(a) == getPostKeyID(b)) 
		return 0; // caso os posts tenham o mesmo id para a procura
	
	int r = (-1) * strcmp(getPostKeyDate(a), getPostKeyDate(b));

	if(r==0) r = getPostKeyID(a)-getPostKeyID(b); // evitar que posts com strings de data iguais nao deixem de ser inseridos na btree
	
	return r; 
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




// Setters

void setPostAuxDate(PostAux postAux, char* data){
	postAux->data = mystrdup(data);
}

