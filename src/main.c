#include <date.h>
#include <stdio.h>
#include <interface.h>
#include <libxml/parser.h>
#include <gmodule.h>
#include <glib.h>
#include <string.h>
#include <time.h>
#include "my_date.h"

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



// FUNCAO AUXILIAR DE INSERCAO, DEPOIS REMOVER DO main

int insert(int* array, int elem, int size){
	int i = 0;
	int pos = -1;

	for(i = 0; i<size && pos==-1; i++){
		if(array[i]<elem) pos = i;
	}
	for(i = size-1; i>pos; i--){
		array[i] = array[i-1];
	}

	array[pos] = elem;
	/*printf("inseriu em %d\n",pos );
	for(int j = 0; j<20;j++)
		printf("%d ",array[j] ); printf("E\n"); */
	return pos;
}

// para propósitos temporários (q9)
int insertDate(Date* array, Date elem, int size){
	int i = 0;
	int pos = -1;

	for(i = 0; i<size && pos==-1; i++){
		if(comparaDatas(array[i],elem)==-1) pos=i;
	}
	for(i = size-1; i>pos; i--){
		array[i] = array[i-1];
	}

	array[pos] = elem;
	/*printf("inseriu em %d\n",pos );
	for(int j = 0; j<20;j++)
		printf("%d ",array[j] ); printf("E\n"); */
	return pos;
}

void insereId(int* v, int x, int i, int n){

	for(n=n-1; n>i; n--){
		v[n] = v[n-1];
	}

	v[i] = x;
}



// QUERY 2

void insertionSort (gpointer key, gpointer user_pointer, gpointer info){
	struct User* user = (struct User*) user_pointer;

	int pos;
	int *idArray = ((int**)info)[0];
	int *countArray = ((int**)info)[1];
	int size = *((int**)info)[2];
	int *ocupados = ((int**)info)[3];
	int total = user->n_posts;

	// insere no array caso nao esteja ainda cheio, ou se estiver, n_posts maior que o menor elemento do array
	if( (*ocupados < size) || ( (*ocupados == size) && ( (user->n_posts) > countArray[(size)-1]) ) ){

		pos = insert(countArray,total,size);
		insereId(idArray,user->id,pos,size);

		if(*ocupados < (size)) (*ocupados)++;	

	}
	
}


LONG_list top_most_active(TAD_community com, int N) {
	
	LONG_list res = create_list(N);	
	
	int *ocupados = malloc(sizeof(int)); *ocupados=0;
	int id[N];
	int num_posts[N];

	for (int i=0;i<N;i++) {
		id[i] = num_posts[i]=-1;
	}
	
	void* info[4] = {id,num_posts,&N,ocupados};

	g_hash_table_foreach(com->user, insertionSort, info);

	for (int i=0;i<N;i++)
		set_list(res,i,(long)id[i]);

	return res;

}

// QUERY 3

void posts_count(gpointer key, gpointer post_pointer, gpointer info){
	
	struct Post* post = (struct Post*) post_pointer;
	Date post_date = post->data;

	Date begin = ((Date*)(info))[0];
	Date end = ((Date*)(info))[1];

	int* numQuestions = ((int**)(info))[2];
	int* numAnswers = ((int**)(info))[3];
	
	if(comparaDatas(post_date,begin)==1 && comparaDatas(end,post_date)==1){
		if(post->type_id==1) (*numQuestions)++;
			else (*numAnswers)++;
	}
}


LONG_pair total_posts(TAD_community com, Date begin, Date end){

	int *numQuestions = malloc(sizeof(int));
	int *numAnswers = malloc(sizeof(int));
	*numQuestions = *numAnswers = 0;

	void* info[4] = {begin, end, numQuestions, numAnswers};
	
	g_hash_table_foreach(com->post,posts_count,info);
	LONG_pair totalPost = create_long_pair(*numQuestions,*numAnswers);

	return totalPost;
}




// QUERY 5 ainda com erros

int ordena(gconstpointer a,gconstpointer b){
	int* a1 = (int*)a; int* b2 = (int*)b;
	if(*a1 == 0) return 1;
	if(*b2 == 0) return -1; 
	struct Post* post1 = (struct Post*)a;
	struct Post* post2 = (struct Post*)b;
	return comparaDatas(post1->data,post2->data) *(-1);
}

