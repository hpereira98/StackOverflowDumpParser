#include <query_5.h>

USER get_user_info_aux(GHashTable* com_user, long id){
	User user = (User)g_hash_table_lookup(com_user,&id);
	int i, size; long posts[10];
	Post post; 
	USER res = NULL;

	if(user!=NULL){
		GArray* userPosts = getClonedUserPosts(user);
		
		g_array_sort (userPosts,ordena);
		
		if(userPosts->len >= 10) 
			size = 10;
		else size = userPosts->len;

		for(i=0;i<size;i++){
				post = g_array_index(userPosts,Post,i);

				if(post!=NULL)
					posts[i] = getPostID(post);
				else posts[i] = -2;
		}
		res = create_user( getUserShortBio(user),posts);
	}

	return res;
}	
