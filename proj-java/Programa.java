import src.main.java.engine.TCD;

import javax.xml.stream.XMLStreamException;

public class Programa {

    public static void main (String []args) throws XMLStreamException {
        TCD com = new TCD();



        String path = "C:/Users/ASUS/Dropbox/MIEI/2º Ano/2º Semestre/Laboratórios de Informática III/Projeto/dumpexemplo/android";

        double startTime = System.nanoTime();
        com.readFiles(path);
        double stopTime = System.nanoTime();
        System.out.println("EXEC LOAD: "+((stopTime - startTime)/1000000000.0)+"seg");

        System.out.println("Load efetuado com sucesso!");
        /*System.out.println("USERS: ");
        System.out.println(com.getUsers().toString());
        System.out.println("POSTS: ");
        System.out.println(com.getPosts().toString());
        System.out.println("TAGS: ");
        System.out.println(com.getTags().toString());

        System.out.println("Print efetuado com sucesso!");*/

        com.info_from_post(1456);
    }
}
