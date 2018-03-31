#include <query_9.h>

// QUERY 9
/*
void swapAnswerPID (TAD_community com, GArray* posts) {
	for (int i=0;i<posts->len;i++) {
		struct Post* post = g_array_index(posts,struct Post*,i);
		if (post->type_id==2) {
			struct Post* newPost = g_hash_table_lookup(com->post,&(post->parent_id));
			g_array_append_val(posts,newPost);
			g_array_remove_index(posts,i);
			i--;
		}
	}
}

LONG_list both_participated(TAD_community com, long id1, long id2, int N){
	
	struct User* user1 = g_hash_table_lookup(com->user,&id1); 
	struct User* user2 = g_hash_table_lookup(com->user,&id2);

	int* ocupados = malloc(sizeof(int));
	*ocupados=0;

	GArray *posts1 = user1->userPosts;
	GArray *posts2 = user2->userPosts;
	
	printf("swap 1\n");
	swapAnswerPID(com,posts1);
	printf("swap 2\n");
	swapAnswerPID(com,posts2);

	g_array_sort(posts1,ordena);
	g_array_sort(posts2,ordena);
	
	LONG_list r = create_list(N); // ou até ocupados -> FALAR COM O PROF
	for (int i=0;i<N;i++) set_list(r,i,-2);

	for (int i=0;i<(user1->n_posts);i++) {
		struct Post* post1 = g_array_index(posts1,struct Post*,i);
		for (int j=0;j<(user2->n_posts) && *ocupados<N ;j++) {
			struct Post* post2 = g_array_index(posts2,struct Post*,j);
			if (post1->id == post2->id) {				
					set_list(r,*ocupados,post1->id);
					(*ocupados)++;
			}
		}
	}
	
	return r;

} 
*/