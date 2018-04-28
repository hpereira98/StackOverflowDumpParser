#ifndef __CLEAN_H__
#define __CLEAN_H__

#include "interface.h"
#include "structs.h"
#include <gmodule.h>


TAD_community clean_aux(GHashTable* users, GTree* posts, GHashTable* postAux, GHashTable* tags);

#endif
