#include <query_1.h>


STR_pair info_from_post_aux(GTree* com_post, GHashTable* com_postAux, GHashTable* com_user, long id){
	STR_pair result = create_str_pair(NULL, NULL);

	Post post = getPost(com_post, com_postAux, id);

	if (post){

		if(getPostTypeID(post) == 2){ 
			long parentID = getPostParentID(post);
			Post parent = getPost(com_post, com_postAux, parentID);

			if(!parent) return result;
		}

		long ownerID = getPostOwnerID(post);
		User user = getUser(com_user, ownerID);

		char* display_name;

		if(user) display_name = getUserDisplayName(user);
		else display_name = NULL; 

		char* title = getPostTitle(post);

		set_fst_str(result, title);
		set_snd_str(result, display_name);	

		free(title);
		free(display_name);
	}	


	return result;
}
