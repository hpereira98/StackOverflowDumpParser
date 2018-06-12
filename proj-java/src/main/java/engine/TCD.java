package engine;

import common.Pair;
import javax.xml.stream.XMLInputFactory;
import javax.xml.stream.XMLStreamException;
import javax.xml.stream.XMLStreamReader;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.time.LocalDate;
import java.time.LocalDateTime;
import java.util.*;
import java.util.stream.Collectors;



public class TCD implements li3.TADCommunity {

    private Map<Long, User> users;
    private Map<PostKey, Post> posts;
    private Map<Long, LocalDateTime> postAux;
    private Map<String, Tag> tags;


    // CONSTRUCTORS

    public TCD() {
        this.users = new HashMap<>();
        this.posts = new TreeMap<>();
        this.postAux = new HashMap<>();
        this.tags = new HashMap<>();
    }

    // PARSER USERS

    private void loadUsers(String path) throws XMLStreamException, FileNotFoundException {
        XMLInputFactory input = XMLInputFactory.newInstance();
        XMLStreamReader reader = null;

        reader = input.createXMLStreamReader(new FileInputStream(path));

        while (reader.hasNext()) {
            int eventType = reader.next();
            long id = -2;
            String name = "";
            int rep = 0;
            String bio = "";

            switch (eventType) {
                case XMLStreamReader.START_ELEMENT:
                    String qName = reader.getName().getLocalPart();
                    if (qName.equalsIgnoreCase("row")) {
                        for (int i = 0; i < reader.getAttributeCount(); i++) {
                            switch (reader.getAttributeLocalName(i)) {
                                case "Id":
                                    id = Long.parseLong(reader.getAttributeValue(i));
                                    break;
                                case "DisplayName":
                                    name = reader.getAttributeValue(i);
                                    break;
                                case "Reputation":
                                    rep = Integer.parseInt(reader.getAttributeValue(i));
                                    break;
                                case "AboutMe":
                                    bio = (reader.getAttributeValue(i));
                                    break;
                            }
                        }
                        User user = new User(id, name, 0, rep, bio, new TreeSet<>());
                        users.put(id, user);
                    }
                    break;

                    case XMLStreamReader.END_ELEMENT:
                        break;
            }
        }
        reader.close();
    }

    // PARSER POSTS

    private void loadPosts(String path) throws XMLStreamException, FileNotFoundException {
        XMLInputFactory input = XMLInputFactory.newInstance();
        XMLStreamReader reader = null;

        reader = input.createXMLStreamReader(new FileInputStream(path));

        while (reader.hasNext()) {
            int eventType = reader.next();
            long id = -2;
            String titulo = "";
            long owner_id = -2;
            int type_id = -2;
            long parent_id = -2;
            LocalDateTime data = null;
            String tags_str = "";
            int score = 0;
            int n_comments = 0;
            int n_answers = 0;

            switch (eventType) {
                case XMLStreamReader.START_ELEMENT:
                    String qName = reader.getName().getLocalPart();
                    if (qName.equalsIgnoreCase("row")) {
                        for (int i = 0; i < reader.getAttributeCount(); i++) {
                            switch (reader.getAttributeLocalName(i)) {
                                case "Id":
                                    id = Long.parseLong(reader.getAttributeValue(i));
                                    break;
                                case "Title":
                                    titulo = reader.getAttributeValue(i);
                                    break;
                                case "OwnerUserId":
                                    owner_id = Long.parseLong(reader.getAttributeValue(i));
                                    break;
                                case "PostTypeId":
                                    type_id = Integer.parseInt(reader.getAttributeValue(i));
                                    break;
                                case "ParentId":
                                    parent_id = Long.parseLong(reader.getAttributeValue(i));
                                    break;
                                case "CreationDate":
                                    data = LocalDateTime.parse(reader.getAttributeValue(i));
                                    break;
                                case "Tags":
                                    tags_str = reader.getAttributeValue(i);
                                    break;
                                case "Score":
                                    score = Integer.parseInt(reader.getAttributeValue(i));
                                    break;
                                case "CommentCount":
                                    n_comments = Integer.parseInt(reader.getAttributeValue(i));
                                    break;
                                case "AnswerCount":
                                    n_answers = Integer.parseInt(reader.getAttributeValue(i));
                                    break;
                            }
                        }
                        PostKey key = new PostKey(data, id);
                        Post post = new Post(id, titulo, owner_id, type_id, parent_id, data, tagsToList(tags_str), score, n_comments, n_answers);
                        posts.put(key, post);

                        postAux.put(id, data);

                        User user = users.get(owner_id);
                        if (user != null) {
                            user.addPost(post);
                        }
                    }
                    break;

                    case XMLStreamReader.END_ELEMENT:
                        break;
            }
        }
        reader.close();
    }

