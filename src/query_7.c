#include <query_7.h>


int sortByNRespostas(Post* a, Post *b){
	int n_resp_a = getPostNRespostas(*a);
	int n_resp_b = getPostNRespostas(*b);
	
	return n_resp_b - n_resp_a;
}

gboolean inserePosts(gpointer key_pointer, gpointer post_pointer, gpointer info){
	Post post = (Post) post_pointer; 

	if(getPostTypeID(post) == 1){
		char* begin = ((char**)info)[0]; 
		char* end = ((char**)info)[1]; 
		char* post_date = getPostSimpleDate(post);
		GArray* posts = ((GArray**)info)[2];

		int dateCheck = comparaDatas(begin, end, post_date);

		if(dateCheck == -1) return TRUE;

		if(dateCheck == 0) g_array_append_val(posts, post);
	}	

	return FALSE;
}


LONG_list most_answered_questions_aux(GTree* com_post, int N, Date begin, Date end){
	int size;
	Post post;
	GArray* posts = g_array_new(FALSE,FALSE,sizeof(Post));

	char* date_begin = dateToString(begin);
	char* date_end = dateToString(end);

	void* info[3] = {(void*)date_begin, (void*)date_end, (void*)posts};
	
	g_tree_foreach(com_post, (GTraverseFunc)inserePosts, info);
	
	g_array_sort(posts,(GCompareFunc)sortByNRespostas);

	if(posts->len>N) size = N;
	else size = posts->len;

	LONG_list result = create_list(size);	

	for(int i=0; i<size; i++){
		post = g_array_index(posts, Post, i);
		set_list(result, i, getPostID(post));
		/************/printf("Pos: %d Id: %ld Score: %d\n",i,getPostID(post),getPostNRespostas(post));
	}

	return result;
}
