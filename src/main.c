#include <interface.h>
#include <time.h>
#include <structs.h>
#include <query_5.h>
#include <my_funcs.h>

/*NOTAS:
&#xA - \n codificado
&quot - "
&apos - '
&lt - <
&gt - >
&amp - &
*/
void printTagsHT(gpointer key, gpointer tag, gpointer info){
	Tag tag1 = (Tag)tag;

	printf("%s %li\n",(char*)key,getTagID(tag));
}

int compare_ints(gpointer a, gpointer b) {
 		int* x = (int*)a;
 		int* y = (int*)b;
 		return (-1) * (*x - *y);
	}


int main(){
	struct TCD_community* teste = init();
	char* path = "../../dumpexemplo/android/";
	Date inicio = createDate(1,1,2000);
	Date fim = createDate(31,2,2020);

	clock_t begin = clock();
	load(teste, path);
	clock_t end = clock();
	
	printf("Tempo '0 - load' = %f\n", (double)(end-begin)/CLOCKS_PER_SEC);

	clock_t begin1 = clock();
	//STR_pair new1 = info_from_post(teste,212);
	//printf("%s %s\n",get_fst_str(new1),get_snd_str(new1) );
	clock_t end1 = clock();

	printf("Tempo '1 - info_from_post' = %f\n", (double)(end1-begin1)/CLOCKS_PER_SEC);
	
	clock_t begin2 = clock();
	LONG_list new2 = top_most_active(teste,1000);
	/*for (int it=0;it<1000;it++){
		printf("%dº: %li\n",(it+1),get_list(new2,it));
	}*/
	clock_t end2 = clock();

	printf("Tempo '2 - top_most_active' = %f\n", (double)(end2-begin2)/CLOCKS_PER_SEC);

	clock_t begin3 = clock();
	//LONG_pair new3 = total_posts(teste,inicio,fim);
	//printf("%ld %ld\n",get_fst_long(new1),get_snd_long(new1));
	clock_t end3 = clock();

	printf("Tempo '3 - total_posts' = %f\n", (double)(end3-begin3)/CLOCKS_PER_SEC);

	clock_t begin4 = clock();
	//LONG_list new4 = questions_with_tag(teste, "android", inicio, fim);
	clock_t end4 = clock();

	printf("Tempo '4 - questions_with_tag' = %f\n", (double)(end4-begin4)/CLOCKS_PER_SEC);


	clock_t begin5 = clock();
	long id = 9;
	//USER new5 = get_user_info(teste,id);
	clock_t end5 = clock();

	printf("Tempo '5 - get_user_info' = %f\n",(double)(end5-begin5)/CLOCKS_PER_SEC);

	clock_t begin6 = clock();
	LONG_list new6 = most_voted_answers(teste, 100000, inicio, fim);
	//for(int i=0;i<100;i++) printf("%ld\n",get_list(new6, i));
	clock_t end6 = clock();

	printf("Tempo '6 - most_voted_answers' = %f\n", (double)(end6-begin6)/CLOCKS_PER_SEC);


	clock_t begin7 = clock();
	LONG_list new7 = most_answered_questions(teste, 100000, inicio, fim);
	//for(int i=0;i<100;i++) printf("%ld\n",get_list(new5, i));
	clock_t end7 = clock();

	printf("Tempo '7 - most_answered_questions' = %f\n", (double)(end7-begin7)/CLOCKS_PER_SEC);


	clock_t begin8 = clock();
	//LONG_list new8 = contains_word(teste,"a",100000);
	/*
	for(int aux=0;aux<43691;aux++) {
		int id = get_list(new8,aux);
		printf("%d %d ",aux,id);
		Post post = g_hash_table_lookup(teste->post,&id); Date data = getPostDate(post);
		printf("%d %d %d\n",get_day(data),get_month(data),get_year(data));
	}
	*/

	
	clock_t end8 = clock();

	printf("Tempo '8 - contains_word' = %f\n", (double)(end8-begin8)/CLOCKS_PER_SEC);

	clock_t begin9 = clock();
	//LONG_list new9 = both_participated(teste,16575,1465, 10); // ids aleatórios
	clock_t end9 = clock();

	//for(int i=0;i<10;i++) printf("%d: %li\n",i+1,get_list(new9,i));

	printf("Tempo '9 - both_participated' = %f\n", (double)(end9-begin9)/CLOCKS_PER_SEC);


	clock_t begin10 = clock();
	//long new10 = better_answer(teste,216); //escolher id para teste e verificar pelos prints em baixo
	clock_t end10 = clock();

	printf("Tempo '10 - better_answer' = %f\n", (double)(end10-begin10)/CLOCKS_PER_SEC);

	//g_hash_table_foreach(teste->tags,(GHFunc)printTagsHT,NULL);

	
	clock_t begin11 = clock();
	LONG_list new11 = most_used_best_rep(teste, 100000, inicio, fim);
	clock_t end11 = clock();

	printf("Tempo '11 - most_used_best_rep' = %f\n", (double)(end11-begin11)/CLOCKS_PER_SEC);





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