    // PARSER TAGS

    private void loadTags(String path) throws XMLStreamException, FileNotFoundException {
        XMLInputFactory input = XMLInputFactory.newInstance();
        XMLStreamReader reader = null;

        reader = input.createXMLStreamReader(new FileInputStream(path));

        while (reader.hasNext()) {
            int eventType = reader.next();
            long id = -2;
            String name = "";

            switch (eventType) {
                case XMLStreamReader.START_ELEMENT:
                    String qName = reader.getName().getLocalPart();
                    if (qName.equalsIgnoreCase("row")) {
                        for (int i = 0; i < reader.getAttributeCount(); i++) {
                            switch (reader.getAttributeLocalName(i)) {
                                case "Id":
                                    id = Long.parseLong(reader.getAttributeValue(i));
                                    break;
                                case "TagName":
                                    name = reader.getAttributeValue(i);
                                    break;
                            }
                        }
                        Tag tag = new Tag(name, id);
                        tags.put(name, tag);
                    }
                    break;

                    case XMLStreamReader.END_ELEMENT:
                        break;
            }
        }
        reader.close();
    }

    // Separa tags de uma string e passa para ArrayList

    private ArrayList<Tag> tagsToList(String str) {
        ArrayList<Tag> lista = new ArrayList<>();

        if (str != null && str.length() > 1) {
            str = str.replace("<", "").replace(">", ",");
            str = str.substring(0, str.length() - 1);
            String[] strs = str.split(",");

            for (String string : strs) {
                Tag nova = this.tags.get(string);
                if (nova != null) lista.add(nova);
            }
        }

        return lista;
    }






    /* -------------------------------- DEFINIÇÃO DAS QUERIES --------------------------------*/
    // ****************** ver das exceptions
    // Load
    public void load(String path) throws LoadDataErrorException {
        try {
            loadUsers(path + "/Users.xml");
            loadTags(path + "/Tags.xml");
            loadPosts(path + "/Posts.xml");
        } catch (XMLStreamException | FileNotFoundException e) {
            throw new LoadDataErrorException(e.getMessage());
        }
    }


    // Query 1
    public Pair<String, String> infoFromPost(long id) throws PostNotFoundException, UserNotFoundException {
        String titulo, nome;
        User user = null;
        Post post = getPost(id);

        switch (post.getTypeID()) {
            case 1:
                long owner_id = post.getOwnerID();
                user = getUser(owner_id);
                break;

            case 2:
                long parent_id = post.getParentID();
                post = getPost(parent_id);
                user = getUser(post.getOwnerID());
                break;
        }


        return new Pair<>(post.getTitulo(), user.getDisplayName());
    }

    // Query 2
    public List<Long> topMostActive(int N) {
        Set<User> users_by_nposts = new TreeSet<>((u1, u2) -> {
                                                                if (u2.getNPosts() - u1.getNPosts() == 0)
                                                                    return Long.compare(u2.getID(), u1.getID());
                                                                return Integer.compare(u2.getNPosts(), u1.getNPosts());
                                                               });

        users_by_nposts.addAll(this.users.values());

        return users_by_nposts.stream()
                              .limit(N)
                              .map(User::getID)
                              .collect(Collectors.toList());
    }


    // Query 3
/*
    public Pair<Long, Long> totalPosts(LocalDate begin, LocalDate end) {
        long n_questions = 0, n_answers = 0;
        int i;
        Set<Map.Entry<PostKey, Post>> posts_entries = this.posts.entrySet();

        Iterator<Map.Entry<PostKey, Post>> it = posts_entries.iterator();

        while(it.hasNext()){
            Map.Entry<PostKey, Post> entry = it.next();
            if(entry.getKey().getData().toLocalDate().isBefore(end)){
                Post post = entry.getValue();

                if(post.getTypeID() == 1) n_questions++;
                else n_answers++;
            }
            if(entry.getKey().getData().toLocalDate().isBefore(begin)) break;
        }

        return new Pair<Long, Long>(n_questions, n_answers);
    }*/
    // Versao stream query 3

