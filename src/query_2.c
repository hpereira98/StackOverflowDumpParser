#include <query_2.h>

int sortByNPosts(User* a,User *b){
	int nposts1 = getUserNPosts(*a);
	int nposts2 = getUserNPosts(*b);
	return nposts2-nposts1;
}

void insertionSort (gpointer key, gpointer user_pointer, gpointer info){
	
	User user = (User)user_pointer;
	GArray* users = (GArray*)info;

	g_array_append_val(users,user);

}


LONG_list top_most_active_aux(GHashTable* com_user, int N) {

	GArray* users = g_array_new(FALSE,FALSE,sizeof(User));
	User user; 
	int i, size;

	g_hash_table_foreach(com_user, insertionSort, users);

	g_array_sort(users,(GCompareFunc)sortByNPosts);


	if(users->len>N) size = N;
	else size = users->len;


	LONG_list res = create_list(size);

	for (i=0;i<size;i++){
		user = g_array_index(users,User,i);
		set_list(res,i,getUserID(user));

	}

	return res;

}
