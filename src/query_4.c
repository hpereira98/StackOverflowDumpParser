#include <query_4.h>
/*
 Função que verifica se um Post contém a tag passada como argumento à Query 4.
*/
gboolean adicionaComTag(gpointer key_pointer, Post post, gpointer info){ 
	GArray* questionsID = ((GArray**)(info))[0];

	long* tagID = ((long**)(info))[1];

	char* post_date = getPostSimpleDate(post);
	char* begin = ((char**)(info))[2];
	char* end = ((char**)(info))[3]; 

	int added = 0;
	int dateCheck = comparaDatas(begin, end, post_date);

	free(post_date); 

	if(dateCheck == -1) return TRUE;

	long postID;
	long tagID_temp;
	GArray* post_tags;

	if(dateCheck == 0 && getPostTypeID(post) == 1){
		post_tags = getPostTags(post);

		if(post_tags != NULL){

			for(int i = 0; i<post_tags->len && !added; i++){
				tagID_temp = g_array_index(post_tags, long, i);
	
				if(tagID_temp == *tagID){
					postID = getPostID(post);
					g_array_append_val(questionsID, postID);
					added++;
				}
			}
		}
	}
	return FALSE;
}


LONG_list questions_with_tag_aux(GTree* com_post, GHashTable* com_tags, char* tagName, Date begin, Date end){

	char* date_begin = dateToString(begin);
	char* date_end = dateToString(end);

	Tag tag = getTag(com_tags, tagName);

	if(!tag) return create_list(0);

	long tagID = getTagID(tag);

	GArray* questionsID = g_array_new(FALSE, FALSE, sizeof(long));
	
	void* info[4] = {questionsID, &tagID, date_begin, date_end};

	g_tree_foreach(com_post, (GTraverseFunc)adicionaComTag, info);

	int size = questionsID->len;
	LONG_list result = create_list(size);

	for(int i=0; i<size; i++){
		long id = g_array_index(questionsID,long,i);
		set_list(result, i, id);

		SHOW_RESULT( 
			printf("%d -- PostId: %ld\n", i+1, id); 
		)
	}

	free(date_begin);
	free(date_end);
	g_array_free(questionsID, TRUE);
	
	return result;
}
