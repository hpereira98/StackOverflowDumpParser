#include <interface.h>
#include <gmodule.h>
#include <glib.h>
#include "my_date.h"

void posts_count(gpointer key, gpointer post_pointer, gpointer info);
LONG_pair total_posts(TAD_community com, Date begin, Date end);