#ifndef __QUERY4_H__
#define __QUERY4_H__

#include <stdlib.h>
#include "date.h"
#include <glib.h>
#include "interface.h"
#include <string.h>
#include "my_funcs.h"
#include "structs.h"

void adicionaComTag(gpointer key_pointer, gpointer post_pointer, gpointer info);
void addToLongList(gpointer key_pointer, gpointer id_pointer, gpointer info);
LONG_list questions_with_tag_aux(GHashTable* com_post, char* tag, Date begin, Date end);

#endif