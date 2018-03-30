#include "structs.h"


// USERS

int getUserID(User user){
	return user->id;
}

char* getUserDisplayName(User user){
	return mystrdup(user->display_name);
}

int getUserRep(User user){
	return user->rep;
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

GArray* getUserPostsIDs(User user){ // copiar todos para um novo?
	return user->userPosts;
}



// POSTS

int getPostID(Post post){
	return post->id;
}

char* getPostTitle(Post post){
	return mystrdup(post->titulo);
}

int getPostOwnerID(Post post){
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

int getPostParentID(Post post){
	return post->parent_id;
}

Date getPostDate(Post post){
	int dia, mes, ano;

	dia = get_day(post->data);
	mes = get_month(post->data);
	ano = get_year(post->data);

	return createDate(dia, mes, ano);
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

int getPostNUpVotes(Post post){
	return post->n_upvotes;
}

int getPostNDownVotes(Post post){
	return post->n_downvotes;
}

int getPostNRespostas(Post post){
	return post->n_respostas;
}