#include <query_6.h>
/*
void ordenaScores(gpointer key_pointer, gpointer post_pointer, gpointer info){ // info = {ids, begin, end, ocupados, scores, N}
	struct Post* post = (struct Post*) post_pointer;

	if(post->type_id == 2){
		int pos;
		int* ids = ((int**)info)[0]; 
		Date begin = ((Date*)info)[1]; 
		Date end = ((Date*)info)[2]; 
		int *ocupados = ((int**)info)[3]; 
		int* scores = ((int**)info)[4]; 
		int size = *((int**)info)[5];

		int score = (post->n_upvotes)-(post->n_downvotes);

		if(comparaDatas(begin, post->data) == -1 && comparaDatas(post->data, end) == -1){
			if( (*ocupados != size) || (*ocupados == size && score > scores[size-1]) ){ // neste momento já sei que vai ser inserido
				pos = insert(scores, score, size);
				insereId(ids, post->id, pos, size);
				if(*ocupados < size) (*ocupados)++;
			}
		}	
	}

}


LONG_list most_voted_answers(TAD_community com, int N, Date begin, Date end){
	int* ids = malloc(sizeof(int)*N);
	int* scores = malloc(sizeof(int)*N);
	int* ocupados = malloc(sizeof(int)); *ocupados=0;
	int i;

	for(i = 0; i<N; i++){
		ids[i] = -2;
		scores[i] = -2;
	}

	void* info[6] = {(void*)ids, (void*)begin, (void*)end, (void*)ocupados, (void*)scores, (void*)&N};

	g_hash_table_foreach(com->post, ordenaScores, info);

	LONG_list r = create_list(N);	
	for(i = 0; i<N; i++) set_list(r, i, ids[i]);

	return r;
}

*/