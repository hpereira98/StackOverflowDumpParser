package engine;

import java.time.LocalDateTime;

public class PostKey implements Comparable<PostKey>{

    private LocalDateTime data;
    private long id;


    // Getters & Setters

    /**
     * Getter da data da PostKey
     * @return
     */
    public LocalDateTime getData() {
        return this.data;
    }

    /**
     * Setter da data da PostKey
     * @param data nova data
     */
    public void setData(LocalDateTime data) {
        this.data = data;
    }

    /**
     * Getter do ID da PostKey
     * @return ID do post
     */
    public long getID() {
        return this.id;
    }

    /**
     * Setter do ID da PostKey
     * @param id
     */
    public void setID(long id) {
        this.id = id;
    }


    // Comparator

    public int compareTo(PostKey pK) {
        long test = pK.getData().compareTo(this.getData());
        if(test==0) test = this.getID() - pK.getID();
        return (int)test;
    }


    // Equals & Clone

    /**
     * Método que verifica se duas PostKey são iguais
     * @param o objeto a comparar
     * @return true se forem iguais
     */
    public boolean equals(Object o) {
        if (o == this) return true;
        if (o == null || this.getClass() != o.getClass()) return false;

        PostKey pk = (PostKey) o;

        return this.id == pk.getID() && this.data.equals(pk.getData());
    }

    /**
     * Método que transforma um PostKey em String
     * @return String relativa ao PostKey
     */
    public String toString(){
        StringBuilder sb = new StringBuilder();

        sb.append("POSTKEY: \n");
        sb.append("ID: "); sb.append(id); sb.append("\n");
        sb.append("Data: "); sb.append(data); sb.append("\n");

        return sb.toString();
    }

    /**
     * Clone da classe PostKey
     * @return PostKey igual
     */
    public PostKey clone() {
        return new PostKey(this);
    }


    // Construtores

    /**
     * Construtor default da classe PostKey
     */
    public PostKey(){
        this.data = null;
        this.id = -2;
    }

    /**
     * Construtor paramétrico da classe PostKey
     * @param data
     * @param id
     */
    public PostKey(LocalDateTime data, long id){
        this.data = data;
        this.id = id;
    }

    /**
     * Construtor de cópia da classe PostKey
     * @param outra
     */
    public PostKey(PostKey outra){
        this.data = outra.getData();
        this.id = outra.getID();
    }

}
