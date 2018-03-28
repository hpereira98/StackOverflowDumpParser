#ifndef __STRUCTS_H__
#define __STRUCTS_H__

#include <glib.h>
#include <gmodule.h>
#include "my_funcs.h"

struct User{
	int id; // user id
	char* display_name; // username
	int rep; // reputação
	int n_perguntas; // número de perguntas
	int n_respostas; // número de respostas
	int n_posts; // número total de posts
	int reputacao;
	//Date data_posts[];
	//Date data_respostas[];
	//char* títulos[];
	char* short_bio; // descrição do user
	GArray* userPosts;

};

struct Post{
	int id;
	char* titulo;
	int owner_id;
	char* owner_display_name;
	int owner_rep;
	int type_id;
	int parent_id;
	Date data;
	char* tags;
	int score;
	int n_comments;
	int n_upvotes;
	int n_downvotes;
	int n_respostas;
	int accepted_answer; // testar q10 - POR EM COMENTARIO QUANDO NAO FOR NECESSARIO
};


struct TCD_community{
	GHashTable* user;
	GHashTable* post;	
};

#endif