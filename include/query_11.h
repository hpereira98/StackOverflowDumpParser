#ifndef __QUERY11_H__
#define __QUERY11_H__

#include "structs.h"
#include "interface.h"
#include <gmodule.h>
#include <glib.h>
#include <string.h>


void ordenaUsers(gpointer key_pointer, gpointer user_pointer, gpointer info);
int ordenaTags(Tag* a, Tag* b);
char* nextTag(char* tags, int *i);
int elemTag(GArray* array, char* name);
void adicionaTag(GArray* array, char* tags, GHashTable* com_tags);
LONG_list most_used_best_rep_aux(GHashTable* com_user,GHashTable* com_tags, int N, Date begin, Date end);


#endif