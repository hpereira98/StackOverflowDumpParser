#include <query_8.h>


void word_lookup(gpointer key_pointer, gpointer post_pointer, gpointer info){
	Post post = (Post)post_pointer ; 

	if(getPostTypeID(post)==1){
		
		GArray* postArray = ((GArray**)info)[0];

		char* word = mystrdup(((char**)info)[1]);
		char* titulo = getPostTitle(post);
	
		if(strstr(titulo,word)!=NULL ){
			g_array_append_val(postArray,post);
		}

	}
}


LONG_list contains_word_aux(GHashTable* com_post, char* word, int N){
	GArray* postArray = g_array_new(FALSE,FALSE,sizeof(Post)); 
	Post post;
	int i, size;

	void* info[2] ={postArray,word};

	g_hash_table_foreach(com_post, word_lookup, info);

	g_array_sort(postArray,ordena);	
	
	if(postArray->len < N) size = postArray->len;
	else size = N;
	printf("%d\n", postArray->len);
	LONG_list postList = create_list(size);

	for(i = 0; i < size; i++){
		post = g_array_index(postArray,Post,i);
		set_list(postList, i, getPostID(post));
	}
		
	return postList;	
}

