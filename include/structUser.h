#ifndef __STRUCTUSER_H__
#define __STRUCTUSER_H__

typedef struct user* User;

#include "toInclude.h"

//Init User

User initUser();
void initUserPosts(User user); // funcao para fazer criar um garray de posts num dado user

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

/** \brief ola.

	sou eu.
	@param user
	@param short_bio

	@returns
*/
void addUserPost(User user, Post post);

// Cleaner
void freeUser (User user);

#endif