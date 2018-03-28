#include <query_2.h>

// QUERY 2

void insertionSort (gpointer key, gpointer user_pointer, gpointer info){
	struct User* user = (struct User*) user_pointer;

	int pos;
	int *idArray = ((int**)info)[0];
	int *countArray = ((int**)info)[1];
	int size = *((int**)info)[2];
	int *ocupados = ((int**)info)[3];
	int total = user->n_posts;

	// insere no array caso nao esteja ainda cheio, ou se estiver, n_posts maior que o menor elemento do array
	if( (*ocupados < size) || ( (*ocupados == size) && ( (user->n_posts) > countArray[(size)-1]) ) ){

		pos = insert(countArray,total,size);
		insereId(idArray,user->id,pos,size);

		if(*ocupados < (size)) (*ocupados)++;	

	}
	
}


LONG_list top_most_active(TAD_community com, int N) {
	
	LONG_list res = create_list(N);	
	
	int *ocupados = malloc(sizeof(int)); *ocupados=0;
	int id[N];
	int num_posts[N];

	for (int i=0;i<N;i++) {
		id[i] = num_posts[i]=-1;
	}
	
	void* info[4] = {id,num_posts,&N,ocupados};

	g_hash_table_foreach(com->user, insertionSort, info);

	for (int i=0;i<N;i++)
		set_list(res,i,(long)id[i]);

	return res;

}