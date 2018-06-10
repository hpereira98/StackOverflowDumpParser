
/*
// QUERY 2

public List<Long> top_most_active(int n){
	Set<User> users_by_nposts = new TreeSet<>((u1, u2) -> { if(u2.getNPosts() - u1.getNPosts() == 0)
																return u2.getID() - u1.getID();
															return u2.getNPosts() - u1.getNPosts();
														  });

	this.users.values().forEach(u -> users_by_nposts.add(u));

	return users_by_nposts.stream().limit(n).
									mapToLong(User :: getID).
									collect(Collectors.toList());
}




// QUERY 3

public Pair<Long,Long> totalPosts(LocalDate begin, LocalDate end){
	long n_questions = 0, n_answers = 0;

	Set<MapEntry<LocalDate, Post>> posts_entries = this.posts.entrySet();

	// Avança até à data do fim
	for(int i = 0; i < posts_entries.size(); i++){
		if(!posts_key.getKey(i).getData().isAfter(end)) break;
	}

	// Percorre as datas até ser antes do inicio
	for(i = i; i < posts_entries.size(); i++){
		if(posts_key.get(i).getData().isBefore(begin)) break;

		Post post = posts_entries.getValue(i);

		if(post.getTypeID() == 1) n_questions++;
		else n_answers++;

	}

	return new Pair<Long, Long>(n_questions, n_answers);
}



// QUERY 4

public List<Long> questionsWithTag(String tag_name, LocalDate begin, LocalDate end){
	Tag tag = getTag(tag_name);
	List<Long> r = new ArrayList<>();
	
	Set<MapEntry<LocalDate, Post>> posts_entries = this.posts.entrySet();

	// Avança até à data do fim
	for(int i = 0; i < posts_entries.size(); i++){
		if(!posts_key.getKey(i).getData().isAfter(end)) break;
	}

	// Percorre as datas até ser antes do inicio
	for(i = i; i < posts_entries.size(); i++){
		if(posts_key.get(i).getData().isBefore(begin)) in_date = 0;

		Post post = posts_entries.getValue(i);
		ArrayList<Tag> tags = post.getTags();

		tags.stream().filter(t -> t.getID() == tag.getID())
					 .forEach(t -> r.add(t.getID()));
	}

	return r;	
}



// QUERY 5

public Pair<String, List<Long>> getUserInfo(long id){

	User user = this.users.get(id); // != null
	ArrayList<Long> user_posts = user.getUserPosts();

	// estes posts já vão estar por data nao é, Pedro? acho que sugeriste isso
	List<Long> ids = user_posts.stream().limit(10)
										.collect(Collectors.toList());

	return new Pair<String, List<Long>>(user.getShortBio(), ids);
}


*/

// QUERY 6

public List<Long> mostVotedAnswers(int N, LocalDate begin, LocalDate end) {
    Set<Post> setAux = new TreeSet<>((t1,t2)-> {if (t2.getScore()==t1.getScore()) t2.getID()-t1.getID();
                                                else t2.getScore() - t1.getScore();})

    this.posts.values().stream()
        .filter((t) -> t.getTypeID()==2 && t.getData().isAfter(begin) && t.getData().isBefore(end))
        .forEach(t -> setAux.add(t.clone()));

    return setAux.stream().limit(N).mapToLong(Post :: getID).collect(Collectors.toList());
}

// QUERY 7

public List<Long> mostAnsweredQuestions(int N, LocalDate begin, LocalDate end){
    Set<Post> setAux = new TreeSet<>((t1,t2)-> {if (t2.getgetNAnswers()==t1.getgetNAnswers()) t2.getID()-t1.getID();
                                                else t2.getNAnswers() - t1.getNAnswers();})

    this.post.values().stream()
        .filter((t)->t.getTypeID()==1 && t.getData().isAfter(begin) && t.getData().isBefore(end))
        .forEach(t -> setAux.add(t.clone()));

    return setAux.stream().limit(N).mapToLong(Post :: getID).collect(Collectors.toList());
}

// QUERY 8

public List<Long> containsWord(int N, String word) {
    // os posts já estao ordenados por data? Fazer clone?
    return this.posts.values().stream()
            .filter(t -> t.getTypeID()==1 && t.getTitulo().contains(word))
            .limit(N)
            .mapToLong(Post :: getID)
            .collect(Collectors.toList());
}

// QUERY 9

public List<Long> bothParticipated(int N, long id1, long id2) {
    Set<Post> userPosts1 = new TreeSet<>((d1,d2) -> d2.getData().compareTo(d1.getData()));
    this.users.get(id1).getUserPosts().stream()
        .map(p -> {if (p.getTypeID()==2) p = this.posts.get(p.getParentID());})
        .forEach(p -> userPosts1.add(p.clone()));

    Set<Post> userPosts2 = new TreeSet<>((d1,d2) -> d2.getData().compareTo(d1.getData()));
    this.users.get(id2).getUserPosts().stream()
        .map(p -> {if (p.getTypeID()==2) p = this.posts.get(p.getParentID());})
        .forEach(p -> userPosts2.add(p.clone()));

    return userPosts1.stream().filter(f -> userPosts2.contains(f)).limit(N)
            .mapToLong(Post :: getID).collect(Collectors.toList());
}
