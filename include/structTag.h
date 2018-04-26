#ifndef _STRUCTTAG_H_
#define _STRUCTTAG_H_


typedef struct tag* Tag;

#include "toInclude.h"

//Init 
Tag initTag();

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