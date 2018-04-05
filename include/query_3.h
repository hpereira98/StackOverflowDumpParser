#ifndef __QUERY3_H__
#define __QUERY3_H__

#include "toInclude.h"

void posts_count(gpointer key, gpointer post_pointer, gpointer info);
LONG_pair total_posts_aux(GHashTable* com_posts, Date begin, Date end);


#endif