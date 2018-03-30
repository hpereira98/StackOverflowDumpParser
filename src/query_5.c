#include<query_5.h>

USER get_user_info(TAD_community com, long id){
	struct User* user = (struct User*)g_hash_table_lookup(com->user,&id);
	int i, size; long posts[10];
	struct Post* post; 
	USER res = NULL;

	if(user!=NULL){
		g_array_sort (user->userPosts,ordena);
		
		if((user->userPosts)->len > 10) 
			size = 10;
		else size = (user->userPosts)->len;

		for(i=0;i<size;i++){
				post = g_array_index(user->userPosts,struct Post*,i);

				if(post!=NULL)
					posts[i] = (long)(post->id);
				else posts[i] = -2;
		}
		res = create_user(user->short_bio,posts);
	}

	return res;
}	
