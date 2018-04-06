#ifndef __QUERY9_H__
#define __QUERY9_H__

#include "toInclude.h"

void swapAnswerPID (GTree* com_post, GArray* posts);
LONG_list both_participated_aux(GHashTable* com_user, GTree* com_post, long id1, long id2, int N);



#endif
