#include "structs.h"

struct user{
	int id; // user id
	char* display_name; // username
	int n_perguntas; // número de perguntas
	int n_respostas; // número de respostas
	int n_posts; // número total de posts
	int reputacao; // reputacao
	//Date data_posts[];
	//Date data_respostas[];
	//char* títulos[];
	char* short_bio; // descrição do user
	GArray* userPosts;

};

struct post{
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
	// int accepted_answer; // testar q10 - POR EM COMENTARIO QUANDO NAO FOR NECESSARIO
};

struct tag{
	char* name;
	int id;
	int ocorrencias;
};

struct TCD_community{
	GHashTable* user;
	GHashTable* post;
	GHashTable* tags;	
};
// QUERIES

TAD_community init(){
	struct TCD_community* new = malloc(sizeof(struct TCD_community));

  	GHashTable* new_user_hash = g_hash_table_new(g_int_hash, g_int_equal);
  	GHashTable* new_post_hash = g_hash_table_new(g_int_hash, g_int_equal);
	GHashTable* new_tags_hash = g_hash_table_new(g_int_hash, g_int_equal);
  	
  	new->user = new_user_hash;
  	new->post = new_post_hash;
  	new->tags = new_tags_hash;

  	return new;
}


TAD_community load(TAD_community com, char* dump_path){
	load_aux(com->user,com->post,com->tags,dump_path);
	return com;
}  

// query 1
STR_pair info_from_post(TAD_community com, long id){
	return info_from_post_aux(com->post,com->user,id);
}  

// query 2
LONG_list top_most_active(TAD_community com, int N){
	return top_most_active_aux(com->user,N);
}

// query 3
LONG_pair total_posts(TAD_community com, Date begin, Date end){
	return total_posts_aux(com->post,begin,end);
}

// query 4
LONG_list questions_with_tag(TAD_community com, char* tag, Date begin, Date end){
	return questions_with_tag_aux(com->post,tag,begin,end);
}

// query 5
USER get_user_info(TAD_community com, long id){
	return get_user_info_aux(com->user,id);
}

// query 6
LONG_list most_voted_answers(TAD_community com, int N, Date begin, Date end){
	return most_voted_answers_aux(com->post,N,begin,end);
}

// query 7
LONG_list most_answered_questions(TAD_community com, int N, Date begin, Date end){
	return most_answered_questions_aux();
}

// query 8
LONG_list contains_word(TAD_community com, char* word, int N){
	return contains_word_aux(com->post,word,N);
}

// query 9
LONG_list both_participated(TAD_community com, long id1, long id2, int N){
	return both_participated_aux(com->user, com->post,id1,id2,N);
}

// query 10
long better_answer(TAD_community com, long id){
	return better_answer_aux(com->post,id);
}

// query 11
LONG_list most_used_best_rep(TAD_community com, int N, Date begin, Date end){
	return most_used_best_rep_aux(com->user,com->tags,N,begin,end);
}

// USERS

// Inits

User initUser(){
	User new = malloc(sizeof(struct user));
	return new;
}

void initUserPosts(User user){
	user->userPosts = g_array_new (FALSE,TRUE,sizeof(struct post*));
}


// Getters

int getUserID(User user){
	return user->id;
}

char* getUserDisplayName(User user){
	return mystrdup(user->display_name);
}

int getUserReputacao(User user){
	return user->reputacao;
}

int getUserNPerguntas(User user){
	return user->n_perguntas;
}

int getUserNRespostas(User user){
	return user->n_respostas;
}

int getUserNPosts(User user){
	return user->n_posts;
}

char* getUserShortBio(User user){
	return mystrdup(user->short_bio);
}

GArray* getUserPosts(User user){ // copiar todos para um novo?
	return user->userPosts;
}

GArray* getClonedUserPosts(User user){
	int size = (user->userPosts)->len;
	Post aux;
	GArray * new = g_array_new(FALSE,TRUE,sizeof(struct post*));

	for(int i=0; i<size;i++){
		aux = g_array_index(user->userPosts,Post,i);
		g_array_append_val(new,aux);
	}

	return new;
}


// Setters

void setUserID(User user, int id){
	user->id = id;
}

void setUserDisplayName(User user, char* display_name){
	user->display_name = mystrdup(display_name);
}

void setUserReputacao(User user, int reputacao){
	user->reputacao = reputacao;
}

