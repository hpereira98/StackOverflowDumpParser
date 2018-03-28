#include<query_5.h>

int ordena(gconstpointer a,gconstpointer b){
	int* a1 = (int*)a; int* b2 = (int*)b;
	if(*a1 == 0) return 1;
	if(*b2 == 0) return -1; 
	struct Post* post1 = (struct Post*)a;
	struct Post* post2 = (struct Post*)b;
	return comparaDatas(post1->data,post2->data) *(-1);
}

USER get_user_info(TAD_community com, long id){
	struct User* user = (struct User*)g_hash_table_lookup(com->user,&id);
	int i; long posts[10];
	USER res = NULL;
	if(user!=NULL){
		g_array_sort (user->userPosts,ordena);
		for(i=0;i<10;i++){
				struct Post* post = g_array_index(user->userPosts,struct Post*,i);
				if(post!=NULL)
					posts[i] = (long)post->id;
				else posts[i] = -2;
		}
		res = create_user(user->short_bio,posts);
	}
	return res;
}	