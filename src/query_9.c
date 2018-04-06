#include <query_9.h>

void swapAnswerPID (GTree* com_post, GArray* posts) {
	for (int i=0;i<posts->len;i++) {
		Post post = g_array_index(posts,Post,i);
		if (getPostTypeID(post)==2) {

			long pid = getPostParentID(post);
			Post newPost = g_hash_table_lookup(com_post,&pid);

			g_array_append_val(posts,newPost);
			g_array_remove_index(posts,i);
			i--;
		}
	}
}

LONG_list both_participated_aux(GHashTable* com_user, GTree* com_post, long id1, long id2, int N){
	
	User user1 = g_hash_table_lookup(com_user,&id1); 
	User user2 = g_hash_table_lookup(com_user,&id2);

	int nPostsUser1 = getUserNPosts(user1);
	int nPostsUser2 = getUserNPosts(user2);

	int ocupados = 0;

	GArray *posts1 = getClonedUserPosts(user1);
	GArray *posts2 = getClonedUserPosts(user2);
	
	swapAnswerPID(com_post,posts1);
	swapAnswerPID(com_post,posts2);

	g_array_sort(posts1,ordena);
	g_array_sort(posts2,ordena);
	
	LONG_list r = create_list(N); // ou até ocupados -> FALAR COM O PROF
	for (int i=0;i<N;i++) set_list(r,i,-2);

	for (int i=0;i < nPostsUser1;i++) {
		Post post1 = g_array_index(posts1,Post,i);
		for (int j=0;j < nPostsUser2 && ocupados<N ;j++) {
			Post post2 = g_array_index(posts2,Post,j);
			if (getPostID(post1) == getPostID(post2)){				
					set_list(r,ocupados,getPostID(post1));
					ocupados++;
			}
		}
	}
	
	return r;

} 
