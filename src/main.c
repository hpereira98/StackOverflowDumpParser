#include <interface.h>
#include <time.h>
#include <structs.h>
#include <query_5.h>
#include <my_funcs.h>



int main(){
	TAD_community teste = init();
	char* path = "../../dumpexemplo/android/";
	Date inicio = createDate(01,01,2010);
	Date fim = createDate(31,1,2020);

	

	clock_t begin = clock();
	load(teste, path);
	clock_t end = clock();
	//free(path);
	
	//clean(teste);
	
	printf("Tempo '0 - load' = %f\n----------------------------------\n", (double)(end-begin)/CLOCKS_PER_SEC);

	clock_t begin1 = clock();
	STR_pair new1 = info_from_post(teste, 9);
	//printf("%s -- %s\n",get_fst_str(new1),get_snd_str(new1) );
	clock_t end1 = clock();

	printf("Tempo '1 - info_from_post' = %f\n----------------------------------\n", (double)(end1-begin1)/CLOCKS_PER_SEC);
	
	clock_t begin2 = clock();
	LONG_list new2 = top_most_active(teste,10);
	clock_t end2 = clock();

	printf("Tempo '2 - top_most_active' = %f\n----------------------------------\n", (double)(end2-begin2)/CLOCKS_PER_SEC);

	Date inicio3 = createDate(01,07,2016);
	Date fim3 = createDate(31,07,2016);

	clock_t begin3 = clock();
	LONG_pair new3 = total_posts(teste, inicio3, fim3);
	//printf("NPerguntas %ld -- NRespostas %ld\n",get_fst_long(new3),get_snd_long(new3));
	clock_t end3 = clock();

	printf("Tempo '3 - total_posts' = %f\n----------------------------------\n", (double)(end3-begin3)/CLOCKS_PER_SEC);
	Date inicio4 = createDate(01,03,2013);
	Date fim4 = createDate(31,03,2016);

	clock_t begin4 = clock();
	char *aux = "package-management";
	LONG_list new4 = questions_with_tag(teste, aux, inicio4, fim4);
	clock_t end4 = clock();
	
	

	printf("Tempo '4 - questions_with_tag' = %f\n----------------------------------\n", (double)(end4-begin4)/CLOCKS_PER_SEC);


	clock_t begin5 = clock();
	
	int x = 9;
	USER new5 = get_user_info(teste, 245697);
	 /*if(new5){
		long *post_history;
		post_history = get_10_latest_posts(new5);
		printf("10_latest_posts:\n");
		for(int i=0;i<10;i++){
	   	printf("%ld\n", post_history[i]);
		}
	}
	*/
	
	clock_t end5 = clock();
	
	printf("Tempo '5 - get_user_info' = %f\n----------------------------------\n",(double)(end5-begin5)/CLOCKS_PER_SEC);
	Date inicio6 = createDate(01,11,2015);
	Date fim6 = createDate(30,11,2015);

	clock_t begin6 = clock();
	LONG_list new6 = most_voted_answers(teste, 5, inicio6, fim6);
	clock_t end6 = clock();

	printf("Tempo '6 - most_voted_answers' = %f\n----------------------------------\n", (double)(end6-begin6)/CLOCKS_PER_SEC);
	Date inicio7 = createDate(01,1,2012);
	Date fim7 = createDate(31,12,2012);

	clock_t begin7 = clock();
	LONG_list new7 = most_answered_questions(teste, 100, inicio7, fim7);
	clock_t end7 = clock();

	printf("Tempo '7 - most_answered_questions' = %f\n----------------------------------\n", (double)(end7-begin7)/CLOCKS_PER_SEC);


	clock_t begin8 = clock();
	LONG_list new8 = contains_word(teste, "a", 1000);
	
	clock_t end8 = clock();

	printf("Tempo '8 - contains_word' = %f\n----------------------------------\n", (double)(end8-begin8)/CLOCKS_PER_SEC);

	clock_t begin9 = clock();
	LONG_list new9 = both_participated(teste,29, 30, 5); // ids aleatórios
	clock_t end9 = clock();
  	

	printf("Tempo '9 - both_participated' = %f\n----------------------------------\n", (double)(end9-begin9)/CLOCKS_PER_SEC);


	clock_t begin10 = clock();
	long new10 = better_answer(teste, 30334); //escolher id para teste e verificar pelos prints em baixo
	clock_t end10 = clock();
	//printf("%li\n",new10);

	printf("Tempo '10 - better_answer' = %f\n----------------------------------\n", (double)(end10-begin10)/CLOCKS_PER_SEC);
	Date inicio11 = createDate(01,11,2013);
	Date fim11 = createDate(30,11,2013);

	clock_t begin11 = clock();
	LONG_list new11 = most_used_best_rep(teste, 100, inicio11, fim11);
	clock_t end11 = clock();
 
	printf("Tempo '11 - most_used_best_rep' = %f\n----------------------------------\n", (double)(end11-begin11)/CLOCKS_PER_SEC);
	


	clean(teste);

	free_date(inicio);
	free_date(fim);
	free_date(inicio3);
	free_date(fim3);
	free_date(inicio4);
	free_date(fim4);
	free_date(inicio6);
	free_date(fim6);
	free_date(inicio7);
	free_date(fim7);
	free_date(inicio11);
	free_date(fim11);
	free_list(new11);
	free_list(new9);
	free_list(new8);
	free_list(new7);
	free_list(new6);
	free_list(new2);
	free_user(new5);
	free_str_pair(new1);
	free_long_pair(new3);
	free_list(new4);


	/* Função para Debugging da Q10 */
	//g_hash_table_foreach(teste->post,(GHFunc)ver_melhor_resposta,"Post:%d,Best Answer:%d\n");

//	printf("%d -> melhor: %li\n",216,new10);


/* Funcao para Debugging da Q2:
g_hash_table_foreach(teste->user,(GHFunc)ver_num,"UserId:%d, Nº Perguntas:%d, Nº Respostas:%d\n");
*/

/* Funcao para Debugging de UserHashT*/
	//g_hash_table_foreach(teste->user,(GHFunc)printUserHT,NULL);
	//testeAcessoUserHT(teste,4980640);
/* Funcao para Debugging de PostHashT */
	//g_hash_table_foreach(teste->post,(GHFunc)printPostHTa,NULL); 


	/*STR_pair new ;
	new = info_from_post(teste,199);// 199 nao tem owner id apenas owner display name
	printf("\nPERGUNTA:\n%s \n%s\n\n",get_fst_str(new),get_snd_str(new));*/

	/*
	new = info_from_post(teste,7);
	printf("\nRESPOSTA À PERGUNTA:\n%s \n%s\n\n",get_fst_str(new),get_snd_str(new));
   	printf("Tamanho hash: %d\n",g_hash_table_size(teste->user)); */
  	
  	return 0;
} 


