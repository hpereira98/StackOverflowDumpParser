#ifndef __MYFUNCS_H__
#define __MYFUNCS_H__

#include "date.h"
#include <string.h>
#include <stdlib.h>
#include "interface.h"

//tirar estes depois
#include <glib.h>
#include "structs.h"
#include <stdio.h>




Date atribuiData(char* date);
int comparaDatas(Date a, Date b);
int ordena(gconstpointer a,gconstpointer b);
void printUserHT(gpointer key, gpointer value, gpointer user_data);
void printPostHTa(gpointer key, gpointer value, gpointer user_data);
int insert(int* array, int elem, int size);
int insertDate(Date* array, Date elem, int size);
void insereId(int* v, int x, int i, int n);

void ver_melhor_resposta (gpointer key, gpointer post, gpointer user_data);

#endif
