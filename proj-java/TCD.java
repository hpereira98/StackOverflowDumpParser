import java.util.Map;
import java.util.HashMap;
import java.util.TreeMap;

public class TCD {

    private Map<Long,User> users;
    private Map<PostKey,Post> posts;
    private Map<Long,String> postAux;
    private Map<Long,Tag> tags;

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
            novo.put(entry.getKey(),entry.getValue().clone());
        }

        return novo;
    }

    public void setPostAux(Map<Long, String> postAux) {
        Map<Long,String> novo = new HashMap<>();

        for(Map.Entry<Long,String> entry : postAux.entrySet()) {
            novo.put(entry.getKey(),entry.getValue().clone());
        }

        this.postAux=novo;
    }

    public Map<Long, Tag> getTags() {
        Map<Long,Tag> novo = new HashMap<>();

        for(Map.Entry<Long,Tag> entry : tags.entrySet()) {
            novo.put(entry.getKey(),entry.getValue().clone());
        }

        return novo;
    }

    public void setTags(Map<Long, Tag> tags) {
        Map<Long,Tag> novo = new HashMap<>();

        for(Map.Entry<Long,Tag> entry : tags.entrySet()) {
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

    public TCD(Map<Long, User> user, Map<PostKey, Post> post, Map<Long, String> postAux, Map<Long, Tag> tag) {
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
