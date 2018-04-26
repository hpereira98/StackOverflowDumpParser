#ifndef __TO_INCLUDE__
#define __TO_INCLUDE__

/**
	@file toInclude.h
   
	Definição...
*/

#include <gmodule.h>
#include <glib.h>
#include <stdlib.h>
#include <libxml/parser.h>
#include <string.h>
#include <stdio.h>
#include "interface.h"
#include "common.h"
#include "structPost.h"
#include "structs.h"
#include "structUser.h"
#include "structTag.h"
#include "my_funcs.h"
#include "load.h"
#include "query_1.h"
#include "query_2.h"
#include "query_3.h"
#include "query_4.h"
#include "query_5.h"
#include "query_6.h"
#include "query_7.h"
#include "query_8.h"
#include "query_9.h"
#include "query_10.h"
#include "query_11.h"
#include "clean.h"
#include <time.h> // remover depois 

#ifndef DEBUG_MODE
#define DEBUG(X) X
#else
#define DEBUG(X)
#endif

#endif
