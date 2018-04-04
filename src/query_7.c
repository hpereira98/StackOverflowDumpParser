#include <query_7.h>

void ordenaNRespostas(gpointer key_pointer, gpointer post_pointer, gpointer info){ // info = {ids, begin, end, ocupados, n_respostas, N}
	Post post = (Post)post_pointer;

	if(getPostTypeID(post)== 1){
		int pos;
		int* ids = ((int**)info)[0];
		Date begin = ((Date*)info)[1];
		Date end = ((Date*)info)[2];
		int *ocupados = ((int**)info)[3];
		int* n_respostas = ((int**)info)[4];
		int size = *((int**)info)[5];
		Date postDate = getPostDate(post);
		int postID = getPostID(post);
		int postNRespostas = getPostNRespostas(post);

		if(comparaDatas(begin, postDate) == -1 && comparaDatas(postDate, end) == -1){
			if( (*ocupados != size) || (*ocupados == size && postNRespostas > n_respostas[size-1]) ){ // neste momento já sei que vai ser inserido
				pos = insert(n_respostas, postNRespostas, size);
				insereId(ids, postID, pos, size);
				if(*ocupados < size) (*ocupados)++;
			}
		}
	}

}

LONG_list most_answered_questions_aux(GHashTable* com_post, int N, Date begin, Date end){
	int* ids = malloc(sizeof(int)*N);
	int* n_respostas = malloc(sizeof(int)*N);
	int *ocupados = malloc(sizeof(int)); *ocupados=0;
	int i;

	for(i = 0; i<N; i++){
		ids[i] = -2;
		n_respostas[i] = -2;
	}

	void* info[6] = {(void*)ids, (void*)begin, (void*)end, (void*)ocupados, (void*)n_respostas, (void*)&N};
	
	g_hash_table_foreach(com_post, ordenaNRespostas, info);

	LONG_list r = create_list(*ocupados);	
	for(i = 0; i<*ocupados; i++) set_list(r, i, ids[i]);

	return r;
}
