#ifndef __STRUCTPOST_H__
#define __STRUCTPOST_H__

typedef struct post* Post;
typedef struct postAux* PostAux;
typedef struct postKey* PostKey;

#include "toInclude.h"

// Init

/** \brief Função que cria um novo Post.

	@returns Novo Post criado.
*/
Post initPost(); 

// Getters para Post

/** \brief Getter para o ID de um Post

	@param post Um Post

	@returns ID do Post.
*/
long getPostID(Post post);

/** \brief Getter para o título de um Post

	@param post Um Post

	@returns O título do Post.
*/
char* getPostTitle(Post post);

/** \brief Getter para o ownerID de um Post

	@param post Um Post 

	@returns ID do owner do Post.
*/
long getPostOwnerID(Post post);

/** \brief Getter para a reputação do criador de um Post.

	@param post Um Post

	@returns Repuação do criador do Post.
*/
int getPostOwnerRep(Post post);


/** \brief Getter para o TypeID de um Post.

	@param post Um Post

	@returns TypeId do Post.
*/
int getPostTypeID(Post post);

/** \brief Getter para o parentID de um Post.

	@param post Um Post (uma resposta)

	@returns ID da pergunta a que o Post responde.
*/
long getPostParentID(Post post);

/** \brief Getter para o "time-stamp" de um Post.

	@param post Um Post

	@returns "time-stamp" do Post.
*/
char* getPostDate(Post post);

/** \brief Getter para a data de um Post.

	@param post Um Post

	@returns Data do Post no formato AAAA-MM-DD.
*/
char* getPostSimpleDate(Post post);

/** \brief Getter para as Tags de um Post.

	@param post Um Post

	@returns GArray contendo a tags usadas no Post.
*/
GArray* getPostTags(Post post);

/** \brief Getter para o score de um Post.

	@param post Um Post

	@returns Score do Post.
*/
int getPostScore(Post post);

/** \brief Getter para o número de comentários de um Post.

	@param post Um Post

	@returns O número de comentários que o Post obteve.
*/
int getPostNComments(Post post);

/** \brief Getter para o número de respostas de um Post.

	@param post Um Post

	@returns Número de respostas que o Post obteve.
*/
int getPostNRespostas(Post post);


// Setters para Post

/** \brief Setter para o ID de um Post

	@param post Um Post
	@param id Id do Post.

*/
void setPostID(Post post, long id);

/** \brief Setter para o título de um Post

	@param post Um Post
	@param titulo Título do Post

*/
void setPostTitle(Post post, char* titulo);

/** \brief Setter para o ownerID de um Post.

	@param post Um Post
	@param owner_id ID do criador do Post

*/
void setPostOwnerID(Post post, long owner_id);

/** \brief Setter para de a reputação do criador um Post.

	@param post Um Post
	@param owner_rep Reputação do criador.

*/
void setPostOwnerRep(Post post, int owner_rep);

/** \brief Setter para o TypeID de um Post.

	@param post Um Post
	@param type_id TypeID do post

*/
void setPostTypeID(Post post, int type_id);

/** \brief Setter para o ParentID de um Post.

	@param post Um Post
	@param parent_id ParentID do Post

*/
void setPostParentID(Post post, long parent_id);

/** \brief Setter para a Data de um Post.

	@param post Um Post
	@param data "time-stamp" do Post

*/
void setPostDate(Post post, char* data);

/** \brief Setter para as Tags de um Post

	@param post Um Post
	@param tags Tags do Post (conforme no documento Posts.xml)

*/
void setPostTags(Post post, char* tags, GHashTable* com_tags);

/** \brief Setter para o score de um Post

	@param post Um Post
	@param score Score do Post

*/
void setPostScore(Post post, int score);

/** \brief Setter para o número de comentários de um Post.

	@param post Um Post
	@param n_comments Número de comentários que o Post obteve

*/
void setPostNComments(Post post, int n_comments); 

/** \brief Setter para o número de respostas de um Post.

	@param post Um Post
	@param n_respostas AnswerCount do Post.

*/
void setPostNRespostas(Post post, int n_respostas);


// Cleaner

/** \brief Função que liberta o espaço ocupado por um Post.

	@param post Um Post a libertar.

*/
void freePost (Post post);

// PostKey

// Init

/** \brief Função que cria uma nova postKey.

	@param data "time-stamp" de um Post
	@param id Id de um post
	
	@retuns Nova postKey.
*/
PostKey createPostKey(char* data, long id);

// Getters

/** \brief Getter para a Data da postKey de um Post.

	@param post_key Uma postKey
	
	@retuns A data da chave.
*/
char* getPostKeyDate(PostKey post_key);

/** \brief Getter para o ID da postKey de um Post.

	@param post_key Uma postKey
	
	@retuns o ID da chave.
*/
long getPostKeyID(PostKey post_key);

// Free

/** \brief Função para libertar o espaço ocupado por uma postKey.

	@param post_key PostKey a libertar.

*/
void freePostKey(PostKey post_key);

/** \brief Função que estabelece uma relação de ordem entre duas postKeys

	@param a Primeira PostKey
	@param b Segunda PostKey
	@param user_data 

	@returns 0 caso as postKeys sejam iguais, -1 se a primeira for maior que a segunda, 1 caso contrário
*/
int cmpTreeKey(PostKey a, PostKey b, gpointer user_data);




#endif