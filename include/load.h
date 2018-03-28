#ifndef __LOAD_H__
#define __LOAD_H__

#include "interface.h"
#include <libxml/parser.h>
#include "structs.h"
#include <string.h>

TAD_community load(TAD_community com, char* dump_path);


#endif