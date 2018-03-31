#ifndef __STRUCTS_H__
#define __STRUCTS_H__

#include <glib.h>
#include <gmodule.h>
#include "my_funcs.h"
#include "common.h"

typedef struct user* User;
typedef struct post* Post;


struct TCD_community{
	GHashTable* user;
	GHashTable* post;	
};

// Inits 
User initUser();
void initUserPosts(User user); // funcao para fazer criar um garray de posts num dado user
Post initPost();

// Getters para user
int getUserID(User user);
char* getUserDisplayName(User user);
int getUserReputacao(User user);
int getUserNPerguntas(User user);
int getUserNRespostas(User user);
int getUserNPosts(User user);
char* getUserShortBio(User user);
GArray* getUserPosts(User user);
GArray* getClonedUserPosts(User user);

// Setters para user
void setUserID(User user, int id);
void setUserDisplayName(User user, char* display_name);
void setUserReputacao(User user, int reputacao);
void setUserNPerguntas(User user, int n_perguntas);
void setUserNRespostas(User user,int n_respostas);
void setUserNPosts(User user, int n_posts);
void setUserShortBio(User user, char* short_bio);

// Getters para Post
int getPostID(Post post);
char* getPostTitle(Post post);
int getPostOwnerID(Post post);
char* getPostOwnerDisplayName(Post post);
int getPostOwnerRep(Post post);
int getPostTypeID(Post post);
int getPostParentID(Post post);
Date getPostDate(Post post);
char* getPostTags(Post post);
int getPostScore(Post post);
int getPostNComments(Post post);
int getPostNUpVotes(Post post);
int getPostNDownVotes(Post post);
int getPostNRespostas(Post post);

// Setters para Post
void setPostID(Post post, int id);
void setPostTittle(Post post, char* titulo);
void setPostOwnerID(Post post, int owner_id);
void setPostOwnerDisplayName(Post post, char* owner_display_name);
void setPostOwnerRep(Post post, int owner_rep);
void setPostTypeID(Post post, int type_id);
void setPostParentID(Post post, int parent_id);
void setPostDate(Post post, Date data);
void setPostTags(Post post, char* tags);
void setPostScore(Post post, int score);
void setPostNComments(Post post, int n_comments);
void setPostNDownVotes(Post post, int n_downvotes);
void setPostNUpVotes(Post post, int n_upvotes);
void setPostNRespostas(Post post, int n_respostas);

#endif
