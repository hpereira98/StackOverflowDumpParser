#ifndef __QUERY7_H__
#define __QUERY7_H__

#include "toInclude.h"


int sortByNRespostas(Post* a, Post *b);
gboolean inserePosts(gpointer key_pointer, gpointer post_pointer, gpointer info);
LONG_list most_answered_questions_aux(GTree* com_post, int N, Date begin, Date end);


#endif