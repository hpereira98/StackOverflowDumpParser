package engine;

public class Tag{

    private String nome;
    private long id;


    // Getters & Setters

    /**
     * Getter do nome da Tag
     * @return nome da tag
     */
    public String getNome() {
        return this.nome;
    }

    /**
     * Setter do nome da Tag
     * @param nome novo nome
     */
    public void setNome(String nome) {
        this.nome = nome;
    }

    /**
     * Getter do ID da Tag
     * @return ID da Tag
     */
    public long getID() {
        return this.id;
    }

    /**
     * Setter do ID da Tag
     * @param id novo ID
     */
    public void setID(long id) {
        this.id = id;
    }


    
    // Equals & Clone & toString

    /**
     * Método que verifica se duas tags são iguais
     * @param o objeto a comparar
     * @return true se forem iguais
     */
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        
        Tag tag = (Tag) o;
        
        return this.id == tag.getID() &&
               this.nome.equals(tag.getNome());
    }

    /**
     * Clone da class Tag
     * @return Tag igual
     */
    public Tag clone(){
        return new Tag(this);
    }

    /**
     * Método que transforma uma Tag em String
     * @return String relativa à Tag
     */
    public String toString() {
        return "src.main.java.engine.Tag{" +
                "nome='" + nome + '\'' +
                ", id=" + id +
                '}';
    }


    // Construtores

    /**
     * Construtor default da classe Tag
     */
    public Tag(){
        this.nome = "";
        this.id = -2;
    }

    /**
     * Construtor paramétrico da classe Tag
     * @param nome
     * @param id
     */
    public Tag(String nome, long id){
        this.nome = nome;
        this.id = id;
    }

    /**
     * Construtor de cópia da classe Tag
     * @param outra
     */
    public Tag(Tag outra){
        this.nome = outra.getNome();
        this.id = outra.getID();
    }


}
