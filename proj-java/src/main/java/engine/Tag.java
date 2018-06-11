package engine;

public class Tag {

    private String nome;
    private long id;



    // Getters & Setters

    public String getNome() {
        return this.nome;
    }

    public void setNome(String nome) {
        this.nome = nome;
    }

    public long getID() {
        return this.id;
    }

    public void setID(long id) {
        this.id = id;
    }


    
    // Equals & Clone & toString
    
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        
        Tag tag = (Tag) o;
        
        return this.id == tag.getID() &&
               this.nome.equals(tag.getNome());
    }
    
    public Tag clone(){
        return new Tag(this);
    }


    // Construtores

    public Tag(){
        this.nome = "";
        this.id = -2;
    }

    public Tag(String nome, long id){
        this.nome = nome;
        this.id = id;
    }

    public Tag(Tag outra){
        this.nome = outra.getNome();
        this.id = outra.getID();
    }

    public String toString() {
        return "src.main.java.engine.Tag{" +
                "nome='" + nome + '\'' +
                ", id=" + id +
                '}';
    }
}
