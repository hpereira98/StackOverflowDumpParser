#include <query_7.h>


int sortByNRespostas(Post* a, Post *b){
	int n_resp_a = getPostNRespostas(*a);
	int n_resp_b = getPostNRespostas(*b);
	
	return n_resp_b - n_resp_a;
}

gboolean inserePosts(gpointer key_pointer, gpointer post_pointer, gpointer info){
	Post post = (Post) post_pointer;

	if(getPostTypeID(post) == 1){
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


LONG_list most_answered_questions_aux(GTree* com_post, int N, Date begin, Date end){

	GArray* posts = g_array_new(FALSE,FALSE,sizeof(Post));
	int size;
	Post post;

	void* info[6] = {(void*)begin, (void*)end, (void*)posts};
	
	g_tree_foreach(com_post, (GTraverseFunc)inserePosts, info);
	
	g_array_sort(posts,(GCompareFunc)sortByNRespostas);

	if(posts->len>N) size = N;
	else size = posts->len;

	LONG_list r = create_list(size);	

	for(int i=0; i<size; i++){
		post = g_array_index(posts, Post, i);
		set_list(r, i, (long)getPostID(post));
	}

	return r;
}
