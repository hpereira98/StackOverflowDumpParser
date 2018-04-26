#include <query_5.h>

USER get_user_info_aux(GHashTable* com_user, long id){
	long postsID[10] = {[0 ... 9] = -2};

	int i, size;
	Post post; 
	USER res = NULL;
	
	User user = getUser(com_user, id);
	
	if(user!=NULL){
		GArray* userPosts = getClonedUserPosts(user);
		
		g_array_sort (userPosts,(GCompareFunc)sortByDate);
		
		size = selectSize(userPosts->len, 10);
		
		for(i=0;i<size;i++){
				post = g_array_index(userPosts,Post,i);

				postsID[i] = getPostID(post);

		}
		char* short_bio = getUserShortBio(user);

		res = create_user(short_bio, postsID);
		/************/ //printf("%s\n", getUserShortBio(user));
		//g_array_free(userPosts, TRUE);
		free(short_bio);
	}

	return res;
}	