    public Pair<Long, Long> totalPosts(LocalDate begin, LocalDate end){
        long n_questions = 0, n_answers = 0;

        Map<Integer, List<Post>> posts_by_type = this.posts.values()
                                                           .stream()
                                                           .filter(p -> isBetween(p.getData().toLocalDate(), begin, end))
                                                           .collect(Collectors.groupingBy(Post::getTypeID));

        List<Post> questions = posts_by_type.get(1);
        List<Post> answers = posts_by_type.get(2);
        if(questions != null) n_questions = questions.size();
        if(answers != null) n_answers = answers.size();

        return new Pair<>(n_questions, n_answers);
    }


    // Query 4
/*
    public List<Long> questionsWithTag(String tag_name, LocalDate begin, LocalDate end) throws TagNotFoundException{
        Tag tag = getTag(tag_name);
        List<Long> r = new ArrayList<>();
        Set<Map.Entry<PostKey, Post>> posts_entries = this.posts.entrySet();

        Iterator<Map.Entry<PostKey, Post>> it = posts_entries.iterator();

        while(it.hasNext()){
            Map.Entry<PostKey, Post> entry = it.next();
            if(entry.getKey().getData().toLocalDate().isBefore(end)){
                Map.Entry<PostKey, Post> entry = it.next();

                Post post = entry.getValue();
                ArrayList<Tag> tags = post.getTags();

                tags.stream().filter(t -> t.getID() == tag.getID())
                        .forEach(t -> r.add(t.getID()));
            }
            if(entry.getKey().getData().toLocalDate().isBefore(begin)) break;
        }

        return r;
    }
*/
    //Query 4 - versao com stream
    public List<Long> questionsWithTag(String tag_name, LocalDate begin, LocalDate end) throws TagNotFoundException {
        Tag tag = getTag(tag_name);

        return this.posts.values().stream()
                                  .filter(p -> isBetween(p.getData().toLocalDate(), begin, end) && p.getTags().contains(tag) )
                                  .map(Post::getID)
                                  .collect(Collectors.toList());
    }


    // Query 5
    public Pair<String, List<Long>> getUserInfo(long id) throws UserNotFoundException{
        User user = getUser(id);

        // estes posts já vão estar por data nao é, Pedro? acho que sugeriste isso
        List<Long> ids = user.getUserPosts().stream()
                                            .limit(10)
                                            .map(Post::getID)
                                            .collect(Collectors.toList());

        return new Pair<>(user.getShortBio(), ids);
    }

    // Query 6
    public List<Long> mostVotedAnswers(int N, LocalDate begin, LocalDate end) {
        Set<Post> posts_by_votes = new TreeSet<>((p1, p2) -> {
                                                                if (p2.getScore() == p1.getScore())
                                                                     return Long.compare(p2.getID(), p1.getID());
                                                                return p2.getScore() - p1.getScore();
                                                             });

        this.posts.values().stream()
                           .filter(p -> p.getTypeID() == 2 && isBetween(p.getData().toLocalDate(), begin, end))
                           .forEach(p -> posts_by_votes.add(p));

        return posts_by_votes.stream()
                             .limit(N)
                             .map(Post::getID)
                             .collect(Collectors.toList());
    }

    // Query 7
    public List<Long> mostAnsweredQuestions(int N, LocalDate begin, LocalDate end) {
        Set<Post> posts_by_n_answers = new TreeSet<>((p1, p2) -> {
                                                                    if (p2.getNAnswers() == p1.getNAnswers())
                                                                        return Long.compare(p2.getID(), p1.getID());
                                                                    return p2.getNAnswers() - p1.getNAnswers();
                                                                  });

        this.posts.values().stream()
                           .filter(p -> p.getTypeID() == 1 && isBetween(p.getData().toLocalDate(), begin, end))
                           .forEach(p -> posts_by_n_answers.add(p));

        return posts_by_n_answers.stream()
                                 .limit(N)
                                 .map(Post::getID)
                                 .collect(Collectors.toList());
    }

    // Query 8
    public List<Long> containsWord(int N, String word) {
        return this.posts.values().stream()
                                  .filter(t -> t.getTypeID() == 1 && t.getTitulo().contains(word))
                                  .limit(N)
                                  .map(Post::getID)
                                  .collect(Collectors.toList());
    }

