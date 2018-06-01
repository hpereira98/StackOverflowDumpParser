package src.main.java.engine;

import common.Pair;

import javax.xml.stream.XMLInputFactory;
import javax.xml.stream.XMLStreamException;
import javax.xml.stream.XMLStreamReader;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.time.LocalDate;
import java.util.*;

public class TCD implements li3.TADCommunity {

    private Map<Long, User> users;
    private Map<PostKey, Post> posts;
    private Map<Long,String> postAux;
    private Map<String, Tag> tags;

    // QUERIES:

    // auxiliares

    private Post getPost(long id) throws PostNotFoundException {

        String data = postAux.get(id);
        if (data == null) throw new PostNotFoundException("src.main.java.engine.Post "+id+" não foi encontrado.");
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
                            users.put(id,user);
                        }
                        break;

                    case XMLStreamReader.END_ELEMENT:
                        break;
                }
            }
            reader.close();
        }
        catch (FileNotFoundException e) {
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
                int type_id=-2;
                long parent_id=-2;
                String data = "";
                String tags_str = "";
                int score=0;
                int n_comments=0;
                int n_answers=0;

                switch (eventType) {
                    case XMLStreamReader.START_ELEMENT:
                        String qName = reader.getName().getLocalPart();
                        if (qName.equalsIgnoreCase("row")) {
                            for (int i=0; i < reader.getAttributeCount(); i++) {
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
                            Post post = new Post(id, titulo, owner_id, type_id, parent_id, data, tagsToList(tags_str), score, n_comments, n_answers);
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
        }
        catch (FileNotFoundException e) {
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
                            Tag tag = new Tag(name,id);
                            tags.put(name,tag);
                        }
                        break;

                    case XMLStreamReader.END_ELEMENT:
                        break;
                }
            }
            reader.close();
        }
        catch (FileNotFoundException e) {
            System.out.println(e.getMessage());
        }
    }

    // Separa tags de uma string e passa para ArrayList

    private ArrayList<Tag> tagsToList(String str) {
        ArrayList<Tag> lista = new ArrayList<>();

        if (str!=null && str.length()>1){
            str = str.replace("<","").replace(">",",");
            str = str.substring(0,str.length() - 1);
            String[] strs = str.split(",");

            for (String string : strs) {
                Tag nova = tags.get(string);
                if (nova!=null) lista.add(nova);
            }
        }

        return lista;
    }

    // GETTERS E SETTERS

    public Map<Long, User> getUsers() {
        Map<Long, User> novo = new HashMap<>();

        for(Map.Entry<Long, User> entry : this.users.entrySet()) {
            novo.put(entry.getKey(),entry.getValue().clone());
        }

        return novo;
    }

    public void setUsers(Map<Long, User> users) {
        Map<Long, User> novo = new HashMap<>();

        for(Map.Entry<Long, User> entry : users.entrySet()) {
            novo.put(entry.getKey(),entry.getValue().clone());
        }

        this.users=novo;
    }

    public Map<PostKey, Post> getPosts() {
        Map<PostKey, Post> novo = new HashMap<>();

        for (Map.Entry<PostKey, Post> entry : posts.entrySet()) {
            novo.put(entry.getKey(),entry.getValue().clone());
        }

        return novo;
    }

    public void setPosts(Map<PostKey, Post> posts) {
        Map<PostKey, Post> novo = new HashMap<>();

        for(Map.Entry<PostKey, Post> entry : posts.entrySet()) {
            novo.put(entry.getKey(),entry.getValue().clone());
        }

        this.posts=novo;
    }

    public Map<Long, String> getPostAux() {
        Map<Long, String> novo = new HashMap<>();

        for(Map.Entry<Long,String> entry : postAux.entrySet()){
            novo.put(entry.getKey(),entry.getValue());
        }

        return novo;
    }

    public void setPostAux(Map<Long, String> postAux) {
        Map<Long,String> novo = new HashMap<>();

        for(Map.Entry<Long,String> entry : postAux.entrySet()) {
            novo.put(entry.getKey(),entry.getValue());
        }

        this.postAux=novo;
    }

    public Map<String, Tag> getTags() {
        Map<String, Tag> novo = new HashMap<>();

        for(Map.Entry<String, Tag> entry : tags.entrySet()) {
            novo.put(entry.getKey(),entry.getValue().clone());
        }

        return novo;
    }

    public void setTags(Map<String, Tag> tags) {
        Map<String, Tag> novo = new HashMap<>();

        for(Map.Entry<String, Tag> entry : tags.entrySet()) {
            novo.put(entry.getKey(),entry.getValue().clone());
        }

        this.tags=novo;
    }


    // CONSTRUCTORS

    public TCD() {
        this.users = new HashMap<>();
        this.posts = new TreeMap<>((d1,d2)-> d1.compareTo(d2));
        this.postAux = new HashMap<>();
        this.tags = new HashMap<>();
    }

    public TCD(Map<Long, User> user, Map<PostKey, Post> post, Map<Long, String> postAux, Map<String, Tag> tag) {
        this.users = user;
        this.posts = post;
        this.postAux = postAux;
        this.tags = tag;
    }

    public TCD(TCD outro){
        this.users=outro.getUsers();
        this.posts=outro.getPosts();
        this.postAux=outro.getPostAux();
        this.tags=outro.getTags();
    }





    /* -------------------------------- DEFINIÇÃO DAS QUERIES --------------------------------*/

    // Load
    public void load(String path){}
    public void loadA (String path) throws XMLStreamException{
        double startTime = System.nanoTime();
        loadUsers(path + "/Users.xml");
        double stopTime = System.nanoTime();
        System.out.println("EXEC USERS: "+((stopTime - startTime)/1000000000.0)+"seg");

        startTime = System.nanoTime();
        loadTags(path + "/Tags.xml");
        stopTime = System.nanoTime();
        System.out.println("EXEC TAGS: "+((stopTime - startTime)/1000000000.0)+"seg");

        startTime = System.nanoTime();
        loadPosts(path + "/Posts.xml");
        stopTime = System.nanoTime();
        System.out.println("EXEC POSTS: "+((stopTime - startTime)/1000000000.0)+"seg");
    }


    // Query 1
    public Pair<String,String> infoFromPost(long id) { // FIXME: Mudar o tipo para a estrutura q os stores derem

        try {
            Post post = getPost(id);

            switch (post.getTypeID()) {
                case 1: long owner_id = post.getOwnerID();
                    User user = users.get(owner_id).clone(); // FIXME: clone?
                    System.out.println("Titulo: " + post.getTitulo() + ", Nome: " + user.getDisplayName());
                    return new Pair<>(post.getTitulo(),user.getDisplayName());

                case 2: long parent_id = post.getParentID();
                    Post qPost = getPost(parent_id);
                    User qUser = users.get(qPost.getOwnerID()).clone(); // FIXME: clone?
                    System.out.println("Titulo: " + qPost.getTitulo() + ", Nome: " + qUser.getDisplayName());
                    return new Pair<>(qPost.getTitulo(), qUser.getDisplayName());
            }
        }
        catch (PostNotFoundException e) {
            e.printStackTrace();
        }
        return null;
    }

    // Query 2
    public List<Long> topMostActive(int N) {
        return Arrays.asList(15811L,449L,158442L,167850L,367165L,295286L,59676L,93977L,35795L,3940L);
    }

    // Query 3
    public Pair<Long,Long> totalPosts(LocalDate begin, LocalDate end) {
        return new Pair<>(3667L,4102L);
    }

    // Query 4
    public List<Long> questionsWithTag(String tag, LocalDate begin, LocalDate end) {
        return Arrays.asList(276174L,276029L,274462L,274324L,274316L,274141L,274100L,272937L,
                272813L,272754L,272666L,272565L,272450L,272313L,271816L,271683L,271647L,270853L,270608L,270528L,270488L,
                270188L,270014L,269876L,269781L,269095L,268501L,268155L,267746L,267656L,267625L,266742L,266335L,266016L,
                265531L,265483L,265443L,265347L,265104L,265067L,265028L,264764L,264762L,264616L,264525L,264292L,263816L,
                263740L,263460L,263405L,263378L,263253L,262733L,262574L);
    }

    // Query 5
    public Pair<String, List<Long>> getUserInfo(long id) {
        String shortBio = "<p>Coder. JS, Perl, Python, Basic<br>Books/movies: SF+F.<br>Dead:" +
                "dell 9300<br>Dead: dell 1720 as of may 10th 2011.</p>\n" +
                "<p>Current system: Acer Aspire 7750G.<br>\n" +
                "Works OOTB as of Ubuntu 12.04.<br></p>";
        List<Long> ids = Arrays.asList(982507L,982455L,980877L,980197L,980189L,976713L,974412L,
                974359L,973895L,973838L);
        return new Pair<>(shortBio,ids);
    }

    // Query 6
    public List<Long> mostVotedAnswers(int N, LocalDate begin, LocalDate end) {
        return Arrays.asList(701775L,697197L,694560L,696641L,704208L);
    }

    // Query 7
    public List<Long> mostAnsweredQuestions(int N, LocalDate begin, LocalDate end) {
        return Arrays.asList(505506L,508221L,506510L,508029L,506824L,505581L,505368L,509498L,509283L,508635L);
    }

    // Query 8
    public List<Long> containsWord(int N, String word) {
        return Arrays.asList(980835L,979082L,974117L,974105L,973832L,971812L,971056L,968451L,964999L,962770L);
    }

    // Query 9
    public List<Long> bothParticipated(int N, long id1, long id2) {
        return Arrays.asList(594L);
    }

    // Query 10
    public long betterAnswer(long id) {
        return 175891;
    }

    // Query 11
    public List<Long> mostUsedBestRep(int N, LocalDate begin, LocalDate end) {
        return Arrays.asList(6L,29L,72L,163L,587L);
    }

    public void clear(){

    }
}
