#ifndef __MYFUNCS_H__
#define __MYFUNCS_H__

#include "toInclude.h"

int searchFunc(STR_pair a, STR_pair b);
char* dateToString(Date date);
int cmpTreeKey(STR_pair a, STR_pair b);
int comparaDatas(char* a, char* b, char* c);
int ordena(gconstpointer a,gconstpointer b);
void printUserHT(gpointer key, gpointer value, gpointer user_data);
gboolean printPostTree(gpointer key, gpointer value, gpointer user_data);
void printPostAuxHT(gpointer key, gpointer value, gpointer user_data);
void printTagHT(GHashTable* com_tag);
int insert(int* array, int elem, int size);
int insertDate(Date* array, Date elem, int size);
void insereId(long* v, long x, int i, int n);
char* envolveTag(char* tag);
char* nextTag(char* tags, int *i);
void ver_melhor_resposta (gpointer key, gpointer post, gpointer user_data);

#endif
