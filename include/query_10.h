#ifndef __QUERY10_H__
#define __QUERY10_H__

#include <stdlib.h>
#include <interface.h>
#include <gmodule.h>
#include <glib.h>
#include "structs.h"

double answer_score (int score, int rep, int favs, int comments);
void bestAnswer (gpointer key_pointer, gpointer post_pointer, gpointer info);
long better_answer(TAD_community com, long id);

#endif