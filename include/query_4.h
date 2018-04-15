#ifndef __QUERY4_H__
#define __QUERY4_H__

//#define DEBUG_MODE
#include "toInclude.h"

gboolean adicionaComTag(gpointer key_pointer, gpointer post_pointer, gpointer info);
void addToLongList(gpointer key_pointer, gpointer id_pointer, gpointer info);
LONG_list questions_with_tag_aux(GTree* com_post, char* tag, Date begin, Date end);

#endif