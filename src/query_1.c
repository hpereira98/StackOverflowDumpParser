#include <query_1.h>


STR_pair info_from_post(TAD_community com, long id){
	STR_pair new = create_str_pair(NULL, NULL);

	struct Post* post = malloc(sizeof(struct Post));
	post = (struct Post*)g_hash_table_lookup(com->post, &id);
	
	if (!post) printf("Post not found...\n");
	else { 
		if(post->parent_id != -2){ //caso seja uma resposta...
			post = (struct Post*)g_hash_table_lookup(com->post, &post->parent_id);
		}

		if(*(post->owner_display_name)=='\0'){
			struct User* user = malloc(sizeof(struct User));
			user = (struct User*)g_hash_table_lookup(com->user, &post->owner_id); 
			
			set_fst_str(new, post->titulo);
			set_snd_str(new, user->display_name);
		}
		else new = create_str_pair(post->titulo, post->owner_display_name);
	}	

	return new;
}