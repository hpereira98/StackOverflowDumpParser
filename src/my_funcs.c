#include <my_funcs.h>


// Datas



int cmpTreeKey(STR_pair a, STR_pair b){

	/* Debugging */ // printf("(%s %s) e (%s %s)\n",get_fst_str(a),get_snd_str(a), get_fst_str(b),get_snd_str(b) );
	
	if(strcmp(get_snd_str(a), get_snd_str(b)) == 0) return 0; // caso os posts tenham o mesmo id para a procura

	int r = strcmp(get_fst_str(a), get_fst_str(b));

	if(r==0) r = 1; // evitar que posts com strings de data iguais nao deixem de ser inseridos na btree
	
	return (-1)*r; // inverter ordem cronologica
}

int comparaDatas(Date a, Date b, Date c){ // se a primeira for mais pequena que a segunda retorna -1

	// Compara o ano
	if(get_year(c) < get_year(a)) return -1;
	else if(get_year(b) < get_year(c)) return 1;

	// Compara o mês - se chegaram aqui é proque o ano é o mesmo
	if(get_month(c) < get_month(a)) return -1;
	else if(get_month(b) < get_month(c)) return 1;

	// Compara o dia - se chegaram aqui é porque o ano e o mês são os mesmos
	if(get_day(c) < get_day(a)) return -1;
	else if(get_day(b) < get_day(c)) return 1;

	return 0;
}

int ordena(gconstpointer a,gconstpointer b){
	Post post1 = *((Post*)(a));
	Post post2 = *((Post*)(b));
	return strcmp(getPostDate(post1),getPostDate(post2))*(-1);
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

/*
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
		printf("%d ",array[j] ); printf("E\n");
	return pos;
}*/

void insereId(long* v, long x, int i, int n){

	for(n=n-1; n>i; n--){
		v[n] = v[n-1];
	}

	v[i] = x;
}



// String

char* envolveTag(char* tag){
	char* aux = malloc(strlen(tag) + 2);
	int i;
	
	aux[0] = '<';
	for(i = 1; i<strlen(tag) + 1; i++) aux[i] = tag[i-1];
	aux[i] = '>';

	return aux;

}





/* Funcao para Debugging de PostHashT */

gboolean printPostTree(gpointer key, gpointer value, gpointer user_data){
	Post post = (Post)value;
	
	int* i = ((int*)user_data);
	printf("%d %s %ld %s\n",(*i)++,getPostDate(post),getPostID(post),getPostTitle(post));
 	
	return FALSE;
}

void printPostAuxHT(gpointer key, gpointer value, gpointer user_data){
	PostAux postAux = (PostAux)value;
	
	int* i = ((int*)user_data);
	printf("%d %d %s\n",(*i)++,*((int*)key),getPostAuxDate(postAux));
 	
}

/* Funcao para Debugging de UserHashT */
/*
void printUserHT(gpointer key, gpointer value, gpointer user_data){
	User aux = (User)value;
	int* keyId = (int* )key;
	printf("%d %d %s %d %d %d %d\n%s\n",*keyId, getUserID(aux), 
		   getUserDisplayName(aux),
		   getUserReputacao(aux),
		   getUserNPerguntas(aux),
		   getUserNRespostas(aux),
		   getUserNPosts(aux),
		   getUserShortBio(aux));
}
*/
/* Funcao para verificar procura na UserHashT */ 
/*
void testeAcessoUserHT(TAD_community com, int id){
	int* aux = malloc(sizeof(int));
	*aux=id;
	User user = initUser();
	user = (User)g_hash_table_lookup(com->user, aux);
	if(user) printf("%d %s\n",getUserID(user),getUserDisplayName(user));
	 else printf("user not found\n");
}
*/
// Função para verificar contagem do nº posts
/*
void ver_num (gpointer key, gpointer value, gpointer user_data){
	User aux = (User)value;
	int* keyId = (int* )key;
	printf(user_data,*keyId, getUserNRespostas(aux),getUserNPerguntas(aux));
}
*/
/*
// Função para seleção da melhor resposta
void ver_melhor_resposta (gpointer key, gpointer post, gpointer user_data){
	struct Post* aux = (struct Post*)post;
	int* keyId = (int* )key;
	if (aux!=NULL && aux->type_id==1) printf(user_data,*keyId, aux->accepted_answer);
}
*/
