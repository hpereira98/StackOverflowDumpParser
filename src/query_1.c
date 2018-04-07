#include <query_1.h>

/*
STR_pair info_from_post_aux(GTree* com_post, GHashTable* com_postAux, GHashTable* com_user, long id){
	STR_pair new = create_str_pair(NULL, NULL);

	Post post = getPost(com_post, com_postAux, id);

	if (!post) printf("Post not found...\n");
	else {
		if(getPostTypeID(post)==2){ //caso seja uma resposta...
			long parentID = getPostParentID(post);
			post = getPost(com_post, com_postAux, parentID);
		}
		if(!getPostOwnerDisplayName(post)){
			long ownerID = getPostOwnerID(post);
			User user = (User)g_hash_table_lookup(com_user, &ownerID); 
			
			set_fst_str(new, getPostTitle(post));
			set_snd_str(new, getUserDisplayName(user));
		}
		else new = create_str_pair(getPostTitle(post), getPostOwnerDisplayName(post));
	}	

	return new;
}
*/