USER get_user_info(TAD_community com, long id){
	struct User* user = (struct User*)g_hash_table_lookup(com->user,&id);
	int i; long posts[10];
	USER res = NULL;
	if(user!=NULL){
		g_array_sort (user->userPosts,ordena);
		for(i=0;i<10;i++){
				struct Post* post = g_array_index(user->userPosts,struct Post*,i);
				if(post!=NULL)
					posts[i] = (long)post->id;
				else posts[i] = -2;
		}
		res = create_user(user->short_bio,posts);
	}
	return res;
}	





// QUERY 8

void printPostHT(struct Post* aux){
	if(aux!=NULL){
	printf("%d ",aux->id);
	printf("%d ",aux->type_id);
	printf("%d ",aux->owner_id);
	printf("%s ",aux->owner_display_name);
	printf("%d ",aux->parent_id);
	printf("%s\n",aux->titulo);
	} 
	else printf("null\n");
}

void insertByDate(struct Post* posts[],struct Post* post, int N, int* used){ //resultado: data mais recente para mais antiga
	int i = 0;
	int pos = 0;
	
	printf("%d",*used);
	for(i = 0; i < *used && pos==0; i++){
		printf("A comparar %d %d %d com %d %d %d\n",get_day(post->data),get_month(post->data),get_year(post->data),get_day(posts[i]->data),get_month(posts[i]->data),get_year(posts[i]->data));
		printf("%d\n",comparaDatas(post->data,(posts[i])->data));
		if(comparaDatas(post->data,(posts[i])->data)==1)
			break;		
	}

	pos = i;

	for(i = N-1; i>pos; i--){
		posts[i] = posts[i-1];
	}

	if(*used < N) (*used)++;
	posts[pos] = post;	

}



void word_lookup(gpointer key_pointer, gpointer post_pointer, gpointer info){
	struct Post* post = (struct Post*)post_pointer ; int i=0;
	if(post->type_id==1){
		
		char* titulo = malloc(strlen(post->titulo)+1);
		strcpy(titulo, post->titulo);

		char* word = malloc(strlen(((char**)info)[1])+1);
		strcpy(word,((char**)info)[1]);

		struct Post** postArray = ((struct Post***)info)[0];
	
		int size = *((int**)info)[2];
		
		int* ocupados = ((int**)info)[3];
	
		struct Post* last = postArray[size-1];// null ou endereço de um post
		printf("%d\n",*ocupados);
		printPostHT(post);

		if(strstr(titulo,word)!=NULL && ((*ocupados<size) || ((*ocupados == size) && (comparaDatas(post->data,last->data)==1)))){
			 insertByDate(postArray,post,size,ocupados);
			 printf("inseriu %dº\n",++i);
			 for(int aux=0;aux<10;aux++) if(postArray[aux]!=NULL)printf("%d\n",((struct Post*)(postArray[aux]))->id );
		}
	}
}

LONG_list contains_word(TAD_community com, char* word, int N){
	struct Post* postArray[N]; int i;

	for(i=0;i<N;i++) postArray[i]=NULL;

	int* ocupados = malloc(sizeof(int)); *ocupados=0;

	void* info[4] ={postArray,word,&N,ocupados};

	g_hash_table_foreach(com->post, word_lookup, info);

	LONG_list r = create_list(N);

	for(i = 0; i<N; i++) 
		if(postArray[i]!=NULL) 
			set_list(r, i, (postArray[i])->id);
		else 
			set_list(r,i,-2);


	return r;	
}

// QUERY 9

void dateInsertionSort (int id, Date data,int *ids,Date *datas, int* ocupados,int size) {
	
	int pos;
	if( (*ocupados < size) || ( (*ocupados == size) && ( comparaDatas(data,datas[(size)-1])==1 ) ) ){

		pos = insertDate(datas,data,size);
		insereId(ids,id,pos,size);

		// Debugging: imprime o array dos ids e das datas
		for (int i=0,i<*ocupados;i++)
			printf("PostId: %d, Data: %d-%d-%d",ids[i],get_day(datas[i]),get_month(datas[i]),get_year(datas[i]));
			
		if(*ocupados < (size)) (*ocupados)++;	

	}
}

