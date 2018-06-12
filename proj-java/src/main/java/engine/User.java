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


    /**
     * Método que adiciona um Post a um User
     * @param post Post a adicionar
     */
    public void addPost(Post post){
        this.user_posts.add(post);
        this.n_posts++;
    }


    // Getters & Setters

    /**
     * Getter do ID do User
     * @return ID do User
     */
    public long getID() { return this.id; }

    /**
     * Setter do ID do User
     * @param id novo ID
     */
    public void setID(long id) {
        this.id = id;
    }

    /**
     * Getter do Display Name do User
     * @return Display Name do User
     */
    public String getDisplayName() {
        return this.display_name;
    }

    /**
     * Setter do Display Name do User
     * @param display_name novo Display Name
     */
    public void setDisplayName(String display_name) {
        this.display_name = display_name;
    }

    /**
     * Getter do número de posts do User
     * @return número de posts
     */
    public int getNPosts() {
        return this.n_posts;
    }

    /**
     * Setter do número de posts do User
     * @param n_posts novo número de posts
     */
    public void setNPosts(int n_posts) {
        this.n_posts = n_posts;
    }

    /**
     * Getter da reputação do User
     * @return reputação
     */
    public int getRep() {
        return this.reputacao;
    }

    /**
     * Setter da reputação do User
     * @param reputacao nova reputação
     */
    public void setRep(int reputacao) {
        this.reputacao = reputacao;
    }

    /**
     * Getter da Short Bio do User
     * @return short bio
     */
    public String getShortBio() {
        return this.short_bio;
    }

    /**
     * Setter da Short Bio do User
     * @param short_bio nova short bio
     */
    public void setShortBio(String short_bio) {
        this.short_bio = short_bio;
    }

    /**
     * Getter dos posts que o User fez
     * @return posts do User
     */
    public Set<Post> getUserPosts() { return new TreeSet<>(this.user_posts);}

    /**
     * Setter dos posts que o User fez
     * @param user_posts novos posts
     */
    public void setUserPosts(Set<Post> user_posts) { this.user_posts = new TreeSet<>(user_posts); }



    // Equals & Clone & toString

    /**
     * Método que verifica se dois User são iguais
     * @param o objeto a comparar
     * @return true se forem iguais
     */
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

    /**
     * Clone da classe User
     * @return User igual
     */
    public User clone(){
        return new User(this);
    }

    /**
     * Método que transforma um User em String
     * @return String relativa ao User
     */
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



    // Construtores

    /**
     * Construtor default da classe User
     */
    public User(){
        this.id = -2;
        this.display_name = "";
        this.n_posts = -1;
        this.reputacao = -1;
        this.short_bio = "";
        this.user_posts = new TreeSet<>();
    }

    /**
     * Construtor paramétrico da classe User
     * @param id
     * @param display_name
     * @param n_posts
     * @param reputacao
     * @param short_bio
     * @param user_posts
     */
    public User(long id, String display_name, int n_posts, int reputacao, String short_bio, Set<Post> user_posts) {
        this.id = id;
        this.display_name = display_name;
        this.n_posts = n_posts;
        this.reputacao = reputacao;
        this.short_bio = short_bio;
        this.user_posts = new TreeSet<>();
        this.user_posts.addAll(user_posts);
    }

    /**
     * Construtor de cópia da classe User
     * @param outro
     */
    public User(User outro){
        this.id = outro.getID();
        this.display_name = outro.getDisplayName();
        this.n_posts = outro.getNPosts();
        this.reputacao = outro.getRep();
        this.short_bio = outro.getShortBio();
        this.user_posts = new TreeSet<>();
        this.user_posts.addAll(outro.getUserPosts());
    }

}
