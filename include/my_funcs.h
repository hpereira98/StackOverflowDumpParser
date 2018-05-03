#ifndef __MYFUNCS_H__
#define __MYFUNCS_H__

/**
	@file my_funcs.h
   
	Ficheiro .h com os tipos das funções auxiliares por nós definidas.
*/

#include "toInclude.h"


// Funcoes sobre Posts

/** \brief Função que devolve um (Post) Post.

	@param *com_post Árvore dos Posts
	@param *com_postAux Tabela de Hash auxiliar dos Posts
	@param id Identificador do Post a receber

	@returns (Post) Post com o ID dado caso este exista, NULL caso contrário
*/
Post getPost(GTree* com_post, GHashTable* com_postAux, long id);

/** \brief Função que insere num array dinâmico os Posts com um determinado tipo.

	Realiza as operações tendo em conta um dado intervalo de tempo.
	@param *com_post Árvore dos Posts
	@param date_begin Limite inferior do intervalo de tempo
	@param date_end Limite superior do intervalo de tempo
	@param typeId Tipo do Post

	@returns Array dinâmico com os Posts do tipo dado
*/
GArray* filterPostsByTypeID(GTree* com_post, char* date_begin, char* date_end, int typeId);

// Funções sobre Hash User

/** \brief Função que devolve um (User) User.

	@param *com_user Tabela de Hash dos Users
	@param id Identificador do User

	@returns (User) User com o dado ID
*/
User getUser(GHashTable* com_user, long id);

/** \brief Função que passa os Users da Tabela de Hash para um Array dinâmico

	@param *com_user Tabela de Hash dos Users

	@returns Array dinâmico com os Users da tabela de Hash dada
*/
GArray* usersHashToGArray(GHashTable* com_user);

// Funções sobre hash das Tags

/** \brief Função que retorna uma Tag, dado o seu nome.

	@param *com_tags Tabela de Hash das Tags
	@param tag Nome da Tag

	@returns Tag com o nome passado como argumento.
*/
Tag getTag(GHashTable* com_tags, char* tag);

// Funções para ordenação 

/** \brief Função de ordenação de Users pelo número de Posts

	@param a Primeiro utilizador
	@param b Segundo utilizador

	@returns 0, caso o nº de Posts de ambos os Users seja igual
	@returns <0, caso o nº de Posts do primeiro User seja superior ao do segundo User
	@return >0, caso o nº de Posts do primeiro User seja inferior ao do segundo User
*/
int sortByNPosts(User* a,User *b);

/** \brief Função de ordenação de Users pela reputação

	@param a Primeiro utilizador
	@param b Segundo utilizador

	@returns 0, caso a reputação de ambos os Users seja igual
	@returns <0, caso a reputação do primeiro User seja superior à do segundo User
	@return >0, caso a reputação do primeiro User seja inferior à do segundo User
*/
int sortByRep(User* a,User *b);

/** \brief Função de ordenação de Posts pelo Score

	@param a Primeiro Post
	@param b Segundo Post

	@returns 0, caso o score de ambos os Posts seja igual
	@returns <0, caso o score do primeiro Post seja superior ao do segundo Post
	@return >0, caso o score do primeiro Post seja inferior ao do segundo Post
*/
int sortByScore(Post *a, Post *b);

/** \brief Função de ordenação de Posts pelo número de respostas

	@param a Primeiro Post
	@param b Segundo Post

	@returns 0, caso o nº de respostas de ambos os Posts seja igual
	@returns <0, caso o nº de respostas do primeiro Post seja superior ao do segundo Post
	@return >0, caso o nº de respostas do primeiro Post seja inferior ao do segundo Post
*/
int sortByNAnswers(Post* a, Post *b);

/** \brief Função de ordenação de Posts pela Data

	@param a Primeiro Post
	@param b Segundo Post

	@returns 0, caso a data de ambos os Posts seja igual
	@returns <0, caso a data do primeiro Post seja mais recente que a do segundo Post
	@return >0, caso a data do primeiro Post seja mais antiga que a do segundo Post
*/
int sortByDate(Post* a, Post* b);

/** \brief Função de ordenação de Pares(ID Tag,nº de ocorrências) pelo segundo elemento do par

	@param a Primeiro Par
	@param b Segundo Par

	@returns <0, caso o número de ocorrências do primeiro Par seja superior ao do segundo Par 
	@returns >0, caso o número de ocorrências do primeiro Par seja inferior ao do segundo Post
	@returns tagID1 - tagID2, caso as tags tenham registado o mesmo número do ocorrências.
*/
int sortMSet(LONG_pair* a, LONG_pair* b);

/** \brief Função de ordenação de inteiros (long)

	@param a Primeiro inteiro
	@param b Segundo inteiro

	@returns 0, caso ambos sejam iguais
	@returns <0, caso o primeiro seja menor que o segundo
	@return >0, caso o primeiro seja maior que o segundo
*/
int cmpInt(long *a, long* b);

// Funções para tratamentos de datas

/** \brief Função que transforma uma (Date) data numa String

	@param date Data

	@returns String representativa da data no formato AAAA-MM-DD.
*/
char* dateToString(Date date);

/** \brief Função que verifica se uma dada data está dentro de um dado intervalo de tempo

	@param begin Limite inferior do intervalo de tempo
	@param end Limite superior do intervalo de tempo
	@param post_date Data a verificar

	@returns 0, caso a Data esteja dentro do intervalo
	@returns -1, caso a Data esteja fora do limite inferior do intervalo
	@returns 1, caso a Data seja mais recente que o limite superior do intervalo
*/
int comparaDatas(char* begin, char* end, char* post_date);


/** \brief Função que retira a String de uma tag.

	Isto é, remove os caracteres '<' e '>'.
	@param tags Tags
	@param *i Apontador para a posição atual da iteração

	@returns String contida na Tag
*/
char* nextTag(char* tags, int *i);

// Função para determinar tamanho da LONG_list a devolver 

/** \brief Função que determina o tamanho da LONG_list a devolver como resultado nas Queries

	@param garraySize Tamanho do array dinâmico
	@param n Número de elementos passado como argumento na função principal da Query

	@returns Tamanho do array, caso seja inferior a N
	@returns N, caso contrário
*/
int selectSize(int garraySize, int n);

#endif
