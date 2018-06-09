

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




// QUERY 6


