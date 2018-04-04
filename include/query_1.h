#ifndef __QUERY1_H__
#define __QUERY1_H__

#include <stdio.h> // tirar depois de tirar os prints
#include <glib.h>
#include "interface.h"
#include "structs.h"
#include <stdlib.h>

STR_pair info_from_post_aux(GHashTable* com_post,GHashTable* com_user, long id);

#endif