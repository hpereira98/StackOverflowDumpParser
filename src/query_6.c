#include <query_6.h>

int sortByScore(Post* a, Post *b){
	int score_a = getPostScore(*a);
	int score_b = getPostScore(*b);
	return score_b - score_a;
}


LONG_list most_voted_answers_aux(GTree* com_post, int N, Date begin, Date end){
	GArray* posts = g_array_new(FALSE, FALSE, sizeof(Post));
	int size;
	Post post;

	char* date_begin = dateToString(begin);
	char* date_end = dateToString(end);

	void* info[3] = {(void*)date_begin, (void*)date_end, (void*)posts};

	g_tree_foreach(com_post, (GTraverseFunc)inserePosts, info);

	g_array_sort(posts,(GCompareFunc)sortByScore);

	if(posts->len>N) size = N;
	else size = posts->len;

	LONG_list result = create_list(size);	

	for(int i=0; i<size; i++){
		post = g_array_index(posts, Post, i);
		set_list(result, i, getPostID(post));
	}
	return result;
}

