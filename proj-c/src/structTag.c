#include "structTag.h"

struct tag{
	char* name;
	long id;
};

// Tags

// Init 

Tag initTag(){
	Tag new = malloc(sizeof(struct tag));
	return new;
}

// Getters

char* getTagName(Tag tag){
	return mystrdup(tag->name);
}

long getTagID(Tag tag){
	return tag->id;
}


// Setters 

void setTagName(Tag tag, char* name){
	tag->name = mystrdup(name); 
}

void setTagID(Tag tag, long id){
	tag->id = id;
}

// Cleaner

void freeTags (Tag tag) {
	free(tag->name);
	free(tag);
} 


