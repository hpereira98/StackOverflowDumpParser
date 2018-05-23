import java.util.Objects;

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
    
    public String toString(){
        return ""; // FIXME: 22-05-2018 
    }
    


    // Construtores

    public Tag(){
        this.nome = "";
        this.id = -2;
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
