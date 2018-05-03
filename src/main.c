#include <interface.h>
#include <time.h>
#include <structTCD.h>
#include <query_5.h>
#include <my_funcs.h>



int main(){
	char* path = "../../dumpexemplo/ubuntu/";

	long idQ1 = 796430;

	int nQ2 = 10;

	Date inicio3 = createDate(1,1,2014);
	Date fim3 = createDate(31,12,2014);

	char* tagToLookup = "nautilus";
	Date inicio4 = createDate(01,01,2014);
	Date fim4 = createDate(31,01,2014);

	long idQ5 = 449;

	int nQ6 = 50;
	Date inicio6 = createDate(01,05,2013);
	Date fim6 = createDate(06,05,2013);

	int nQ7 = 100;
	Date inicio7 = createDate(01,01,2012);
	Date fim7 = createDate(31,12,2012);

	char* wordQ8 = "glib";
	int nQ8 = 10;

	long id1Q9 = 253;
	long id2Q9 = 455;
	int nQ9 = 5;

	long idQ10 = 5942;

	int nQ11 = 10;
	Date inicio11 = createDate(01,01,2014);
	Date fim11 = createDate(31,12,2014);	

	
	TAD_community teste = init();

	TIME( clock_t begin = clock();)
	
	load(teste, path);
	
	TIME(
		clock_t end = clock();	
		printf("Tempo '0 - load' = %f\n----------------------------------\n", (double)(end-begin)/CLOCKS_PER_SEC);
	)

	TIME( clock_t begin1 = clock();)
	
	RESULT(printf("***** Resultado '1 - info_from_post' ******\n");)
	STR_pair new1 =  info_from_post(teste, idQ1);
	
	TIME(
		clock_t end1 = clock();
		printf("Tempo '1 - info_from_post' = %f\n----------------------------------\n", (double)(end1-begin1)/CLOCKS_PER_SEC);
	)

	TIME( clock_t begin2 = clock();)
	
	RESULT(printf("***** Resultado '2 - top_most_active' ******\n");)
	LONG_list new2 = top_most_active(teste, nQ2);
	
	TIME(
		clock_t end2 = clock();
		printf("Tempo '2 - top_most_active' = %f\n----------------------------------\n", (double)(end2-begin2)/CLOCKS_PER_SEC);
	)	

	TIME( clock_t begin3 = clock();)
	
	RESULT(printf("***** Resultado '3 - total_posts' ******\n");)
	LONG_pair new3 = total_posts(teste, inicio3, fim3);
	
	TIME(
		clock_t end3 = clock();
		printf("Tempo '3 - total_posts' = %f\n----------------------------------\n", (double)(end3-begin3)/CLOCKS_PER_SEC);
	)

	TIME( clock_t begin4 = clock();)
	
	RESULT(printf("***** Resultado '4 - questions_with_tag' ******\n");)
	LONG_list new4 = questions_with_tag(teste, tagToLookup, inicio4, fim4);
	
	TIME(
		clock_t end4 = clock();
		printf("Tempo '4 - questions_with_tag' = %f\n----------------------------------\n", (double)(end4-begin4)/CLOCKS_PER_SEC);
	)

	TIME( clock_t begin5 = clock();)
	
	RESULT(printf("***** Resultado '5 - get_user_info' ******\n");)
	USER new5 = get_user_info(teste, idQ5);	
	
	TIME(
		clock_t end5 = clock();
		printf("Tempo '5 - get_user_info' = %f\n----------------------------------\n",(double)(end5-begin5)/CLOCKS_PER_SEC);
	)

	TIME( clock_t begin6 = clock();)
	
	RESULT(printf("***** Resultado '6 - most_voted_answers' ******\n");)
	LONG_list new6 = most_voted_answers(teste, nQ6, inicio6, fim6);
	
	TIME(
		clock_t end6 = clock();
		printf("Tempo '6 - most_voted_answers' = %f\n----------------------------------\n", (double)(end6-begin6)/CLOCKS_PER_SEC);
	)

	TIME( clock_t begin7 = clock();)
	
	RESULT(printf("***** Resultado '7 - most_answered_questions' ******\n");)
	LONG_list new7 = most_answered_questions(teste, nQ7, inicio7, fim7);
	
	TIME(
		clock_t end7 = clock();
		printf("Tempo '7 - most_answered_questions' = %f\n----------------------------------\n", (double)(end7-begin7)/CLOCKS_PER_SEC);
	)

	TIME( clock_t begin8 = clock();)

	RESULT(printf("***** Resultado '8 - contains_word' ******\n");)
	LONG_list new8 = contains_word(teste, wordQ8, nQ8);
	
	TIME(
		clock_t end8 = clock();
		printf("Tempo '8 - contains_word' = %f\n----------------------------------\n", (double)(end8-begin8)/CLOCKS_PER_SEC);
	)

	TIME( clock_t begin9 = clock();)
	
	RESULT(printf("***** Resultado '9 - both_participated' ******\n");)
	LONG_list new9 = both_participated(teste, id1Q9, id2Q9, nQ9);
	
	TIME(
		clock_t end9 = clock();
		printf("Tempo '9 - both_participated' = %f\n----------------------------------\n", (double)(end9-begin9)/CLOCKS_PER_SEC);
	)

	TIME( clock_t begin10 = clock();)
	
	RESULT(printf("***** Resultado '10 - better_answer' ******\n");)
	better_answer(teste, idQ10);
	
	TIME(
		clock_t end10 = clock();
		printf("Tempo '10 - better_answer' = %f\n----------------------------------\n", (double)(end10-begin10)/CLOCKS_PER_SEC);
	)

	TIME( clock_t begin11 = clock();)

	RESULT(printf("***** Resultado '11 - most_used_best_rep' ******\n");)
	LONG_list new11 = most_used_best_rep(teste, nQ11, inicio11, fim11);
	
	TIME(
		clock_t end11 = clock();
		printf("Tempo '11 - most_used_best_rep' = %f\n----------------------------------\n", (double)(end11-begin11)/CLOCKS_PER_SEC);
	)

	clean(teste);


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

	free_str_pair(new1);
	free_list(new2);
	free_long_pair(new3);
	free_list(new4);
	free_user(new5);
	free_list(new6);
	free_list(new7);
	free_list(new8);
	free_list(new9);
	free_list(new11);

  	return 0;
} 


