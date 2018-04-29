#ifndef _STRUCTTAG_H_
#define _STRUCTTAG_H_


typedef struct tag* Tag;

#include "toInclude.h"

//Init 
/** \brief Cria uma nova Tag.

	@returns Nova Tag criada.
*/
Tag initTag();

// Getters para Tag

/** \brief Getter para o nome de uma Tag

	@param tag Uma Tag

	@returns Nome da tag.
*/
char* getTagName(Tag tag);

/** \brief Getter para ID de uma Tag

	@param tag Uma Tag

	@returns ID da Tag
*/
long getTagID(Tag tag);


// Setters para Tag

/** \brief Setter para o nome da Tag

	@param tag Uma Tag
	@param name Nome a atribuir à Tag

*/
void setTagName(Tag tag, char* name);

/** \brief 

	@param tag Uma tag
	@param id Id a atribuir à Tag

*/
void setTagID(Tag tag, long id);


// Cleaner

/** \brief Liberta o espaço ocupado pela Tag

	@param tag Tag a libertar
	
*/
void freeTags (Tag tag);


#endif