public class PostKey {

    private String data;
    private int id;



    // Getters & Setters

    public String getData() {
        return this.data;
    }

    public void setData(String data) {
        this.data = data;
    }

    public int getID() {
        return this.id;
    }

    public void setID(int id) {
        this.id = id;
    }


    // Construtores

    public PostKey(){
        this.data = "";
        this.id = -1;
    }

    public PostKey(String data, int id){
        this.data = data;
        this.id = id;
    }

    public PostKey(PostKey outra){
        this.data = outra.getData();
        this.id = outra.getID();
    }
}
