#include <query_5.h>

USER get_user_info_aux(GHashTable* com_user, long id){
	int i, size; long postsID[10];
	Post post; 
	USER res = NULL;
	
	User user = (User)g_hash_table_lookup(com_user,&id);

	if(user!=NULL){
		GArray* userPosts = getUserPosts(user);
		
		g_array_sort (userPosts,ordena);
		
		if(userPosts->len >= 10) 
			size = 10;
		else size = userPosts->len;

		for(i=0;i<size;i++){
				post = g_array_index(userPosts,Post,i);

				if(post!=NULL)
					postsID[i] = getPostID(post);
				else postsID[i] = -2;
		}
		res = create_user( getUserShortBio(user),postsID);
	}

	return res;
}	
