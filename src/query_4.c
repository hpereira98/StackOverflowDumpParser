#include <query_4.h>

gboolean adicionaComTag(gpointer key_pointer, gpointer post_pointer, gpointer info){ // info = {tree, tag, inicio, fim}
	Post post = (Post) post_pointer;
	Date begin = ((Date*)(info))[2];
	Date end = ((Date*)(info))[3]; 
	GTree* tree = ((GTree**)(info))[0]; 
	Date post_date = getPostDate(post);

	char* tag = envolveTag(((char**)info)[1]);

	if(comparaDatas(begin, end, post_date) == 0){ 
		char* post_tags = getPostTags(post);
		if(post_tags != NULL && strstr(post_tags, tag) != NULL){
			long postID = getPostID(post);
			g_tree_insert(tree, (gpointer)post_date, (gpointer)(&postID));			
		}
	}

	else if(comparaDatas(begin, end, post_date) == -1) return TRUE;

	return FALSE;
}


void addToLongList(gpointer key_pointer, gpointer id_pointer, gpointer info){ // info = {lista, i}
	long* id = (long*) id_pointer;
	int* i = ((int**)(info))[1]; 
	LONG_list lista = ((LONG_list*)(info))[0]; 

	set_list(lista, *i, *id);
	(*i)--;
}


LONG_list questions_with_tag_aux(GTree* com_post, char* tag, Date begin, Date end){ // PERGUNTAR AO STOR O TIPO DA TAG: "<TAG>" OU "TAG" !!!!!!!!!!!!!!!!!!!!!!!!!!!!

	GTree* tree = g_tree_new((GCompareFunc)comparaDatas);
	void* info[4] = {(void*)tree, (void*)tag, (void*)begin, (void*)end};

	// Constroi a tree com os posts com a tag e dentro da data
	g_tree_foreach(com_post, (GTraverseFunc)adicionaComTag, (gpointer)info);

	gint tam = g_tree_nnodes(tree); 

	LONG_list r = create_list(tam);

	int* i = malloc(sizeof(int));
	*i = tam-1;
	void* lista[2] = {r, i};

	// Constroi a lista resultado (r)
	g_tree_foreach(tree, (GTraverseFunc)addToLongList, (gpointer)lista);

	return r;
}
