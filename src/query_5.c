#include <query_5.h>

USER get_user_info_aux(GHashTable* com_user, long id){
	long postsID[10] = {[0 ... 9] = -2};

	int i, size;
	Post post; 
	USER result = NULL;
	
	User user = getUser(com_user, id);
	
	if(user!=NULL){
		GArray* userPosts = getClonedUserPosts(user);
		
		if(userPosts){
			g_array_sort(userPosts,(GCompareFunc)sortByDate);
		
			size = selectSize(userPosts->len, 10);
		
			for(i=0;i<size;i++){
				post = g_array_index(userPosts,Post,i);
				postsID[i] = getPostID(post);
			}	

			g_array_free(userPosts, TRUE);		
		}	

		char* short_bio = getUserShortBio(user);

		result = create_user(short_bio, postsID);

		free(short_bio);
	}

	RESULT(
		if(result){
			char* shortBio = get_bio(result);
			long* posts = get_10_latest_posts(result);
			printf("ShortBio: %s\nPosts do User:\n", shortBio);
			for(i=0; i<10; i++)
				printf("%d -- PostID: %ld\n", i, posts[i]);
			free(posts);
		}
	)

	return result;
}	