void setUserNPerguntas(User user, int n_perguntas){
	user->n_perguntas = n_perguntas;
}

void setUserNRespostas(User user,int n_respostas){
	user->n_respostas = n_respostas;
}

void setUserNPosts(User user, int n_posts){
	user->n_posts = n_posts;
}

void setUserShortBio(User user, char* short_bio){
	 user->short_bio = mystrdup(short_bio);
}


// Cleaner

void freeUser (User user) {
	free(user->display_name);
	free(user->short_bio);
	g_array_free(user->userPosts,TRUE);
	free(user);
}

// POSTS

// Init

Post initPost(){
	Post new = malloc(sizeof(struct post));
	return new;
}

// Getters

int getPostID(Post post){
	return post->id;
}

char* getPostTitle(Post post){
	return mystrdup(post->titulo);
}

int getPostOwnerID(Post post){
	if(post->owner_id != -2) return post->owner_id;
	else return post->id;
}

char* getPostOwnerDisplayName(Post post){
	return mystrdup(post->owner_display_name);
}

int getPostOwnerRep(Post post){
	return post->owner_rep;
}

int getPostTypeID(Post post){
	return post->type_id;
}

int getPostParentID(Post post){
	return post->parent_id;
}

Date getPostDate(Post post){
	int dia, mes, ano;

	dia = get_day(post->data);
	mes = get_month(post->data);
	ano = get_year(post->data);

	return createDate(dia, mes, ano);
}

char* getPostTags(Post post){
	return mystrdup(post->tags);
}

int getPostScore(Post post){
	return post->score;
}

int getPostNComments(Post post){
	return post->n_comments;
}

int getPostNUpVotes(Post post){
	return post->n_upvotes;
}

int getPostNDownVotes(Post post){
	return post->n_downvotes;
}

int getPostNRespostas(Post post){
	return post->n_respostas;
}

// Setters

void setPostID(Post post, int id){
	post->id = id;
}

void setPostTitle(Post post, char* titulo){
	post->titulo = mystrdup(titulo); 
}

void setPostOwnerID(Post post, int owner_id){
	post->owner_id = owner_id; 		
}

void setPostOwnerDisplayName(Post post, char* owner_display_name){
	 post->owner_display_name = mystrdup(owner_display_name);
}

void setPostOwnerRep(Post post, int owner_rep){
	post->owner_rep = owner_rep; 
}

void setPostTypeID(Post post, int type_id){
	post->type_id = type_id;
}

void setPostParentID(Post post, int parent_id){
	post->parent_id = parent_id; 
}

void setPostDate(Post post, Date data){
	int dia, mes, ano;

	dia = get_day(data);
	mes = get_month(data);
	ano = get_year(data);

	post->data = createDate(dia, mes, ano);
}

void setPostTags(Post post, char* tags){
	post->tags = mystrdup(tags); 
}

void setPostScore(Post post, int score){
	post->score = score;
}

void setPostNComments(Post post, int n_comments){
	post->n_comments =  n_comments;
}

void setPostNDownVotes(Post post, int n_downvotes){
	post->n_downvotes = n_downvotes; 
}

void setPostNUpVotes(Post post, int n_upvotes){
	post->n_upvotes = n_upvotes; 
}

void setPostNRespostas(Post post, int n_respostas){
	post->n_respostas = n_respostas;
}

// Cleaner

void freePost (Post post) {
	free(post->titulo);
	free(post->owner_display_name);
	free_date(post->data);
	free(post->tags);
	free(post);	
}



// Tags

// Init 

Tag initTag(){
	Tag new = malloc(sizeof(struct tag));
	return new;
}

Tag createTag(char* name, int id, int ocorrencias){
	Tag new = initTag();

	setTagName(new, name);
	setTagID(new, id);
	setTagOcor(new, ocorrencias);

	return new;
}

// Getters

char* getTagName(Tag tag){
	return mystrdup(tag->name);
}

int getTagID(Tag tag){
	return tag->id;
}

int getTagOcor(Tag tag){
	return tag->ocorrencias;
}

// Setters 

void setTagName(Tag tag, char* name){
	tag->name = mystrdup(name); 
}

void setTagID(Tag tag, int id){
	tag->id = id;
}

void setTagOcor(Tag tag, int ocor){
	tag->ocorrencias = ocor;
}

// Cleaner

void freeTags (Tag tag) {
	free(tag->name);
	free(tag);
} 
