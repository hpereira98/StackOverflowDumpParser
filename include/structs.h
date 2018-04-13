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
long getUserID(User user);
char* getUserDisplayName(User user);
int getUserReputacao(User user);
int getUserNPerguntas(User user);
int getUserNRespostas(User user);
int getUserNPosts(User user);
char* getUserShortBio(User user);
GArray* getUserPosts(User user);
GArray* getClonedUserPosts(User user);

// Setters para user
void setUserID(User user, long id);
void setUserDisplayName(User user, char* display_name);
void setUserReputacao(User user, int reputacao);
void setUserNPerguntas(User user, int n_perguntas);
void setUserNRespostas(User user,int n_respostas);
void setUserNPosts(User user, int n_posts);
void setUserShortBio(User user, char* short_bio);
// Cleaner
void freeUser (User user);

// Getters para Post
long getPostID(Post post);
char* getPostTitle(Post post);
long getPostOwnerID(Post post);
int getPostOwnerRep(Post post);
int getPostTypeID(Post post);
long getPostParentID(Post post);
char* getPostDate(Post post);
char* getPostSimpleDate(Post post);
GArray* getPostTags(Post post);
int getPostScore(Post post);
int getPostNComments(Post post);
int getPostNRespostas(Post post);

// Setters para Post
void setPostID(Post post, long id);
void setPostTitle(Post post, char* titulo);
void setPostOwnerID(Post post, long owner_id);
void setPostOwnerRep(Post post, int owner_rep);
void setPostTypeID(Post post, int type_id);
void setPostParentID(Post post, long parent_id);
void setPostDate(Post post, char* data);
void setPostTags(Post post, GArray* tags);
void setPostScore(Post post, int score);
void setPostNComments(Post post, int n_comments);
void setPostNDownVotes(Post post, int n_downvotes);
void setPostNUpVotes(Post post, int n_upvotes);
void setPostNRespostas(Post post, int n_respostas);

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
