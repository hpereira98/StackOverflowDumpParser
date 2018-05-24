import javax.xml.stream.*;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.util.*;

public class TCD {

    private Map<Long,User> users;
    private Map<PostKey,Post> posts;
    private Map<Long,String> postAux;
    private Map<String,Tag> tags;


    // PARSER

    public void readFile (String path) throws XMLStreamException {
        readFileUsers(path + "/Users.xml");
        readFileTags(path + "/Tags.xml");
        readFilePosts(path + "/Posts.xml");
    }


    // PARSER USERS

    public void readFileUsers(String path) throws XMLStreamException {
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
                        for (int i=0; i < reader.getAttributeCount(); i++) {
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
                        if (id!=-2) {
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

    public void readFilePosts(String path) throws XMLStreamException {
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
                        if (id!=-2) {
                            //inserir nas estruturas
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

    public void readFileTags(String path) throws XMLStreamException {
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
                        for (int i=0; i < reader.getAttributeCount(); i++) {
                            switch (reader.getAttributeLocalName(i)) {
                                case "Id":
                                    id = Long.parseLong(reader.getAttributeValue(i));
                                    break;
                                case "TagName":
                                    name = reader.getAttributeValue(i);
                                    break;
                            }
                        }
                        if (id!=-2) {
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
        str = str.replace("<","").replace(">",",");
        str = str.substring(0,str.length() - 1);
        String[] strs = str.split(",");

        ArrayList<Tag> lista = new ArrayList<>();

        for (String string : strs) {
            Tag nova = tags.get(string);
            if (nova!=null) lista.add(nova);
        }

        return lista;
    }

    // GETTERS E SETTERS

    public Map<Long, User> getUsers() {
        Map<Long,User> novo = new HashMap<>();

        for(Map.Entry<Long,User> entry : this.users.entrySet()) {
            novo.put(entry.getKey(),entry.getValue().clone());
        }

        return novo;
    }

    public void setUsers(Map<Long, User> users) {
        Map<Long,User> novo = new HashMap<>();

        for(Map.Entry<Long,User> entry : users.entrySet()) {
            novo.put(entry.getKey(),entry.getValue().clone());
        }

        this.users=novo;
    }

    public Map<PostKey, Post> getPosts() {
        Map<PostKey,Post> novo = new HashMap<>();

        for (Map.Entry<PostKey,Post> entry : posts.entrySet()) {
            novo.put(entry.getKey(),entry.getValue().clone());
        }

        return novo;
    }

    public void setPosts(Map<PostKey, Post> posts) {
        Map<PostKey,Post> novo = new HashMap<>();

        for(Map.Entry<PostKey,Post> entry : posts.entrySet()) {
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
        Map<String,Tag> novo = new HashMap<>();

        for(Map.Entry<String,Tag> entry : tags.entrySet()) {
            novo.put(entry.getKey(),entry.getValue().clone());
        }

        return novo;
    }

    public void setTags(Map<String, Tag> tags) {
        Map<String,Tag> novo = new HashMap<>();

        for(Map.Entry<String,Tag> entry : tags.entrySet()) {
            novo.put(entry.getKey(),entry.getValue().clone());
        }

        this.tags=novo;
    }

    // CLONE

    public TCD clone(){
        return new TCD(this);
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


}
