#ifndef __STRUCTS_H__
#define __STRUCTS_H__


typedef struct user* User;
typedef struct post* Post;
typedef struct postAux* PostAux;
typedef struct tag* Tag;
typedef struct postKey* PostKey;

#include "toInclude.h"

//Xml to TAD

void usersXmlToTAD(TAD_community com, xmlNodePtr doc_root);
void postsXmlToTAD(TAD_community com, xmlNodePtr doc_root);
void tagsXmlToTAD(TAD_community com, xmlNodePtr doc_root);

//Post

Post getPost(GTree* com_post, GHashTable* com_postAux, long id);

// Inits 
User initUser();
void initUserPosts(User user); // funcao para fazer criar um garray de posts num dado user
Post initPost();
Tag initTag();
PostAux initPostAux();

// Getters para user

/** \brief ola.

	sou eu.
	@param user

	@returns
*/
long getUserID(User user);

/** \brief ola.

	sou eu.
	@param user

	@returns
*/
char* getUserDisplayName(User user);

/** \brief ola.

	sou eu.
	@param user

	@returns
*/

/** \brief ola.

	sou eu.
	@param user

	@returns
*/
int getUserReputacao(User user);

/** \brief ola.

	sou eu.
	@param user

	@returns
*/
int getUserNPerguntas(User user);

/** \brief ola.

	sou eu.
	@param user

	@returns
*/
int getUserNRespostas(User user);

/** \brief ola.

	sou eu.
	@param user

	@returns
*/
int getUserNPosts(User user);

/** \brief ola.

	sou eu.
	@param user

	@returns
*/
char* getUserShortBio(User user);

/** \brief ola.

	sou eu.
	@param user

	@returns
*/
GArray* getUserPosts(User user);

/** \brief ola.

	sou eu.
	@param user

	@returns
*/
GArray* getClonedUserPosts(User user);

// Setters para user

/** \brief ola.

	sou eu.
	@param user
	@param id
	
	@returns
*/
void setUserID(User user, long id);

/** \brief ola.

	sou eu.
	@param user
	@param display_name
	
	@returns
*/
void setUserDisplayName(User user, char* display_name);

/** \brief ola.

	sou eu.
	@param user
	@param reputacao
	
	@returns
*/
void setUserReputacao(User user, int reputacao);

/** \brief ola.

	sou eu.
	@param user
	@param n_perguntas
	
	@returns
*/
void setUserNPerguntas(User user, int n_perguntas);

/** \brief ola.

	sou eu.
	@param user
	@param n_respostas
	
	@returns
*/
void setUserNRespostas(User user,int n_respostas);

/** \brief ola.

	sou eu.
	@param user
	@param n_posts
	
	@returns
*/
void setUserNPosts(User user, int n_posts);

/** \brief ola.

	sou eu.
	@param user
	@param short_bio

	@returns
*/
void setUserShortBio(User user, char* short_bio);
// Cleaner
void freeUser (User user);

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

char* getPostKeyDate(PostKey post_key);
long getPostKeyID(PostKey post_key);

void setPostKeyDate(PostKey post_key, char* data);
void setPostKeyID(PostKey post_key, long id);


// Getters para PostAux
char* getPostAuxDate(PostAux postAux);
int getPostAuxNDownVotes(PostAux postAux);
int getPostAuxNUpVotes(PostAux postAux);

// Setters para PostAux
void setPostAuxDate(PostAux postAux, char* data);
void setPostAuxNDownVotes(PostAux postAux, int n_downvotes);
void setPostAuxNUpVotes(PostAux postAux, int n_upvotes);

// Getters para Tag
char* getTagName(Tag tag);
long getTagID(Tag tag);
int getTagOcor(Tag tag);

// Setters para Tag
void setTagName(Tag tag, char* name);
void setTagID(Tag tag, long id);
void setTagOcor(Tag tag, int ocor);

// Cleaner
void freeTags (Tag tag);


Tag createTag(char* name, long id, int ocorrencias);

#endif
