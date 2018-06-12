package engine;

import java.time.LocalDateTime;
import java.util.ArrayList;
import java.util.List;

public class Post implements Comparable<Post> {

    private long id;
    private String titulo;
    private long owner_id;
    private int type_id;
    private long parent_id;
    private LocalDateTime data;
    private List<Tag> tags;
    private int score;
    private int n_comments;
    private int n_answers;


    public int compareTo(Post o) {
        if(this.data.equals(o.getData()))
            return Long.compare(this.id, o.getID());
        return o.getData().compareTo(this.data);
    }

    // Getters & Setters

    /**
     * Getter do ID do Post
     * @return ID do Post
     */
    public long getID() {
        return this.id;
    }

    /**
     * Setter do ID do Post
     * @param id novo ID
     */
    public void setID(long id) {
        this.id = id;
    }

    /**
     * Getter do título do Post
     * @return título do Post
     */
    public String getTitulo() {
        return this.titulo;
    }

    /**
     * Setter do título do Post
     * @param titulo novo título
     */
    public void setTitulo(String titulo) {
        this.titulo = titulo;
    }

    /**
     * Getter do ID do autor do Post
     * @return ID do autor do Post
     */
    public long getOwnerID() {
        return this.owner_id;
    }

    /**
     * Setter do ID do autor do Post
     * @param owner_id novo ID do autor
     */
    public void setOwnerID(long owner_id) {
        this.owner_id = owner_id;
    }

    /**
     * Getter do ID do tipo de Post
     * @return ID do tipo de Post
     */
    public int getTypeID() {
        return this.type_id;
    }

    /**
     * Setter do ID do tipo de Post
     * @param type_id novo ID do tipo
     */
    public void setTypeID(int type_id) {
        this.type_id = type_id;
    }

    /**
     * Getter do ID do qual o Post descende
     * @return ID do Post do "pai"
     */
    public long getParentID() {
        return this.parent_id;
    }

    /**
     * Setter do ID do qual o Post descende
     * @param parent_id novo ID do "pai"
     */
    public void setParentID(long parent_id) {
        this.parent_id = parent_id;
    }

    /**
     * Getter da data de criação do Post
     * @return data de criação do Post
     */
    public LocalDateTime getData() {
        return this.data;
    }

    /**
     * Setter da data de criação do Post
     * @param data nova data
     */
    public void setData(LocalDateTime data) {
        this.data = data;
    }

    /**
     * Getter da lista das tags do Post
     * @return lista das tags
     */
    public List<Tag> getTags() { // FIXME: 21-05-2018
        return this.tags;
    }

    /**
     * Setter da lista das tags do Post
     * @param tags nova lista de tags
     */
    public void setTags(List<Tag> tags) {
        this.tags = tags;
    }

    /**
     * Getter do score do Post
     * @return score
     */
    public int getScore() {
        return this.score;
    }

    /**
     * Setter do score do Post
     * @param score novo score
     */
    public void setScore(int score) {
        this.score = score;
    }

    /**
     * Getter do número de comentários que o Post tem
     * @return número de comentários
     */
    public int getNComments() {
        return this.n_comments;
    }

    /**
     * Setter do número de comentários do Post
     * @param n_comments novo número de comentários
     */
    public void setNComments(int n_comments) {
        this.n_comments = n_comments;
    }

    /**
     * Getter do número de respostas que o Post tem
     * @return número de respostas
     */
    public int getNAnswers() {
        return this.n_answers;
    }

    /**
     * Setter do número de respostas do Post
     * @param n_answers novo número de respostas
     */
    public void setNAnswers(int n_answers) {
        this.n_answers = n_answers;
    }





    // Equals & Clone & toString

    /**
     * Método que verifica se dois Post são iguais
     * @param o objeto a comparar
     * @return true se forem iguais
     */
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

    /**
     * Clone da classe Post
     * @return Post igual
     */
    public Post clone(){
        return new Post(this);
    }

    /**
     * Método que transforma um Post em String
     * @return String relativa ao Post
     */
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



    // Construtores

    /**
     * Construtor defaut da classe Post
     */
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

    /**
     * Construtor paramétrico da classe Post
     * @param id
     * @param titulo
     * @param owner_id
     * @param type_id
     * @param parent_id
     * @param data
     * @param tags
     * @param score
     * @param n_comments
     * @param n_answers
     */
    public Post(long id, String titulo, long owner_id, int type_id, long parent_id, LocalDateTime data, List<Tag> tags, int score, int n_comments, int n_answers) {
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

    /**
     * Construtor de cópia da classe Post
     * @param outro
     */
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


}
