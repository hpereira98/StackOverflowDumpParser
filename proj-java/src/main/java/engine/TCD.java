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


    /**
     * Construtor default da classe TCD
     */
    public TCD() {
        this.users = new HashMap<>();
        this.posts = new TreeMap<>();
        this.postAux = new HashMap<>();
        this.tags = new HashMap<>();
    }

    /* -------------------------------- DEFINIÇÃO DAS QUERIES -------------------------------- */


    // Load

    /**
     * Método que carrega todos os dados para a estrutura
     * @param path diretoria do dump
     * @throws LoadDataErrorException
     */
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

    /**
     * Método que, dado o ID de um Post, devolve um Par com o título da pergunta correspondente ao Post e o nome do User.
     * @param id
     * @return
     * @throws PostNotFoundException
     * @throws UserNotFoundException
     */
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

    /**
     * Método que lista os utilizadores mais ativos da comunidade.
     * @param N
     * @return
     */
    public List<Long> topMostActive(int N) {
        Set<User> users_by_nposts = new TreeSet<>((u1, u2) -> {
                                                                if (u2.getNPosts() - u1.getNPosts() == 0)
                                                                    return Long.compare(u1.getID(), u2.getID());
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

    // Versao stream

    /**
     * Método que, dado um intervalo de tempo, conta quantas perguntas e quantas respostas foram feitas durante o mesmo.
     * @param begin
     * @param end
     * @return
     */
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

    //versao com stream

    /**
     * Método que, dado um intervalo de tempo e uma tag, retorna uma LONG_list contendo os IDs de perguntas, feitas no intervalo, que contenham essa tag.
     * @param tag_name
     * @param begin
     * @param end
     * @return
     * @throws TagNotFoundException
     */
    public List<Long> questionsWithTag(String tag_name, LocalDate begin, LocalDate end) throws TagNotFoundException {
        Tag tag = getTag(tag_name);

        return this.posts.values().stream()
                                  .filter(p -> isBetween(p.getData().toLocalDate(), begin, end) && p.getTags().contains(tag) )
                                  .map(Post::getID)
                                  .collect(Collectors.toList());
    }


    // Query 5

    /**
     * Método que dado um ID retorna informação sobre o correspondente User.
     * @param id
     * @return
     * @throws UserNotFoundException
     */
    public Pair<String, List<Long>> getUserInfo(long id) throws UserNotFoundException{
        User user = getUser(id);

        List<Long> ids = user.getUserPosts().stream()
                                            .limit(10)
                                            .map(Post::getID)
                                            .collect(Collectors.toList());

        return new Pair<>(user.getShortBio(), ids);
    }


    // Query 6

    /**
     * Método que, dado um inteiro e um intervalo de datas, retorna uma lista com IDs das respostas com mais votos.
     * @param N
     * @param begin
     * @param end
     * @return
     */
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

    /**
     * Método que, dado um inteiro e um intervalo de datas, retorna uma lista com IDs das perguntas com mais respostas.
     * @param N
     * @param begin
     * @param end
     * @return
     */
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

    /**
     * Método que, dada uma palavra e um inteiro N, retorna uma lista com, no máximo N, IDs de perguntas cujos títulos contenham a palavra dada.
     * @param N
     * @param word
     * @return
     */
    public List<Long> containsWord(int N, String word) {
        return this.posts.values().stream()
                                  .filter(t -> t.getTypeID() == 1 && t.getTitulo().contains(word))
                                  .limit(N)
                                  .map(Post::getID)
                                  .collect(Collectors.toList());
    }


    // Query 9

    /**
     * Método que lista, no máximo, os N IDs dos Posts em que dois utilizadores participam.
     * @param N
     * @param id1
     * @param id2
     * @return
     * @throws UserNotFoundException
     */
    public List<Long> bothParticipated(int N, long id1, long id2) throws UserNotFoundException {
        User user1 = getUser(id1);
        User user2 = getUser(id2);

        Set<Post> user1_posts = user1.getUserPosts();
        Set<Post> user2_posts = user2.getUserPosts();

        swapAnswerToQuestion(user1_posts);
        swapAnswerToQuestion(user2_posts);

        user1_posts.retainAll(user2_posts);

        return user1_posts.stream()
                          .limit(N)
                          .map(Post::getID)
                          .collect(Collectors.toList());
    }


    // Query 10

    /**
     * Método que, dado um ID de uma pergunta, devolve o ID da melhor resposta.
     * @param id
     * @return
     * @throws PostNotFoundException
     * @throws QuestionWithoutAnswersException
     */
    public long betterAnswer(long id) throws PostNotFoundException, QuestionWithoutAnswersException{
        Post post = getPost(id); // apenas serve para verificar se o post existe ou nao, se nao existir lança excepção
        Set<Post> answers_by_score = new TreeSet<>((p1,p2) -> Double.compare(answer_score(p2), answer_score(p1)));

        this.posts.values().stream()
                           .filter(p -> p.getTypeID() == 2 && p.getParentID() == id)
                           .forEach(p -> answers_by_score.add(p));

        if(answers_by_score.size() == 0)
            throw new QuestionWithoutAnswersException(Long.toString(id));

        return ((TreeSet<Post>) answers_by_score).first().getID();
    }




    // Query 11

    /**
     * Método que lista as tags mais usadas, pelos N utilizadores com melhor reputação, durante um dado intervalo de tempo.
     * @param N
     * @param begin
     * @param end
     * @return
     */
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

        Map<Long, Long> tags_ocur = tags.stream()
                                        .collect(Collectors.groupingBy(Tag::getID, Collectors.counting()));

        Comparator<Map.Entry<Long,Long>> comp = (e1,e2) -> {
                                                            if(e1.getValue() == e2.getValue())
                                                                return Long.compare(e1.getKey(), e2.getKey());
                                                            return Long.compare(e2.getValue(), e1.getValue());
                                                            };

        return tags_ocur.entrySet().stream()
                                   .sorted(comp)
                                   .limit(N)
                                   .map(Map.Entry::getKey)
                                   .collect(Collectors.toList());
    }

    public void clear() {
        this.users.clear();
        this.posts.clear();
        this.postAux.clear();
        this.tags.clear();
        this.users = null;
        this.posts = null;
        this.postAux = null;
        this.tags = null;
    }

    /* -------------------------------- Funções e métodos auxiliares às queries -------------------------------- */


    /**
     * Método que verifica se uma data pertence a um dado intervalo (inclusive)
     * @param to_check
     * @param begin
     * @param end
     * @return
     */
    private static boolean isBetween(LocalDate to_check, LocalDate begin, LocalDate end) {
        return (to_check.isAfter(begin) && to_check.isBefore(end)) || to_check.equals(begin) || to_check.equals(end);
    }

    /**
     * Método que, dado um id, retorna o Post correspondente
     * @param id
     * @return
     * @throws PostNotFoundException
     */
    private Post getPost(long id) throws PostNotFoundException {
        LocalDateTime data = postAux.get(id);

        if (data == null)
            throw new PostNotFoundException(Long.toString(id));

        PostKey key = new PostKey(data, id);

        return posts.get(key);
    }


    /**
     * Método que, dado um id, retorna o User correspondente
     * @param id
     * @return
     * @throws UserNotFoundException
     */
    private User getUser(long id) throws UserNotFoundException {
        User user = this.users.get(id);

        if(user == null)
            throw new UserNotFoundException(Long.toString(id));

        return user;
    }


    /**
     * Método que, dado o nome duma Tag, retorna a Tag correspondente
     * @param tag_name
     * @return
     * @throws TagNotFoundException
     */
    private Tag getTag(String tag_name) throws TagNotFoundException {
        Tag tag = this.tags.get(tag_name);

        if(tag == null)
            throw new TagNotFoundException(tag_name);

        return tag;
    }



    // Auxiliares do parser

    /**
     * Método que carrega para a estrutura os users
     * @param path diretoria do dump
     * @throws XMLStreamException
     * @throws FileNotFoundException
     */
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


    /**
     * Método que carrega para a estrutura os posts
     * @param path diretoria do dump
     * @throws XMLStreamException
     * @throws FileNotFoundException
     */
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


    /**
     * Método que carrega para a estrutura as tags
     * @param path diretoria do dump
     * @throws XMLStreamException
     * @throws FileNotFoundException
     */
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


    /**
     * Método que separa as tags duma string para List de string
     * @param str string com todas as tags
     * @return lista com as tags separadas
     */
    private List<Tag> tagsToList(String str) {
       List<Tag> lista = new ArrayList<>();

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

    // Auxiliar query 9

    /**
     * Método para trocar as respostas pela respetiva pergunta
     * @param posts
     */
    private void swapAnswerToQuestion(Collection<Post> posts){
        List<Post> respostas = posts.stream().filter(p -> p.getTypeID()==2)
                .collect(Collectors.toList());

        posts.removeAll(respostas);

        for(Post r : respostas){
            Long parent_id = r.getParentID();
            LocalDateTime data = this.postAux.get(parent_id);
            if(data != null){
                PostKey aux = new PostKey(data, parent_id);
                posts.add(this.posts.get(aux));
            }
        }
    }

    // Auxiliar query 10

    /**
     * Método para calcular o score de um post
     * @param post
     * @return
     */
    private double answer_score(Post post){
        double owner_rep = this.users.get(post.getOwnerID()).getRep();

        return post.getScore() * 0.65 +
                owner_rep * 0.25 +
                post.getNComments() * 0.1;
    }

}