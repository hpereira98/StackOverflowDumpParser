#include <date.h>
#include <stdio.h>
#include <interface.h>
#include <libxml/parser.h>
#include <gmodule.h>
#include <glib.h>
#include <string.h>
#include <time.h>

/*NOTAS:
&#xA - \n codificado
&quot - "
&apos - '
&lt - <
&gt - >
&amp - &
*/



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



TAD_community init(){
	struct TCD_community* new = malloc(sizeof(struct TCD_community));
  	GHashTable* newUserHash = g_hash_table_new(g_int_hash, g_int_equal);
  	GHashTable* newPostHash = g_hash_table_new(g_int_hash, g_int_equal);

  	new->user = newUserHash;
  	new->post = newPostHash;

  	return new;
}



int main(){
	struct TCD_community* teste = init();
	char* path = "../../dumpexemplo/android/";
	Date inicio = createDate(12,9,2010);
	Date fim = createDate(14,9,2010);

	clock_t begin = clock();
	load(teste, path);
	clock_t end = clock();

	printf("Tempo '0 - load' = %f\n", (double)(end-begin)/CLOCKS_PER_SEC);

	clock_t begin1 = clock();
	STR_pair new = info_from_post(teste,199);
	clock_t end1 = clock();

	printf("Tempo '1 - info_from_post' = %f\n", (double)(end1-begin1)/CLOCKS_PER_SEC);
	
	clock_t begin5 = clock();
	LONG_list new3 = top_most_active(teste,500);
	/*for (int it=0;it<500;it++) {
		printf("%dº: %li ",(it+1),get_list(new3,it));
		int *aux = malloc(sizeof(int));
		*aux = get_list(new3,it);
		struct User* user = g_hash_table_lookup(teste->user,aux);
		if(user) printf("%d\n",user->n_perguntas+user->n_respostas);
	}*/
	clock_t end5 = clock();

	printf("Tempo '2 - top_most_active' = %f\n", (double)(end5-begin5)/CLOCKS_PER_SEC);

	clock_t begin3 = clock();
	LONG_pair new1 = total_posts(teste,inicio,fim);
	//printf("%ld %ld\n",get_fst_long(new1),get_snd_long(new1));
	clock_t end3 = clock();

	printf("Tempo '3 - total_posts' = %f\n", (double)(end3-begin3)/CLOCKS_PER_SEC);

	clock_t begin4 = clock();
	LONG_list new2 = questions_with_tag(teste, "android", inicio, fim);
	clock_t end4 = clock();

	printf("Tempo '4 - questions_with_tag' = %f\n", (double)(end4-begin4)/CLOCKS_PER_SEC);

	clock_t begin6 = clock();
	LONG_list new4 = most_voted_answers(teste, 100, inicio, fim);
	//for(int i=0;i<100;i++) printf("%ld\n",get_list(new4, i));
	clock_t end6 = clock();

	printf("Tempo '6 - most_voted_answers' = %f\n", (double)(end6-begin6)/CLOCKS_PER_SEC);

	clock_t begin7 = clock();
	LONG_list new5 = most_answered_questions(teste, 100, inicio, fim);
	//for(int i=0;i<100;i++) printf("%ld\n",get_list(new5, i));
	clock_t end7 = clock();

	printf("Tempo '7 - most_answered_questions' = %f\n", (double)(end7-begin7)/CLOCKS_PER_SEC);



	LONG_list new8 = contains_word(teste,"there",10);
	for(int aux=0;aux<10;aux++) printf("%ld ",get_list(new8,aux));
	printf("\n");

	clock_t begin9 = clock();
	//LONG_list new9 = both_participated(teste,76,77, 10); // ids aleatórios
	clock_t end9 = clock();

	printf("Tempo '9 - both_participated' = %f\n", (double)(end9-begin9)/CLOCKS_PER_SEC);


	//clock_t begin8 = clock();
	//LONG_list new10 = better_answer(teste,76); //escolher id para teste e verificar pelos prints em baixo
	//clock_t end8 = clock();

	/* Função para Debugging da Q10 */
	//g_hash_table_foreach(teste->post,(GHFunc)ver_melhor_resposta,"Post:%d,Best Answer:%d\n");

	//printf("Tempo '10 - better_answer' = %f\n", (double)(end8-begin8)/CLOCKS_PER_SEC);


/* Funcao para Debugging da Q2:
g_hash_table_foreach(teste->user,(GHFunc)ver_num,"UserId:%d, Nº Perguntas:%d, Nº Respostas:%d\n");
*/

/* Funcao para Debugging de UserHashT*/
	//g_hash_table_foreach(teste->user,(GHFunc)printUserHT,"%d %d %s\n");
	//testeAcessoUserHT(teste,4980640);
/* Funcao para Debugging de PostHashT */
	//g_hash_table_foreach(teste->post,(GHFunc)printPostHT,NULL); 


	/*STR_pair new ;
	new = info_from_post(teste,199);// 199 nao tem owner id apenas owner display name
	printf("\nPERGUNTA:\n%s \n%s\n\n",get_fst_str(new),get_snd_str(new));*/

	/*
	new = info_from_post(teste,7);
	printf("\nRESPOSTA À PERGUNTA:\n%s \n%s\n\n",get_fst_str(new),get_snd_str(new));
   	printf("Tamanho hash: %d\n",g_hash_table_size(teste->user)); */
  	
  	return 0;
} 


