#ifndef __CLEAN_H__
#define __CLEAN_H__

#include "interface.h"
#include "structs.h"
#include <gmodule.h>


void cleanUser (gpointer key, gpointer user_pointer, gpointer info);
void cleanPost (gpointer key, gpointer post_pointer, gpointer info);
void cleanTag (gpointer key, gpointer tag_pointer, gpointer info);

TAD_community clean_aux(GHashTable* users, GTree* posts, GHashTable* tags);

#endif
