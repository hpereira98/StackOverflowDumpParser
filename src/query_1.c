#include <query_1.h>


STR_pair info_from_post_aux(GTree* com_post, GHashTable* com_postAux, GHashTable* com_user, long id){
	STR_pair result = create_str_pair(NULL, NULL);

	Post post = getPost(com_post, com_postAux, id);

	if (!post) printf("Post not found...\n");
	else {
		if(getPostTypeID(post)==2){ //caso seja uma resposta...
			long parentID = getPostParentID(post);
			post = getPost(com_post, com_postAux, parentID);
		}

		long ownerID = getPostOwnerID(post);
		User user = getUser(com_user, ownerID); 	

		char* title = getPostTitle(post);
		char* display_name = getUserDisplayName(user);

		set_fst_str(result, title);
		set_snd_str(result, display_name);	

		free(title);
		free(display_name);
	}	


	return result;
}
