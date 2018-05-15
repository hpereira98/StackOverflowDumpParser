#include <query_8.h>


gboolean word_lookup(gpointer key_pointer, Post post, gpointer info){

	if(getPostTypeID(post)==1){
		
		GArray* postIDArray = ((GArray**)info)[0];

		char* word = ((char**)info)[1];

		char* titulo = getPostTitle(post);

		if(strstr(titulo,word)!=NULL ){
			long postId = getPostID(post);
			g_array_append_val(postIDArray, postId);
		}
		
		free(titulo);

	}
	return FALSE;
}


LONG_list contains_word_aux(GTree* com_post, char* word, int N){
	GArray* postIDArray = g_array_new(FALSE,FALSE,sizeof(long)); 
	long postID;
	int i, size;

	void* info[2] = {postIDArray,word};

	g_tree_foreach(com_post, (GTraverseFunc)word_lookup, info);
	
	size = selectSize(postIDArray->len, N);
	
	LONG_list postList = create_list(size);

	for(i = 0; i < size; i++){
		postID = g_array_index(postIDArray,long,i);
		set_list(postList, i, postID);

		RESULT(
			printf("%d --  postId: %ld\n", i+1, postID);
		)
	}

	g_array_free(postIDArray, TRUE);
		
	return postList;	
}

