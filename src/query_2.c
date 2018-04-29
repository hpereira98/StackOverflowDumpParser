#include <query_2.h>

LONG_list top_most_active_aux(GHashTable* com_user, int N) {
	User user; 
	int i;

	GArray* users = usersHashToGArray(com_user);

	g_array_sort(users, (GCompareFunc)sortByNPosts);

	int size = selectSize(users->len ,N);
	
	LONG_list result = create_list(size);

	for (i=0; i<size; i++){
		user = g_array_index(users, User, i);
		set_list(result, i, getUserID(user));
		/*****************/ printf("Pos: %d Id: %ld NumPosts %d\n",i ,getUserID(user),getUserNPosts(user));
	}

	g_array_free(users, TRUE);

	return result;
}
