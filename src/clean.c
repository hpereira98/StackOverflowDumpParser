#include <clean.h>


TAD_community clean_aux(GHashTable* users, GTree* posts, GHashTable* postAux ,GHashTable* tags) {
	g_hash_table_remove_all(users);
	g_hash_table_remove_all(postAux);
	g_tree_destroy(posts);
	g_hash_table_remove_all(tags);


	return NULL; 
}
