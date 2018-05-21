public class Tag {

    private String nome;
    private int id;



    // Getters & Setters

    public String getNome() {
        return this.nome;
    }

    public void setNome(String nome) {
        this.nome = nome;
    }

    public int getID() {
        return this.id;
    }

    public void setID(int id) {
        this.id = id;
    }


    // Construtores

    public Tag(){
        this.nome = "";
        this.id = -1;
    }

    public Tag(String nome, int id){
        this.nome = nome;
        this.id = id;
    }

    public Tag(Tag outra){
        this.nome = outra.getNome();
        this.id = outra.getID();
    }
}
