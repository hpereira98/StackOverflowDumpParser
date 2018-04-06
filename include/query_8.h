#ifndef __QUERY8_H__
#define __QUERY8_H__

#include "toInclude.h"


void word_lookup(gpointer key_pointer, gpointer post_pointer, gpointer info);
LONG_list contains_word_aux(GTree* com_post, char* word, int N);

#endif