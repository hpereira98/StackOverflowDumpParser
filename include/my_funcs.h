#ifndef __MYFUNCS_H__
#define __MYFUNCS_H__

#include "toInclude.h"

int postTreeSearch(STR_pair a, STR_pair b);
int cmpIsoDate(STR_pair a, STR_pair b);
int comparaDatas(Date a, Date b, Date c);
int ordena(gconstpointer a,gconstpointer b);
void printUserHT(gpointer key, gpointer value, gpointer user_data);
gboolean printPostTree(gpointer key, gpointer value, gpointer user_data);
void printPostAuxHT(gpointer key, gpointer value, gpointer user_data);
int insert(int* array, int elem, int size);
int insertDate(Date* array, Date elem, int size);
void insereId(long* v, long x, int i, int n);
char* envolveTag(char* tag);

void ver_melhor_resposta (gpointer key, gpointer post, gpointer user_data);

#endif
