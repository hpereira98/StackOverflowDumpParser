#ifndef __QUERY10_H__
#define __QUERY10_H__

#include "toInclude.h"

double answer_score (int score, int rep, int comments);
gboolean bestAnswer (gpointer key_pointer, gpointer post_pointer, gpointer info);
long better_answer_aux(GTree* com_post,GHashTable* com_postAux, long id);

#endif
