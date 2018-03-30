#include <query_9.h>

// QUERY 9

void dateInsertionSort (int id, Date data,int *ids,Date *datas, int* ocupados,int size) {
	
	int pos;
	if( (*ocupados < size) || ( (*ocupados == size) && ( comparaDatas(data,datas[(size)-1])==1 ) ) ){

		pos = insertDate(datas,data,size);
		insereId(ids,id,pos,size);
			
		if(*ocupados < (size)) (*ocupados)++;	

	}
}

void get_question_ids (struct User* user, int *ids, Date *datas,int* ocupados,int size) {
	if (user!=NULL) {
		for (int i=0;i<(user->n_posts);i++) {
			struct Post* post = g_array_index(user->userPosts,struct Post*,i);
			if (post!=NULL) {
			
				int type = post->type_id;
				int id = post->id;
				Date data = post->data;
				if (type==1) dateInsertionSort(id,data,ids,datas,ocupados,size);
				else if (type==2) dateInsertionSort(post->parent_id,data,ids,datas,ocupados,size);
			}
		}	
	}
}

LONG_list both_participated(TAD_community com, long id1, long id2, int N){
	
	struct User* user1 = g_hash_table_lookup(com->user,&id1); 
	struct User* user2 = g_hash_table_lookup(com->user,&id2);

	int size1 = user1->n_posts;
	int size2 = user2->n_posts;

	int *ids1 = malloc(sizeof(int)*size1);
	Date *datas1 = malloc(sizeof(int)*size2);

	int *ids2 = malloc(sizeof(int)*size1);
	Date *datas2 = malloc(sizeof(int)*size2);

	for (int i=0;i<size1;i++) {
		datas1[i]=createDate(0,0,0);
		ids1[i]=-2;
	}

	for (int j=0;j<size2;j++) {
		datas2[j]=createDate(0,0,0);
		ids2[j]=-2;
	}

	int* ocupados=malloc(sizeof(int));
	*ocupados=0; // vai até N no máximo
	//debugging
	if (user1==NULL) printf("user 1 nao existe\n");
	//debugging
	if (user2==NULL) printf("user 2 nao existe\n");
	if (user1!=NULL && user2!=NULL) {
		get_question_ids(user1,ids1,datas1,ocupados,size1);
		*ocupados=0;
		get_question_ids(user2,ids2,datas2,ocupados,size2);
		*ocupados=0;
	}
	
	LONG_list r = create_list(N); // ou até ocupados -> FALAR COM O PROF
	for (int i=0;i<size1;i++)
		for (int j=0;j<size2 && *ocupados<N ;j++)
			if (ids1[i]!=-2 && ids2[j]!=-2 && ids1[i]==ids2[j]) {
				printf("id: %d, data: %d-%d-%d\n",ids1[i],get_day(datas1[i]),get_month(datas1[i]),get_year(datas1[i]));
				set_list(r,*ocupados,(long)ids1[i]);
				(*ocupados)++;
			}
	
	return r;

}