LONG_list both_participated(TAD_community com, long id1, long id2, int N){
	
	struct User* user1 = malloc(sizeof(struct User));
	user1 = g_hash_table_lookup(com->user,&id1); 
	struct User* user2 = malloc(sizeof(struct User));
	user2 = g_hash_table_lookup(com->user,&id2);

	int *ids = malloc(sizeof(int)*N);
	Date *datas = malloc(sizeof(int)*N);
	for (int i=0;i<N;i++) {
		datas[i]=createDate(0,0,0);
		ids[i]=-2;
	}

	int* ocupados;
	*ocupados=0; // vai até N no máximo
	
	if (user1!=NULL && user2!=NULL) {
		for (int i=0;i<user1->n_posts;i++) {
			struct Post* post1 = g_array_index(user1->userPosts,struct Post*,i);

			if (post1!=NULL) {
				for (int j=i<user2->n_posts;i++) {
					
					struct Post* post2 = g_array_index(user2->userPosts,struct Post*,j);             //     dateInsertionSort NÃO DEFINIDA
				
					if (post2!=NULL) {
						if (post1->type_id == 1 && post2->type_id == 2 && post2->parent_id == post1->id) dateInsertionSort(post1->id,post1->data,ids,datas,ocupados,N); // post1 pergunta e post2 resposta: verificar se o pai do post2 é o post1
						else if (post1->type_id == 2 && post2->type_id == 1 && post1->parent_id == post2->id) dateInsertionSort(post2->id,post2->data,ids,datas,ocupados,N); // post1 resposta e post2 pergunta: verificar se o pai do post1 é o post2
						else if (post1->type_id == 2 && pos2->type_id == 2 && post1->parent_id == post2->parent_id) { // post1 e post2 respostas: verificar se têm o mm pai
							struct Post* post3 = g_hash_table_lookup(com->post,post2->parent_id);
							dateIinsertionSort(post3->id,post3->data,ids,datas,ocupados,N);
						}
					}
				}
			}
		}
	}
	
	LONG_list r = create_list(N); // ou até ocupados -> FALAR COM O PROF
	for (int i=0,i<N;i++) set_list(r,i,ids[i]);
	return r;

}


// QUERY 10

double answer_score (int score, int rep, int favs, int comments) {
	return ( (score*0.45)+(rep*0.25)+(favs*0.2)+(comments*0.1));
}

void bestAnswer (gpointer key_pointer, gpointer post_pointer, gpointer info) {
	struct Post* post = (struct Post*)post_pointer;
	int* parentId = ((int**)info)[0];
	double* max = ((double**)info)[1];
	int* answerId = ((int**)info)[2];
	double score;

	if (post->type_id == 2 && post->parent_id == *parentId) {
		score=answer_score(post->score, post->owner_rep, (post->n_upvotes)-(post->n_downvotes), post->n_comments);
		if (score>(*max)) {
			*max=score;
			*answerId=post->id;
		}
	}
}

long better_answer(TAD_community com, long id) {

	int* parentId = malloc(sizeof(int));
	*parentId=id;

	int *max = malloc(sizeof(int));
	*max=0;

	int *answerId = malloc(sizeof(int));

	void* info[3] = {(void*)parentId, (void*)max, (void*)answerId};

	g_hash_table_foreach(com->post, bestAnswer, info);



	return (long)*answerId;
}

// QUERY 11




/* Funcao para Debugging de PostHashT */


/* Funcao para Debugging de UserHashT */
void printUserHT(gpointer key, gpointer value, gpointer user_data){
	struct User* aux = (struct User*)value;
	int* keyId = (int* )key;
	printf(user_data,*keyId, aux->id, aux->display_name);
}

/* Funcao para verificar procura na UserHashT */ 
void testeAcessoUserHT(TAD_community com, int id){
	int* aux = malloc(sizeof(int));
	*aux=id;
	struct User* user = malloc(sizeof(struct User));
	user = (struct User*)g_hash_table_lookup(com->user, aux);
	if(user) printf("%d %s\n",user->id,user->display_name);
	 else printf("user not found\n");
}

// Função para verificar contagem do nº posts
void ver_num (gpointer key, gpointer value, gpointer user_data){
	struct User* aux = (struct User*)value;
	int* keyId = (int* )key;
	printf(user_data,*keyId, aux->n_respostas,aux->n_perguntas);
}

// Função para seleção da melhor resposta
void ver_melhor_resposta (gpointer key, gpointer post, gpointer user_data){
	struct Post* aux = (struct Post*)post;
	int* keyId = (int* )key;
	if (aux->type_id==1) printf(user_data,*keyId, aux->accepted_answer);
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
	LONG_list new9 = both_participated(teste,76,77); // ids aleatórios
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


