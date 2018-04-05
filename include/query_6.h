#ifndef __QUERY6_H__
#define __QUERY6_H__

#include "toInclude.h"


int sortByScore(Post* a, Post *b);
void inserePost(gpointer key_pointer, gpointer post_pointer, gpointer info);
LONG_list most_voted_answers_aux(GHashTable* com_post, int N, Date begin, Date end);


#endif