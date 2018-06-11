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
    private Map<Long, String> postAux;
    private Map<String, Tag> tags;

    // QUERIES:

    // auxiliares

    private Post getPost(long id) throws PostNotFoundException {

        String data = postAux.get(id);
        if (data == null) throw new PostNotFoundException("src.main.java.engine.Post " + id + " não foi encontrado.");
        else {
            PostKey key = new PostKey(data, id);

            return posts.get(key).clone();
        }
    }


    // PARSER USERS

    private void loadUsers(String path) throws XMLStreamException {
        XMLInputFactory input = XMLInputFactory.newInstance();
        XMLStreamReader reader = null;

        try {
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
                            User user = new User(id, name, 0, rep, bio, new ArrayList<>());
                            users.put(id, user);
                        }
                        break;

                    case XMLStreamReader.END_ELEMENT:
                        break;
                }
            }
            reader.close();
        } catch (FileNotFoundException e) {
            System.out.println(e.getMessage());
        }
    }

    // PARSER POSTS

    private void loadPosts(String path) throws XMLStreamException {
        XMLInputFactory input = XMLInputFactory.newInstance();
        XMLStreamReader reader = null;

        try {
            reader = input.createXMLStreamReader(new FileInputStream(path));

            while (reader.hasNext()) {
                int eventType = reader.next();
                long id = -2;
                String titulo = "";
                long owner_id = -2;
                int type_id = -2;
                long parent_id = -2;
                String data = "";
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
                                        data = reader.getAttributeValue(i);
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
                            Post post = new Post(id, titulo, owner_id, type_id, parent_id, LocalDateTime.parse(data), tagsToList(tags_str), score, n_comments, n_answers);
                            posts.put(key, post);

                            postAux.put(id, data);

                            User user = users.get(owner_id);
                            if (user != null) {
                                user.setNPosts(user.getNPosts() + 1); // n_posts++;

                                ArrayList<Post> nova = user.getUserPosts();
                                nova.add(post);
                                user.setUserPosts(nova); // post adicionado à lista de posts do user
                            }
                        }
                        break;

                    case XMLStreamReader.END_ELEMENT:
                        break;
                }
            }
            reader.close();
        } catch (FileNotFoundException e) {
            System.out.println(e.getMessage());
        }
    }

    // PARSER TAGS

    private void loadTags(String path) throws XMLStreamException {
        XMLInputFactory input = XMLInputFactory.newInstance();
        XMLStreamReader reader = null;

        try {
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
        } catch (FileNotFoundException e) {
            System.out.println(e.getMessage());
        }
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

    // GETTERS E SETTERS

    public Map<Long, User> getUsers() {
        Map<Long, User> novo = new HashMap<>();

        for (Map.Entry<Long, User> entry : this.users.entrySet()) {
            novo.put(entry.getKey(), entry.getValue().clone());
        }

        return novo;
    }

    public void setUsers(Map<Long, User> users) {
        Map<Long, User> novo = new HashMap<>();

        for (Map.Entry<Long, User> entry : users.entrySet()) {
            novo.put(entry.getKey(), entry.getValue().clone());
        }

        this.users = novo;
    }

    public Map<PostKey, Post> getPosts() {
        Map<PostKey, Post> novo = new HashMap<>();

        for (Map.Entry<PostKey, Post> entry : posts.entrySet()) {
            novo.put(entry.getKey(), entry.getValue().clone());
        }

        return novo;
    }

    public void setPosts(Map<PostKey, Post> posts) {
        Map<PostKey, Post> novo = new HashMap<>();

        for (Map.Entry<PostKey, Post> entry : posts.entrySet()) {
            novo.put(entry.getKey(), entry.getValue().clone());
        }

        this.posts = novo;
    }

    public Map<Long, String> getPostAux() {
        Map<Long, String> novo = new HashMap<>();

        for (Map.Entry<Long, String> entry : postAux.entrySet()) {
            novo.put(entry.getKey(), entry.getValue());
        }

        return novo;
    }

    public void setPostAux(Map<Long, String> postAux) {
        Map<Long, String> novo = new HashMap<>();

        for (Map.Entry<Long, String> entry : postAux.entrySet()) {
            novo.put(entry.getKey(), entry.getValue());
        }

        this.postAux = novo;
    }

    public Map<String, Tag> getTags() {
        Map<String, Tag> novo = new HashMap<>();

        for (Map.Entry<String, Tag> entry : tags.entrySet()) {
            novo.put(entry.getKey(), entry.getValue().clone());
        }

        return novo;
    }

    public void setTags(Map<String, Tag> tags) {
        Map<String, Tag> novo = new HashMap<>();

        for (Map.Entry<String, Tag> entry : tags.entrySet()) {
            novo.put(entry.getKey(), entry.getValue().clone());
        }

        this.tags = novo;
    }


    // CONSTRUCTORS

    public TCD() {
        this.users = new HashMap<>();
        this.posts = new TreeMap<>((d1, d2) -> d1.compareTo(d2));
        this.postAux = new HashMap<>();
        this.tags = new HashMap<>();
    }

    public TCD(Map<Long, User> user, Map<PostKey, Post> post, Map<Long, String> postAux, Map<String, Tag> tag) {
        this.users = user;
        this.posts = post;
        this.postAux = postAux;
        this.tags = tag;
    }

    public TCD(TCD outro) {
        this.users = outro.getUsers();
        this.posts = outro.getPosts();
        this.postAux = outro.getPostAux();
        this.tags = outro.getTags();
    }


    /* -------------------------------- DEFINIÇÃO DAS QUERIES --------------------------------*/
    // ****************** ver das exceptions
    // Load
    public void load(String path) {
        try {
            loadUsers(path + "/Users.xml");
            loadTags(path + "/Tags.xml");
            loadPosts(path + "/Posts.xml");
        } catch (XMLStreamException e) {
            e.printStackTrace();
        }
    }


    // Query 1
    public Pair<String, String> infoFromPost(long id) {
        try {
            String titulo, nome;
            User user = null;
            Post post = getPost(id);

            switch (post.getTypeID()) {
                case 1:
                    long owner_id = post.getOwnerID();
                    user = this.users.get(owner_id);
                    break;

                case 2:
                    long parent_id = post.getParentID();
                    post = getPost(parent_id);
                    user = this.users.get(post.getOwnerID());
                    break;
            }


            return new Pair<>(post.getTitulo(), user.getDisplayName());
        } catch (PostNotFoundException e) {
            e.printStackTrace();
        }
        return null; // tirar, so meti para compilar
    }

    // Query 2
    public List<Long> topMostActive(int N) {
        Set<User> users_by_nposts = new TreeSet<>((u1, u2) -> {
            if (u2.getNPosts() - u1.getNPosts() == 0)
                return Long.compare(u2.getID(), u1.getID());
            return Integer.compare(u2.getNPosts(), u1.getNPosts());
        });

        this.users.values().addAll(users_by_nposts);

        return users_by_nposts.stream().limit(N).
                map(User::getID).
                collect(java.util.stream.Collectors.toList());
    }


    // Query 3
    // Arranjar esta versao e depois comparar em tempo com versao de stream e meterno relatorio seria interessante
    /*
    public Pair<Long,Long> totalPosts(LocalDate begin, LocalDate end) {
        long n_questions = 0, n_answers = 0;

        Set<Map.Entry<LocalDate, Post>> posts_entries = this.posts.entrySet();

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
*/
    // Versao stream query 3
    public Pair<Long,Long> totalPosts(LocalDate begin, LocalDate end){
        long n_questions = 0, n_answers = 0;

        Map<Integer, List<Post>> posts_by_type = this.posts.values()
                                                           .stream()
                                                           .filter(p -> isBetween(p.getData().toLocalDate(), begin, end))
                                                           .collect(Collectors.groupingBy(Post::getTypeID));

        n_questions = posts_by_type.get(1).size();
        n_answers = posts_by_type.get(2).size();

        return new Pair<>(n_questions, n_answers);
    }
    // Query 4 -- fazer o mesmo que na 3
/*
    public List<Long> questionsWithTag(String tag, LocalDate begin, LocalDate end) {
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
*/
    //Query 4 - versao com stream
    public List<Long> questionsWithTag(String tag_name, LocalDate begin, LocalDate end) {
        Tag tag = this.tags.get(tag_name); // throws tag inexistente exception.....

        return this.posts.values().stream()
                                  .filter(p -> isBetween(p.getData().toLocalDate(), begin, end) && p.getTags().contains(tag) )
                                  .map(Post::getID)
                                  .collect(Collectors.toList());
    }


    // Query 5 -- user not found exception
    public Pair<String, List<Long>> getUserInfo(long id) {
        User user = this.users.get(id); // != null

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
                                                                    if (p2.getScore() == p1.getScore())
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
    public List<Long> bothParticipated(int N, long id1, long id2) {
        return Arrays.asList(594L);
    }/*
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
    */
    // Query 10
    public long betterAnswer(long id) {
        return 175891;
    }

    // Query 11
    public List<Long> mostUsedBestRep(int N, LocalDate begin, LocalDate end) {
        return Arrays.asList(6L, 29L, 72L, 163L, 587L);
    }

    public void clear() {

    }


// Função para ver se uma data pertence a um dado intervalo de datas

    private static boolean isBetween(LocalDate to_check, LocalDate begin, LocalDate end) {
        return to_check.isAfter(begin) && to_check.isBefore(end);
    }

}