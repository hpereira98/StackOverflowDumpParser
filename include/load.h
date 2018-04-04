#ifndef __LOAD_H__
#define __LOAD_H__

#include "interface.h"
#include <libxml/parser.h>
#include "structs.h"
#include <string.h>

void load_aux(GHashTable* com_user, GHashTable* com_post ,GHashTable* com_tags, char* dump_path);
TAD_community init();


#endif