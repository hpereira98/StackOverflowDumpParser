#ifndef __STRUCTPOST_H__
#define __STRUCTPOST_H__

typedef struct post* Post;
typedef struct postAux* PostAux;
typedef struct postKey* PostKey;

#include "toInclude.h"

// Init
	Post initPost(); 
	PostAux initPostAux();
// Getters para Post

/** \brief ola.

	sou eu.
	@param post

	@returns
*/
long getPostID(Post post);

/** \brief ola.

	sou eu.
	@param post

	@returns
*/
char* getPostTitle(Post post);

/** \brief ola.

	sou eu.
	@param post

	@returns
*/
long getPostOwnerID(Post post);

/** \brief ola.

	sou eu.
	@param post

	@returns
*/
int getPostOwnerRep(Post post);

/** \brief ola.

	sou eu.
	@param post

	@returns
*/
int getPostTypeID(Post post);

/** \brief ola.

	sou eu.
	@param post

	@returns
*/
long getPostParentID(Post post);

/** \brief ola.

	sou eu.
	@param post

	@returns
*/
char* getPostDate(Post post);

/** \brief ola.

	sou eu.
	@param post

	@returns
*/
char* getPostSimpleDate(Post post);

/** \brief ola.

	sou eu.
	@param post

	@returns
*/
GArray* getPostTags(Post post);

/** \brief ola.

	sou eu.
	@param post

	@returns
*/
int getPostScore(Post post);

/** \brief ola.

	sou eu.
	@param post

	@returns
*/
int getPostNComments(Post post);

/** \brief ola.

	sou eu.
	@param post

	@returns
*/
int getPostNRespostas(Post post);

/** \brief ola.

	sou eu.
	@param post

	@returns
*/
GArray* getPostRespostas(Post post);


// Setters para Post

/** \brief ola.

	sou eu.
	@param post
	@param id

	@returns
*/
void setPostID(Post post, long id);

/** \brief ola.

	sou eu.
	@param post
	@param *titulo
	
	@returns
*/
void setPostTitle(Post post, char* titulo);

/** \brief ola.

	sou eu.
	@param post
	@param owner_id
	
	@returns
*/
void setPostOwnerID(Post post, long owner_id);

/** \brief ola.

	sou eu.
	@param post
	@param owner_rep
	
	@returns
*/
void setPostOwnerRep(Post post, int owner_rep);

/** \brief ola.

	sou eu.
	@param post
	@param type_id
	
	@returns
*/
void setPostTypeID(Post post, int type_id);

/** \brief ola.

	sou eu.
	@param post
	@param parent_id
	
	@returns
*/
void setPostParentID(Post post, long parent_id);

/** \brief ola.

	sou eu.
	@param post
	@param *data
	
	@returns
*/
void setPostDate(Post post, char* data);

/** \brief ola.

	sou eu.
	@param post
	@param *tags
	
	@returns
*/
void setPostTags(Post post, GArray* tags);

/** \brief ola.

	sou eu.
	@param post
	@param score
	
	@returns
*/
void setPostScore(Post post, int score);

/** \brief ola.

	sou eu.
	@param post
	@param n_comments
	
	@returns
*/
void setPostNComments(Post post, int n_comments); 

/** \brief ola.

	sou eu.
	@param post
	@param n_respostas
	
	@returns
*/
void setPostNRespostas(Post post, int n_respostas);

/** \brief ola.

	sou eu.
	@param post
	@param *respostas
	
	@returns
*/
void setPostRespostas(Post post, GArray* respostas);


// Cleaner
void freePost (Post post);

// PostKey
PostKey initPostKey();
PostKey createPostKey(char* data, long id);
void freePostKey(PostKey post_key);

char* getPostKeyDate(PostKey post_key);
long getPostKeyID(PostKey post_key);

void setPostKeyDate(PostKey post_key, char* data);
void setPostKeyID(PostKey post_key, long id);

int cmpTreeKey(PostKey a, PostKey b, gpointer user_data);

// Getters para PostAux
char* getPostAuxDate(PostAux postAux);


// Setters para PostAux
void setPostAuxDate(PostAux postAux, char* data);


#endif