public class Post {

    private int id;
    private String titulo;
    private int owner_id;
    private int type_id;
    private int parent_id;
    private String data;
    private Arraylist<Tag> tags;
    private int score;
    private int n_comments;
    private int n_answers;


    // Getters & Setters


    public int getID() {
        return this.id;
    }

    public void setID(int id) {
        this.id = id;
    }

    public String getTitulo() {
        return this.titulo;
    }

    public void setTitulo(String titulo) {
        this.titulo = titulo;
    }

    public int getOwnerID() {
        return this.owner_id;
    }

    public void setOwnerID(int owner_id) {
        this.owner_id = owner_id;
    }

    public int getTypeID() {
        return this.type_id;
    }

    public void setTypeID(int type_id) {
        this.type_id = type_id;
    }

    public int getParentID() {
        return this.parent_id;
    }

    public void setParentID(int parent_id) {
        this.parent_id = parent_id;
    }

    public String getData() {
        return this.data;
    }

    public void setData(String data) {
        this.data = data;
    }

    public Arraylist<Tag> getTags() { // FIXME: 21-05-2018
        return this.tags;
    }

    public void setTags(Arraylist<Tag> tags) {
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


    // Construtores


    public Post() {

    }

    public Post(int id, String titulo, int owner_id, int type_id, int parent_id, String data, Arraylist<Tag> tags, int score, int n_comments, int n_answers) {
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

    }
}
