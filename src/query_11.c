
void ordenaUsers(gpointer key_pointer, gpointer user_pointer, gpointer info){
	int* ids = ((int**)info)[0];
	int* rep = ((int**)info)[1];
	int *ocupados = ((int**)info)[2];
	int size = ((int*)info)[3];
	struct User* user = (struct User*)user_pointer;

	if( (*ocupados != size) || (*ocupados == size && user->rep > rep[size-1]) ){
		pos = insert(rep, user->rep, size);
		insereId(ids, user->id, pos, size);
		if(*ocupados < size) (*ocupados)++;
	}
}


struct Tag{
	char* tag;
	int ocorrencias;
	int id; // se ==-1 procurar na hash de tags, se !=-1 é porque já foi procurada e já se sabe o id (ideia de implementação)
};


LONG_list most_used_best_rep(TAD_community com, int N, Date begin, Date end){
	int* top_users_ids = malloc(sizeof(int)*N);
	int* rep_users = malloc(sizeof(int)*N);
	
	int *ocupados = 0;
	void* info[4] = {top_users_ids, rep_users, ocupados, &N};

	// Filtra os melhores N users por reputação
	g_hash_table_foreach(com->users, ordenaUsers, info);


	GArray* tags = g_array_new(FALSE, TRUE, (guint)sizeof(struct Tag));

	// quando o post for valido (entre as datas e de um dos top_users): contar todas as tags pois são do tipo "<tag><tag>..." - função auxiliar

}