#include <query_9.h>
/*
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
				
					if (post2!=NULL && !(post1->type_id==1 && post2->type_id==1)) {
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

}*/