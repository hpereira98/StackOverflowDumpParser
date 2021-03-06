#include <query_7.h>


LONG_list most_answered_questions_aux(GTree* com_post, int N, Date begin, Date end){
	int size, typeId=1;
	Post post;

	char* date_begin = dateToString(begin);
	char* date_end = dateToString(end);

	GArray* questions = filterPostsByTypeID(com_post, date_begin, date_end, typeId);
	
	g_array_sort(questions,(GCompareFunc)sortByNAnswers);

	size = selectSize(questions->len, N);

	LONG_list result = create_list(size);	

	for(int i=0; i<size; i++){
		post = g_array_index(questions, Post, i);
		set_list(result, i, getPostID(post));

		RESULT(
			printf("%d --  postId: %ld numRespostas: %d\n", i+1, getPostID(post), getPostNAnswers(post));
		)	
	}

	free(date_begin);
	free(date_end);
	g_array_free(questions, TRUE);

	return result;
}
