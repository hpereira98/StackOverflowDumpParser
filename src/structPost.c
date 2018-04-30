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


struct postKey{
	char* data;
	long id;
};


// POSTS

// Init

Post initPost(){
	Post new = malloc(sizeof(struct post));
	new->tags = NULL;
	new->parent_id = -2;
	new->n_respostas = -1;

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

	char* simpleDate = g_strndup(date,10);

	free(date);

	return simpleDate;
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

void setPostTags(Post post, char* tags, GHashTable* com_tags){
	
	if(tags){
		int j = 1;
		post->tags = g_array_new(FALSE, FALSE, sizeof(long));

		while(tags[j]!='\0'){
		   	char* next_tag = nextTag((char*)tags, &j);
		   	Tag tag = getTag(com_tags,next_tag);

   			long tagID = getTagID(tag);
			g_array_append_val(post->tags, tagID);

			free(next_tag);
		}
	}	
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

void freePostTags(char** tag){
	free(*tag);
}

void freePost (Post post) {
	free(post->titulo);
	free(post->data);
	if(post->tags != NULL){
		//g_array_set_clear_func(post->tags, (GDestroyNotify)freePostTags);
		g_array_free(post->tags, TRUE);
	}
	free(post);	
}


// PostKey

// Init

PostKey createPostKey(char* data, long id){
	PostKey new =  malloc(sizeof(struct postKey));

	new->data = mystrdup(data);
	new->id = id;

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


// Função para comparação de dois PostKeys

int cmpTreeKey(PostKey a, PostKey b, gpointer user_data){

	if(getPostKeyID(a) == getPostKeyID(b)) 
		return 0; // caso os posts tenham o mesmo id para a procura
	
	char *datePostA = getPostKeyDate(a);
	char *datePostB = getPostKeyDate(b);
	int r = strcmp(datePostB, datePostA);

	if(r==0) r = getPostKeyID(a)-getPostKeyID(b); // evitar que posts com strings de data iguais nao deixem de ser inseridos na btree
	
	free(datePostA);
	free(datePostB);

	return r; 
}


