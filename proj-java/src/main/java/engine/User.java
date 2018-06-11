package engine;

import java.time.LocalDateTime;
import java.util.ArrayList;
import java.util.List;
import java.util.Set;
import java.util.TreeSet;

public class User {

    private long id;
    private String display_name;
    private int n_posts;
    private int reputacao;
    private String short_bio;
    private Set<Post> user_posts;



    // Getters & Setters

    public long getID() { return this.id; }

    public void setID(long id) {
        this.id = id;
    }

    public String getDisplayName() {
        return this.display_name;
    }

    public void setDisplayName(String display_name) {
        this.display_name = display_name;
    }

    public int getNPosts() {
        return this.n_posts;
    }

    public void setNPosts(int n_posts) {
        this.n_posts = n_posts;
    }

    public int getRep() {
        return this.reputacao;
    }

    public void setRep(int reputacao) {
        this.reputacao = reputacao;
    }

    public String getShortBio() {
        return this.short_bio;
    }

    public void setShortBio(String short_bio) {
        this.short_bio = short_bio;
    }

    public List<Post> getUserPosts() { return new ArrayList<>(this.user_posts);}

    public void setUserPosts(Set<Post> user_posts) { this.user_posts = user_posts; }

    // Método para adicionar um Post a um utilizador

    public void addPost(Post post){
        this.user_posts.add(post);
        this.n_posts++;
    }

    // Equals & Clone

    public User clone(){
        return new User(this);
    }

    public boolean equals (Object o) {
        if (o == this) return true;
        if (o == null || this.getClass() != o.getClass()) return false;

        User user = (User) o;

        return this.id == user.getID() &&
                this.display_name.equals(user.getDisplayName()) &&
                this.n_posts == user.getNPosts() &&
                this.reputacao == user.getRep() &&
                this.short_bio.equals(user.getShortBio()) &&
                this.user_posts.equals(user.getUserPosts());
    }

    // Construtores

    public User(){
        this.id = -2;
        this.display_name = "";
        this.n_posts = -1;
        this.reputacao = -1;
        this.short_bio = "";
        this.user_posts = new TreeSet<>();
    }

    public User(long id, String display_name, int n_posts, int reputacao, String short_bio, Set<Post> user_posts) {
        this.id = id;
        this.display_name = display_name;
        this.n_posts = n_posts;
        this.reputacao = reputacao;
        this.short_bio = short_bio;
        this.user_posts = new TreeSet<>((p1,p2) -> p2.getData().compareTo(p1.getData()));
        this.user_posts.addAll(user_posts);
    }

    public User(User outro){
        this.id = outro.getID();
        this.display_name = outro.getDisplayName();
        this.n_posts = outro.getNPosts();
        this.reputacao = outro.getRep();
        this.short_bio = outro.getShortBio();
        this.user_posts = new TreeSet<>((p1,p2) -> p2.getData().compareTo(p1.getData()));
        this.user_posts.addAll(outro.getUserPosts());
    }

    public String toString() {
        return "src.main.java.engine.User{" +
                "id=" + id +
                ", display_name='" + display_name + '\'' +
                ", n_posts=" + n_posts +
                ", reputacao=" + reputacao +
                ", short_bio='" + short_bio + '\'' +
                ", user_posts=" + user_posts.toString() +
                '}';
    }
}
