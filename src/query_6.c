#include <query_6.h>

void ordenaScores(gpointer key_pointer, gpointer post_pointer, gpointer info){ // info = {ids, begin, end, ocupados, scores, N}
	Post post = (Post) post_pointer;

	if(getPostTypeID(post) == 2){
		int pos;
		long* ids = ((long**)info)[0]; 
		Date begin = ((Date*)info)[1]; 
		Date end = ((Date*)info)[2]; 
		int *ocupados = ((int**)info)[3]; 
		int* scores = ((int**)info)[4]; 
		int size = *((int**)info)[5];
		Date postDate = getPostDate(post);
		long postID = getPostID(post);
		int score = getPostNUpVotes(post) - getPostNDownVotes(post);

		if(comparaDatas(begin,postDate ) == -1 && comparaDatas(postDate, end) == -1){
			if( (*ocupados != size) || (*ocupados == size && score > scores[size-1]) ){ // neste momento já sei que vai ser inserido
				pos = insert(scores, score, size);
				insereId(ids, postID, pos, size);
				if(*ocupados < size) (*ocupados)++;
			}
		}	
	}

}


LONG_list most_voted_answers_aux(GHashTable* com_post, int N, Date begin, Date end){
	long* ids = malloc(sizeof(long)*N);
	int* scores = malloc(sizeof(int)*N);
	int* ocupados = malloc(sizeof(int)); *ocupados=0;
	int i;

	for(i = 0; i<N; i++){
		ids[i] = -2;
		scores[i] = -2;
	}

	void* info[6] = {(void*)ids, (void*)begin, (void*)end, (void*)ocupados, (void*)scores, (void*)&N};

	g_hash_table_foreach(com_post, ordenaScores, info);

	LONG_list r = create_list(N);	
	for(i = 0; i<N; i++) set_list(r, i, ids[i]);

	return r;
}

