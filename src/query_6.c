#include <query_6.h>


int sortByScore(Post* a, Post *b){
	int score_a = getPostNUpVotes(*a) - getPostNDownVotes(*a);
	int score_b = getPostNUpVotes(*b) - getPostNDownVotes(*b);
	
	return score_b - score_a;
}


gboolean inserePost(gpointer key_pointer, gpointer post_pointer, gpointer info){
	Post post = (Post) post_pointer;

	if(getPostTypeID(post) == 2){
		Date begin = ((Date*)info)[0]; 
		Date end = ((Date*)info)[1]; 
		Date post_date = getPostSimpleDate(post);
		GArray* posts = ((GArray**)info)[2];

		if(comparaDatas(begin, end, post_date) == 0){
			g_array_append_val(posts, post);
		}	

		else if(comparaDatas(begin, end, post_date) == -1) return TRUE;

	}

	return FALSE;
}


LONG_list most_voted_answers_aux(GTree* com_post, int N, Date begin, Date end){
	GArray* posts = g_array_new(FALSE, FALSE, sizeof(Post));
	int size;
	Post post;

	void* info[3] = {(void*)begin, (void*)end, (void*)posts};

	g_tree_foreach(com_post, (GTraverseFunc)inserePost, info);

	g_array_sort(posts,(GCompareFunc)sortByScore);

	if(posts->len>N) size = N;
	else size = posts->len;

	LONG_list r = create_list(size);	

	for(int i=0; i<size; i++){
		post = g_array_index(posts, Post, i);
		set_list(r, i, (long)getPostID(post));
	}
	return r;
}

