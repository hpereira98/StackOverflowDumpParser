#ifndef __STRUCTS_H__
#define __STRUCTS_H__


#include "toInclude.h"


//Xml to TAD

/** \brief Função para processar a informação presente em Users.xml

	@param com Estrutura onde os dados vão ser armazenados.
	@param doc_root Root do ficheiro .xml

*/
void usersXmlToTAD(TAD_community com, xmlNodePtr doc_root);

/** \brief Função para processar a informação presente em Posts.xml

	@param com Estrutura onde os dados vão ser armazenados.
	@param doc_root Root do ficheiro Posts.xml

*/
void postsXmlToTAD(TAD_community com, xmlNodePtr doc_root);

/** \brief Função para processar a informação presente em Tags.xml

	@param com Estrutura onde os dados vão ser armazenados.
	@param doc_root Root do ficheiro Tags.xml

*/
void tagsXmlToTAD(TAD_community com, xmlNodePtr doc_root);


#endif
