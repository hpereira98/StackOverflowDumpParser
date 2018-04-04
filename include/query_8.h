#ifndef __QUERY8_H__
#define __QUERY8_H__


#include "interface.h"
#include "my_funcs.h"
#include "structs.h"
#include <glib.h>
#include <gmodule.h>

void word_lookup(gpointer key_pointer, gpointer post_pointer, gpointer info);
LONG_list contains_word_aux(GHashTable* com_post, char* word, int N);

#endif