    // Query 9
    public List<Long> bothParticipated(int N, long id1, long id2) throws UserNotFoundException {
        User user1 = getUser(id1);
        User user2 = getUser(id2);

        List<Post> user1_posts = user1.getUserPosts();
        List<Post> user2_posts = user2.getUserPosts();

        swapAnswerToQuestion(user1_posts);
        swapAnswerToQuestion(user2_posts);

        user1_posts.retainAll(user2_posts);

        return user1_posts.stream()
                          .limit(N)
                          .map(Post::getID)
                          .collect(Collectors.toList());
    }

    // Funcao para trocar as respostas pela respetiva pergunta
    private void swapAnswerToQuestion(Collection<Post> posts){
        List<Post> respostas = posts.stream().filter(p -> p.getTypeID()==2)
                                             .collect(Collectors.toList());

        posts.removeAll(respostas); // remover todas as respostas do set

        for(Post r : respostas){ // procurar a pergunta para a qual a resposta foi dada e colocar no set
            Long parent_id = r.getParentID();
            LocalDateTime data = this.postAux.get(parent_id);
            if(data != null){
                PostKey aux = new PostKey(data, parent_id);
                posts.add(this.posts.get(aux));
            }
        }
    }

    // Query 10
    public long betterAnswer(long id) throws PostNotFoundException, QuestionWithoutAnswersException{
        Post post = getPost(id); // apenas serve para verificar se o post existe ou nao
        Set<Post> answers_by_score = new TreeSet<>((p1,p2) -> Double.compare(answer_score(p2), answer_score(p1)));

        this.posts.values().stream()
                           .filter(p -> p.getTypeID() == 2 && p.getParentID() == id)
                           .forEach(p -> answers_by_score.add(p));

        if(answers_by_score.size() == 0)
            throw new QuestionWithoutAnswersException(Long.toString(id));

        return ((TreeSet<Post>) answers_by_score).first().getID();
    }

    // Funcao para calcular o score de um post segundo formula presente no enunciado
    private double answer_score(Post post){
         double owner_rep = this.users.get(post.getOwnerID()).getRep();

         return post.getScore() * 0.65 +
                owner_rep * 0.25 +
                post.getNComments() * 0.1;
    }

    // Query 11
    public List<Long> mostUsedBestRep(int N, LocalDate begin, LocalDate end) {
        int i=0;
        Set<User> users_by_rep = new TreeSet<>((u1, u2) -> {
                                                            if (u2.getRep() - u1.getRep() == 0)
                                                                return Long.compare(u2.getID(), u1.getID());
                                                            return Integer.compare(u2.getRep(), u1.getRep());
                                                            });

        users_by_rep.addAll(this.users.values());

        List<Tag> tags = new ArrayList<>();

        Iterator<User> it = users_by_rep.iterator();
        User user;
        while(i<N && it.hasNext()){
            user = it.next();
            user.getUserPosts().stream()
                               .filter(p -> p.getTypeID()==1 && isBetween(p.getData().toLocalDate(), begin, end))
                               .forEach(p -> tags.addAll(p.getTags()));
            i++;
        }
        // neste momentos temos uma lista com todas as tags a serem contadas (com repeticoes)
        // Map com id - num_ocur
        Map<Long, Long> tags_ocur = tags.stream()
                                        .collect(Collectors.groupingBy(Tag::getID, Collectors.counting()));

        return tags_ocur.entrySet().stream()
                                   .sorted(Map.Entry.<Long,Long>comparingByValue().reversed())
                                   .limit(N)
                                   .map(Map.Entry::getKey)
                                   .collect(Collectors.toList());
    }

    public void clear() {

    }


    // Função para ver se uma data pertence a um dado intervalo de datas

    private static boolean isBetween(LocalDate to_check, LocalDate begin, LocalDate end) {
        return (to_check.isAfter(begin) && to_check.isBefore(end)) || to_check.equals(begin) || to_check.equals(end);
    }

    private Post getPost(long id) throws PostNotFoundException {
        LocalDateTime data = postAux.get(id);

        if (data == null)
            throw new PostNotFoundException(Long.toString(id));

        PostKey key = new PostKey(data, id);

        return posts.get(key);
    }

    private User getUser(long id) throws UserNotFoundException {
        User user = this.users.get(id);

        if(user == null)
            throw new UserNotFoundException(Long.toString(id));

        return user;
    }

    private Tag getTag(String tag_name) throws TagNotFoundException {
        Tag tag = this.tags.get(tag_name);

        if(tag == null)
            throw new TagNotFoundException(tag_name);

        return tag;
    }

}