#ifndef __MYFUNCS_H__
#define __MYFUNCS_H__

#include "toInclude.h"


char* dateToString(Date date);
int cmpTreeKey(PostKey a, PostKey b);
int comparaDatas(char* a, char* b, char* c);
int ordena(gconstpointer a,gconstpointer b);
void printUserHT(gpointer key, gpointer value, gpointer user_data);
gboolean printPostTree(gpointer key, gpointer value, gpointer user_data);
void printPostAuxHT(gpointer key, gpointer value, gpointer user_data);
void printTagHT(GHashTable* com_tag);
char* nextTag(char* tags, int *i);
void ver_melhor_resposta (gpointer key, gpointer post, gpointer user_data);

#endif
