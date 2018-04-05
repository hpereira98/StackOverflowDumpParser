#include <query_7.h>


int sortByNRespostas(Post* a, Post *b){
	int n_resp_a = getPostNRespostas(*a);
	int n_resp_b = getPostNRespostas(*b);
	
	return n_resp_b - n_resp_a;
}

void inserePosts(gpointer key_pointer, gpointer post_pointer, gpointer info){
	Post post = (Post) post_pointer;

	if(getPostTypeID(post) == 1){
		Date begin = ((Date*)info)[0]; 
		Date end = ((Date*)info)[1]; 
		Date postDate = getPostDate(post);
		GArray* posts = ((GArray**)info)[2];

		if(comparaDatas(begin, postDate) == -1 && comparaDatas(postDate, end) == -1){
			g_array_append_val(posts, post);
		}	
	}
}


LONG_list most_answered_questions_aux(GHashTable* com_post, int N, Date begin, Date end){
	GArray* posts = g_array_new(FALSE,FALSE,sizeof(Post));
	int size;
	Post post;

	void* info[6] = {(void*)begin, (void*)end, (void*)posts};
	
	g_hash_table_foreach(com_post, inserePosts, info);
	
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
