#ifndef __QUERY9_H__
#define __QUERY9_H__

#include "interface.h"
#include "my_funcs.h"
#include "structs.h"
#include <gmodule.h>
#include <glib.h>
#include <stdio.h>
#include <stdlib.h>

void swapAnswerPID (TAD_community com, GArray* posts);
LONG_list both_participated(TAD_community com, long id1, long id2, int N);



#endif
