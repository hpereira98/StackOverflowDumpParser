#ifndef __QUERY9_H__
#define __QUERY9_H__

#include "interface.h"
#include "my_funcs.h"
#include "structs.h"
#include <gmodule.h>
#include <glib.h>
#include <stdio.h>
#include <stdlib.h>

void dateInsertionSort (int id, Date data,int *ids,Date *datas, int* ocupados,int size);
LONG_list both_participated(TAD_community com, long id1, long id2, int N);
void get_question_ids (struct User* user, int *ids, Date *datas,int* ocupados,int size);


#endif
