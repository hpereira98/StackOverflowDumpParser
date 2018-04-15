#ifndef __QUERY11_H__
#define __QUERY11_H__

//#define DEBUG_MODE
#include "toInclude.h"

int sortByRep(User* a,User *b);
void ordenaUsers(gpointer key_pointer, gpointer user_pointer, gpointer info);
int sortByTagOcor(Tag* a, Tag* b);
char* nextTag(char* tags, int *i);
int elemTag(GArray* array, char* name);
void adicionaTag(GArray* array, GArray* tags, GHashTable* com_tags);
LONG_list most_used_best_rep_aux(GHashTable* com_user, GHashTable* com_tags, int N, Date begin, Date end);


#endif