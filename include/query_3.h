#ifndef __QUERY3_H__
#define __QUERY3_H__

#include "interface.h"
#include <gmodule.h>
#include <glib.h>
#include "my_funcs.h"
#include "structs.h"
#include <stdlib.h>

void posts_count(gpointer key, gpointer post_pointer, gpointer info);
LONG_pair total_posts_aux(GHashTable* com_posts, Date begin, Date end);


#endif