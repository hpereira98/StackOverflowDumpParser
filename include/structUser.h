#ifndef __STRUCTUSER_H__
#define __STRUCTUSER_H__

typedef struct user* User;

#include "toInclude.h"

//Init User

/** \Cria um novo User.

	@returns Novo User criado.
*/
User initUser();

// Getters para user

/** \Getter do ID de um User.

	@param user Um user 

	@returns ID do utilizador.
*/
long getUserID(User user);

/** \Getter do DisplayName de um User.

	@param user Um User

	@returns DisplayName do User
*/
char* getUserDisplayName(User user);

/** \Getter da Reputação de um User.

	@param user Um User

	@returns Reputação de um User.
*/
int getUserReputation(User user);

/** \Getter do Número de Posts de um User.

	@param user Um User

	@returns Número de Posts de um User
*/
int getUserNPosts(User user);

/** \Getter da ShortBio de um User.

	@param user Um User

	@returns ShortBio do User.
*/
char* getUserShortBio(User user);

/** \Getter dos Posts efetuados por um User.

	@param user Um User

	@returns
*/
GArray* getUserPosts(User user);

/** \Getter dos Posts efetuados por um User.
	
 	ShallowClone dos Posts de um User;
	@param user Um User

	@returns Novo array contendo os Posts do User
*/
GArray* getClonedUserPosts(User user);

// Setters para user

/** \brief Setter para ID do User.

	@param user Um user
	@param id Id do User
	
*/
void setUserID(User user, long id);

/** \brief Setter para DisplayName de um User.

	@param user Um User
	@param display_name DisplayName do User
	
*/
void setUserDisplayName(User user, char* display_name);

/** \brief Setter para reputação de um User

	@param user Um User
	@param reputacao Reputação de um User
	
*/
void setUserReputation(User user, int reputacao);

/** \brief Setter para a ShortBio de um User

	@param user Um User
	@param short_bio ShortBio do User

*/
void setUserShortBio(User user, char* short_bio);

/** \brief Função para adicionar um Post a um User.

	@param user User owner do Post
	@param post Post realizado pelo User

*/
void addUserPost(User user, Post post);

// Cleaner

/** \brief Função para libertar o espaço ocupado por um User.

	@param user User a libertar

*/
void freeUser (User user);

#endif