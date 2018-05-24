public class PostKey implements Comparable<PostKey>{

    private String data;
    private long id;




    // Getters & Setters

    public String getData() {
        return this.data;
    }

    public void setData(String data) {
        this.data = data;
    }

    public long getID() {
        return this.id;
    }

    public void setID(long id) {
        this.id = id;
    }

    // Equals & Clone

    public boolean equals(Object o) {
        if (o == this) return true;
        if (o == null || this.getClass() != o.getClass()) return false;

        PostKey aux = (PostKey) o;

        return this.id == aux.getID() && this.data.equals(aux.getData());
    }

    public PostKey clone() {
        return new PostKey(this);
    }


    // Construtores

    public PostKey(){
        this.data = "";
        this.id = -2;
    }

    public PostKey(String data, long id){
        this.data = data;
        this.id = id;
    }

    public PostKey(PostKey outra){
        this.data = outra.getData();
        this.id = outra.getID();
    }

    // COMPARATOR

    public int compareTo(PostKey pK) {
        long test = this.getData().compareTo(pK.getData());
        if (test==0) test=this.getID() - pK.getID();
        return (int) test;
    }
}
