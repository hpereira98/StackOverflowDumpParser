#include <query_1.h>

STR_pair info_from_post_aux(GHashTable* com_post,GHashTable* com_user, long id){
	STR_pair new = create_str_pair(NULL, NULL);

	Post post = (Post)g_hash_table_lookup(com_post, &id);
	
	if (!post) printf("Post not found...\n");
	else {
		if(getPostTypeID(post)==2){ //caso seja uma resposta...
			int parentID = getPostParentID(post);
			post = (Post) g_hash_table_lookup(com_post, &parentID);
		}
		if(!getPostOwnerDisplayName(post)){
			int ownerID = getPostOwnerID(post);
			User user = (User)g_hash_table_lookup(com_user, &ownerID); 
			
			set_fst_str(new, getPostTitle(post));
			set_snd_str(new, getUserDisplayName(user));
		}
		else new = create_str_pair(getPostTitle(post), getPostOwnerDisplayName(post));
	}	

	return new;
}
