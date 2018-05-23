import java.util.ArrayList;

public class User {

    private int id;
    private String display_name;
    private int n_posts;
    private int reputacao;
    private String short_bio;
    private ArrayList<Post> user_posts;



    // Getters & Setters

    public int getID() {
        return this.id;
    }

    public void setID(int id) {
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

    public ArrayList<Post> getUserPosts() {
        return this.user_posts;
    }

    public void setUserPosts(ArrayList<Post> user_posts) {
        this.user_posts = user_posts;
    }


    // Construtores

    public User(){
        this.id = -2;
        this.display_name = "";
        this.n_posts = -1;
        this.reputacao = -1;
        this.short_bio = "";
        this.user_posts = new ArrayList<>();
    }

    public User(int id, String display_name, int n_posts, int reputacao, String short_bio, ArrayList<Post> user_posts) {
        this.id = id;
        this.display_name = display_name;
        this.n_posts = n_posts;
        this.reputacao = reputacao;
        this.short_bio = short_bio;
        this.user_posts = user_posts;
    }

    public User(User outro){
        this.id = outro.getID();
        this.display_name = outro.getDisplayName();
        this.n_posts = outro.getNPosts();
        this.reputacao = outro.getRep();
        this.short_bio = outro.getShortBio();
        this.user_posts = outro.getUserPosts();
    }
}
