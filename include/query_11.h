#ifndef __QUERY11_H__
#define __QUERY11_H__

#include "interface.h"
#include <gmodule.h>
#include <glib.h>
#include "structs.h"
#include <string.h>


void ordenaUsers(gpointer key_pointer, gpointer user_pointer, gpointer info);
int ordenaTags(Tag a, Tag b);
char* nextTag(char* tags, int *i);
int elemTag(GArray* array, char* name);
void adicionaTag(GArray* array, char* tags, TAD_community com);
LONG_list most_used_best_rep(TAD_community com, int N, Date begin, Date end);


#endif