#ifndef __MYFUNCS_H__
#define __MYFUNCS_H__

/**
	@file my_funcs.h
   
	Definição...
*/

#include "toInclude.h"


// Funcoes sobre Posts

/** \brief ola.

	sou eu.
	@param *a
	@param *b

	@returns
*/
Post getPost(GTree* com_post, GHashTable* com_postAux, long id);

/** \brief ola.

	sou eu.
	@param *a
	@param *b

	@returns
*/
GArray* filterPostsByTypeID(GTree* com_post, char* date_begin, char* date_end, int typeId);

// Funções sobre Hash User

/** \brief ola.

	sou eu.
	@param *a
	@param *b

	@returns
*/
User getUser(GHashTable* com_user, long id);

/** \brief ola.

	sou eu.
	@param *a
	@param *b

	@returns
*/
GArray* usersHashToGArray(GHashTable* com_user);

/** \brief ola.

	sou eu.
	@param *a
	@param *b

	@returns
*/
void appendUserToArray (gpointer key_pointer, gpointer user_pointer, gpointer info);

// Funções para ordenação 

/** \brief ola.

	sou eu.
	@param *a
	@param *b

	@returns
*/
int sortByNPosts(User* a,User *b);

/** \brief ola.

	sou eu.
	@param *a
	@param *b

	@returns
*/
int sortByRep(User* a,User *b);

/** \brief ola.

	sou eu.
	@param *a
	@param *b

	@returns
*/
int sortByScore(Post *a, Post *b);

/** \brief ola.

	sou eu.
	@param *a
	@param *b

	@returns
*/
int sortByNRespostas(Post* a, Post *b);

/** \brief ola.

	sou eu.
	@param *a
	@param *b

	@returns
*/
int sortByDate(Post* a, Post* b);

/** \brief ola.

	sou eu.
	@param *a
	@param *b

	@returns
*/
int sortMSet(LONG_pair* a, LONG_pair* b);

/** \brief ola.

	sou eu.
	@param *a
	@param *b

	@returns
*/
int cmpInt(long *a, long* b);

// Funções para tratamentos de datas

/** \brief ola.

	sou eu.
	@param date

	@returns
*/
char* dateToString(Date date);


/** \brief ola.

	sou eu.
	@param *begin
	@param *end
	@param *post_date

	@returns
*/
int comparaDatas(char* begin, char* end, char* post_date);


/** \brief ola.

	sou eu.
	@param *tags
	@param *i

	@returns
*/
char* nextTag(char* tags, int *i);

// Função para determinar tamanho da LONG_list a devolver 

/** \brief ola.

	sou eu.
	@param *tags
	@param *i

	@returns
*/
int selectSize(int garraySize, int n);

#endif
