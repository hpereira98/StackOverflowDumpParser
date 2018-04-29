#include "structUser.h"

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

// USERS

// Inits

User initUser(){
	User newUser = malloc(sizeof(struct user));

	newUser->userPosts = NULL;
	newUser->n_respostas = 0;
	newUser->n_perguntas = 0;
	newUser->n_posts = 0;

	return newUser;
}

void initUserPosts(User user){
	user->userPosts = g_array_new (FALSE,TRUE,sizeof(Post));
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

GArray* getUserPosts(User user){ 
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

// Add UserPost

void addUserPost(User user, Post post){
	if(!user->userPosts)
		user->userPosts = g_array_new (FALSE,TRUE,sizeof(Post));
	 
	g_array_append_val(user->userPosts, post);

	user->n_posts++;

	if(getPostTypeID(post) == 1) 
		user->n_perguntas++;
	else 
		user->n_respostas++;
}

// Cleaner

void freeUser (User user) {
	free(user->display_name);
	free(user->short_bio);
	if(user->userPosts != NULL) g_array_free(user->userPosts,TRUE);
	free(user);
}
