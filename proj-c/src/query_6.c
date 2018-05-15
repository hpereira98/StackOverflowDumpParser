#include <query_6.h>



LONG_list most_voted_answers_aux(GTree* com_post, int N, Date begin, Date end){
	int size, typeId=2;
	Post post;

	char* date_begin = dateToString(begin);
	char* date_end = dateToString(end);

	GArray* answers = filterPostsByTypeID(com_post, date_begin, date_end, typeId);

	g_array_sort(answers,(GCompareFunc)sortByScore);

	size = selectSize(answers->len, N);

	LONG_list result = create_list(size);	

	for(int i=0; i<size; i++){
		post = g_array_index(answers, Post, i);	
		set_list(result, i, getPostID(post));

		RESULT(
			printf("%d --  postId: %ld Score: %d\n", i+1, getPostID(post), getPostScore(post));
		)
	}

	free(date_begin);
	free(date_end);
	g_array_free(answers, TRUE);
	
	return result;
}

