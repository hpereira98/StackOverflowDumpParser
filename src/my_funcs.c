#include "my_funcs.h"
#include <string.h>
#include <stdlib.h>
 


// Datas

Date atribuiData(char* date){ // "AAAA-MM-DD"
	char* ano_str = malloc(5);
	char* mes_str = malloc(3);
	char* dia_str = malloc(3);
	int ano, mes, dia;

	strncpy(ano_str, date, 4);
	strncpy(mes_str, date+5, 2);
	strncpy(dia_str, date+8, 2);

	ano = atoi(ano_str);
	mes = atoi(mes_str);
	dia = atoi(dia_str);

	return (createDate(dia, mes, ano));
}

int comparaDatas(Date a, Date b){ // se a primeira for mais pequena que a segunda retorna -1

	// Compara o ano
	if(get_year(a) > get_year(b)) return 1;
	if(get_year(a) < get_year(b)) return -1;

	// Compara o mês - se chegaram aqui é proque o ano é o mesmo
	if(get_month(a) > get_month(b)) return 1;
	if(get_month(a) < get_month(b)) return -1;

	// Compara o dia - se chegaram aqui é porque o ano e o mês são os mesmos
	if(get_day(a) > get_day(b)) return 1;
	if(get_day(a) < get_day(b)) return -1;

	return 0;
}



// Ordenar Arrays

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