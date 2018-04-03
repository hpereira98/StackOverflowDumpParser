#include <init.h>

TAD_community init(){
	struct TCD_community* new = malloc(sizeof(struct TCD_community));

  	GHashTable* new_user_hash = g_hash_table_new(g_int_hash, g_int_equal);
  	GHashTable* new_post_hash = g_hash_table_new(g_int_hash, g_int_equal);
	GHashTable* new_tags_hash = g_hash_table_new(g_int_hash, g_int_equal);
  	
  	new->user = new_user_hash;
  	new->post = new_post_hash;
  	new->tags = new_tags_hash;

  	return new;
}
