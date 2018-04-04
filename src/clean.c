/*
#include <clean.h>

void cleanUser (gpointer key, gpointer user_pointer, gpointer info) {
	User user = (User)user_pointer;
	if (user!=NULL) freeUser(user);
}

void cleanPost (gpointer key, gpointer post_pointer, gpointer info) {
	Post post = (Post)post_pointer;
	if (post!=NULL) freePost(post);
}

void cleanTag (gpointer key, gpointer tag_pointer, gpointer info) {
	Tag tag = (Tag)tag_pointer;
	if (tag!=NULL) freeTags(tag);
}


TAD_community clean(TAD_community com) {

	if (com!=NULL) {
		g_hash_table_foreach(com->user, cleanUser,NULL);
		g_hash_table_foreach(com->post, cleanPost,NULL);
		g_hash_table_foreach(com->tags, cleanTag,NULL);
	}

	return com;
}
*/