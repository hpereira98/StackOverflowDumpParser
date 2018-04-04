#ifndef __QUERY2_H__
#define __QUERY2_H__

#include <interface.h>
#include <gmodule.h>
#include <glib.h>
#include <stdlib.h>
#include "structs.h"


void insertionSort (gpointer key, gpointer user_pointer, gpointer info);
LONG_list top_most_active_aux(GHashTable* com_user, int N);


#endif