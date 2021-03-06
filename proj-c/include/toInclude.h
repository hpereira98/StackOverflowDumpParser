#ifndef __TO_INCLUDE__
#define __TO_INCLUDE__

/**
	@file toInclude.h
   
	Ficheiro .h com a que contém as bibliotecas necessárias à execução do programa, 
	assim como os ficheiros .h dos respetivos ficheiros .c desenvolvidos pelo grupo.
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
#include "structTCD.h"
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
#include <time.h> 

//#define SHOW_TIME	

#ifdef SHOW_TIME
#define TIME(X) X
#else
#define TIME(X)	
#endif

//#define SHOW_RESULT

#ifdef SHOW_RESULT
#define RESULT(X) X
#else
#define RESULT(X)
#endif

#endif
