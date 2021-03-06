#include "structUser.h"

struct user{
	long id; // user id
	char* display_name; // username
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
	newUser->n_posts = 0;

	return newUser;
}

// Getters

long getUserID(User user){
	return user->id;
}

char* getUserDisplayName(User user){
	return mystrdup(user->display_name);
}

int getUserReputation(User user){
	return user->reputacao;
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
	if(!user->userPosts) return NULL;
	
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

void setUserReputation(User user, int reputacao){
	user->reputacao = reputacao;
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
}

// Cleaner

void freeUser (User user) {
	free(user->display_name);
	free(user->short_bio);
	if(user->userPosts != NULL) g_array_free(user->userPosts,TRUE);
	free(user);
}
