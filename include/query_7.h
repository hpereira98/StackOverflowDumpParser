#ifndef __QUERY7_H__
#define __QUERY7_H__

#include "date.h"
#include <glib.h>
#include "interface.h"
#include "structs.h"
#include <stdlib.h>


void ordenaNRespostas(gpointer key_pointer, gpointer post_pointer, gpointer info);
LONG_list most_answered_questions_aux(GHashTable* com_post, int N, Date begin, Date end);


#endif