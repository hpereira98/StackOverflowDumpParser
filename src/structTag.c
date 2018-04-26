#include "structTag.h"

struct tag{
	char* name;
	long id;
	int ocorrencias;
};

// Tags

// Init 

Tag initTag(){
	Tag new = malloc(sizeof(struct tag));
	return new;
}

Tag createTag(char* name, long id, int ocorrencias){
	Tag new = initTag();

	setTagName(new, name);
	setTagID(new, id);
	setTagOcor(new, ocorrencias);

	return new;
}

// Getters

char* getTagName(Tag tag){
	return mystrdup(tag->name);
}

long getTagID(Tag tag){
	return tag->id;
}

int getTagOcor(Tag tag){
	return tag->ocorrencias;
}

// Setters 

void setTagName(Tag tag, char* name){
	tag->name = mystrdup(name); 
}

void setTagID(Tag tag, long id){
	tag->id = id;
}

void setTagOcor(Tag tag, int ocor){
	tag->ocorrencias = ocor;
}

// Cleaner

void freeTags (Tag tag) {
	free(tag->name);
	free(tag);
} 


