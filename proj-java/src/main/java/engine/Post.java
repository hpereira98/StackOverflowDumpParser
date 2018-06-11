package engine;

import java.time.LocalDateTime;
import java.util.ArrayList;

public class Post {

    private long id;
    private String titulo;
    private long owner_id;
    private int type_id;
    private long parent_id;
    private LocalDateTime data;
    private ArrayList<Tag> tags;
    private int score;
    private int n_comments;
    private int n_answers;


    // Getters & Setters


    public long getID() {
        return this.id;
    }

    public void setID(long id) {
        this.id = id;
    }

    public String getTitulo() {
        return this.titulo;
    }

    public void setTitulo(String titulo) {
        this.titulo = titulo;
    }

    public long getOwnerID() {
        return this.owner_id;
    }

    public void setOwnerID(long owner_id) {
        this.owner_id = owner_id;
    }

    public int getTypeID() {
        return this.type_id;
    }

    public void setTypeID(int type_id) {
        this.type_id = type_id;
    }

    public long getParentID() {
        return this.parent_id;
    }

    public void setParentID(long parent_id) {
        this.parent_id = parent_id;
    }

    public LocalDateTime getData() {
        return this.data;
    }

    public void setData(LocalDateTime data) {
        this.data = data;
    }

    public ArrayList<Tag> getTags() { // FIXME: 21-05-2018
        return this.tags;
    }

    public void setTags(ArrayList<Tag> tags) {
        this.tags = tags;
    }

    public int getScore() {
        return this.score;
    }

    public void setScore(int score) {
        this.score = score;
    }

    public int getNComments() {
        return this.n_comments;
    }

    public void setNComments(int n_comments) {
        this.n_comments = n_comments;
    }

    public int getNAnswers() {
        return this.n_answers;
    }

    public void setNAnswers(int n_answers) {
        this.n_answers = n_answers;
    }





    // Equals & Clone & toString

    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;

        Post post = (Post) o;

        return this.id == post.getID() &&
               this.titulo.equals(post.getTitulo()) &&
               this.owner_id == post.getOwnerID() &&
               this.type_id == post.getTypeID() &&
               this.parent_id == post.getParentID() &&
               this.data .equals(post.getData()) &&
               this.tags.equals(post.getTags()) &&
               this.score == post.getScore() &&
               this.n_comments == post.getNComments() &&
               this.n_answers == post.getNAnswers();
    }

    public Post clone(){
        return new Post(this);
    }


    // Construtores

    public Post() {
        this.id = -2;
        this.titulo = "";
        this.owner_id = -2;
        this.type_id = -1;
        this.parent_id = -2;
        this.data = null; // mudar e ver se mantemos todos os construtores ou so o que usamos
        this.tags = new ArrayList<>();
        this.score = -1;
        this.n_comments = -1;
        this.n_answers = -1;
    }

    public Post(long id, String titulo, long owner_id, int type_id, long parent_id, LocalDateTime data, ArrayList<Tag> tags, int score, int n_comments, int n_answers) {
        this.id = id;
        this.titulo = titulo;
        this.owner_id = owner_id;
        this.type_id = type_id;
        this.parent_id = parent_id;
        this.data = data;
        this.tags = tags;
        this.score = score;
        this.n_comments = n_comments;
        this.n_answers = n_answers;
    }

    public Post(Post outro){
        this.id = outro.getID();
        this.titulo = outro.getTitulo();
        this.owner_id = outro.getOwnerID();
        this.type_id = outro.getTypeID();
        this.parent_id = outro.getParentID();
        this.data = outro.getData();
        this.tags = outro.getTags();
        this.score = outro.getScore();
        this.n_comments = outro.getNComments();
        this.n_answers = outro.getNAnswers();
    }

    public String toString() {
        return "src.main.java.engine.Post{" +
                "id=" + id +
                ", titulo='" + titulo + '\'' +
                ", owner_id=" + owner_id +
                ", type_id=" + type_id +
                ", parent_id=" + parent_id +
                ", data='" + data + '\'' +
                ", tags=" + tags.toString() +
                ", score=" + score +
                ", n_comments=" + n_comments +
                ", n_answers=" + n_answers +
                '}';
    }
}
