#include "query_8.h"



void insertByDate(Post posts[],Post post, int N, int* used){ //resultado: data mais recente para mais antiga
	int i = 0;
	int pos = 0;
	
	//printf("%d",*used);
	for(i = 0; i < *used && pos==0; i++){
		/*Debuggin*/ //printf("A comparar %d %d %d com %d %d %d\n",get_day(post->data),get_month(post->data),get_year(post->data),get_day(posts[i]->data),get_month(posts[i]->data),get_year(posts[i]->data));
		/*Debuggin*/ //printf("%d\n",comparaDatas(post->data,(posts[i])->data));

		if(comparaDatas(getPostDate(post),getPostDate(posts[i]))==1)
			break;		
	}

	pos = i;

	for(i = N-1; i>pos; i--){
		posts[i] = posts[i-1];
	}

	if(*used < N) (*used)++;
	posts[pos] = post;	

}


void word_lookup(gpointer key_pointer, gpointer post_pointer, gpointer info){
	Post post = (Post)post_pointer ; 

	if(getPostTypeID(post)==1){
		
		char* titulo = getPostTitle(post);
		char* word = mystrdup(((char**)info)[1]);

		GArray* postArray = ((GArray**)info)[0];

		int* ocupados = ((int**)info)[3];
		int size = postArray->len;

		//if(size!=0) Post last = g_array_index(postArray,Post,size-1);// null ou endereço de um post

		/*Debuggin*/ //printf("%d\n",*ocupados);

		if(strstr(titulo,word)!=NULL ){
			//insertByDate(postArray,post,size,ocupados);
			g_array_append_val(postArray,post);
			/*Debuggin*/ //printf("inseriu %dº\n",++i);
			/*Debuggin*/ //for(int aux=0;aux<10;aux++) if(postArray[aux]!=NULL)printf("%d\n",((struct Post*)(postArray[aux]))->id );
		}
	}
}


LONG_list contains_word(TAD_community com, char* word, int N){
	GArray* postArray = g_array_new(FALSE,FALSE,sizeof(Post)); int i;

	//for(i=0;i<N;i++) postArray[i]=NULL;

	int* used = malloc(sizeof(int)); *used=0;

	void* info[4] ={postArray,word,&N,used};

	g_hash_table_foreach(com->post, word_lookup, info);

	g_array_sort(postArray,ordena);	
	printf("TAMANHO DO ARRAY: %d\n",postArray->len);
	int size;
	if(postArray->len < N) size = postArray->len;
	else size = N;

	LONG_list r = create_list(size);

	for(i = 0; i < size; i++) 
			set_list(r, i, getPostID(g_array_index(postArray,Post,i)));
		


	return r;	
}
