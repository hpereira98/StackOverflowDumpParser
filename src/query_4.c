#include <query_4.h>

gboolean adicionaComTag(gpointer key_pointer, gpointer post_pointer, gpointer info){ 

	GArray* questionsID = ((GArray**)(info))[0];
	Post post = (Post) post_pointer;
	char* tag = ((char**)(info))[1];

	char* post_date = getPostSimpleDate(post);
	char* begin = ((char**)(info))[2];
	char* end = ((char**)(info))[3]; 

	int added = 0;
	int dateCheck = comparaDatas(begin, end, post_date);

	if(dateCheck == -1) return TRUE;

	long postID;
	char* tag_temp;
	GArray* post_tags;

	if(dateCheck == 0 && getPostTypeID(post) == 1){
		post_tags = getPostTags(post);

		if(post_tags != NULL){

			for(int i = 0; i<post_tags->len && !added; i++){
				tag_temp = g_array_index(post_tags, char*, i);
				
				if(strcmp(tag_temp, tag) == 0){
					postID = getPostID(post);
					g_array_append_val(questionsID, postID);
					added++;
				}
			}
		}	
	}

	return FALSE;
}


LONG_list questions_with_tag_aux(GTree* com_post, char* tag, Date begin, Date end){

	char* date_begin = dateToString(begin);
	char* date_end = dateToString(end);

	GArray* questionsID = g_array_new(FALSE, FALSE, sizeof(long));
	void* info[4] = {questionsID, tag, date_begin, date_end};

	g_tree_foreach(com_post, (GTraverseFunc)adicionaComTag, info);

	int size = questionsID->len;
	LONG_list result = create_list(size);

	for(int i=0; i<size; i++){
		long id = g_array_index(questionsID,long,i);
		set_list(result, i, id);
		/*******/ printf("Pos: %d postId: %ld\n",i,id);
	}

	return result;
}
