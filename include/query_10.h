#ifndef __QUERY10_H__
#define __QUERY10_H__

#include "structs.h"
#include "interface.h"
#include "my_funcs.h"
#include <stdlib.h>
#include <gmodule.h>
#include <glib.h>


double answer_score (int score, int rep, int favs, int comments);
void bestAnswer (gpointer key_pointer, gpointer post_pointer, gpointer info);
long better_answer_aux(GHashTable* com_post, long id);

#endif
