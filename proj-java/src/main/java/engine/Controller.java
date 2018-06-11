package engine;

import common.Pair;

import javax.xml.stream.XMLStreamException;
import java.time.LocalDate;
import java.time.LocalDateTime;
import java.time.Month;
import java.time.format.DateTimeFormatter;
import java.util.List;
import java.util.Scanner;


public class Controller {
    private li3.TADCommunity qe;

    public Controller(){ // ver com o stor se esta correto e ver como é que faz print dos resultados !!!!!!!!!!!!!!!!!!!
        this.qe = new TCD();
    }

    public void start(){
        int opcao;

        do{
            Menu.printSeparador();
            Menu.showMainMenuOps();
            opcao = Menu.readOp();
            Menu.printSeparador();
            switch(opcao){
                case 0:  break;
                case 1:  enteringQueriesMenu(); break;
                default: System.out.println("Insira uma opção correta");
            }
        }while(opcao != 0);
    }

    private void enteringQueriesMenu(){ // é melhor meter a dar as opcoes e nao o user a escrever o path
        String path = Menu.getDumpPath();
        try{
            qe.load(path);
        }
        catch (XMLStreamException e){ // este print é feito no controlador ?
            System.out.println("Erro ao carregar os dados");
        }
        execQueriesMenu();
    }

    private void execQueriesMenu(){
        int opcao;

        do{
            Menu.printSeparador();
            Menu.showQueriesMenuOps();
            opcao = Menu.readOp();
            if(opcao!=0) Menu.printSeparador();
            switch(opcao){
                case 0: break;
                case 1: handlerQuery1(); break;
                case 2: handlerQuery2(); break;
                case 3: handlerQuery3(); break;
                case 4: handlerQuery4(); break;
                case 5: handlerQuery5(); break;
                case 6: handlerQuery6_7(6); break;
                case 7: handlerQuery6_7(7); break;
                case 8: handlerQuery8(); break;
                case 9: handlerQuery9(); break;
                case 10: handlerQuery10(); break;
                case 11: handlerQuery11(); break;
                default: System.out.println("Insira uma opção correta");
            }
        }while(opcao != 0);
    }

    private void handlerQuery1() {
        long before, after;
        long id = Menu.getID();
        try{
            before = System.currentTimeMillis();
            common.Pair<String, String> q1 = qe.infoFromPost(id);
            after = System.currentTimeMillis();
            //falta parte de escrita no log
        }
        catch (PostNotFoundException e){
            System.out.println("O post com ID: " + e.getMessage() + " não existe.");
        }
        catch (UserNotFoundException e){
            System.out.println("O User com ID: " + e.getMessage() + " não existe.");
        }
    }

    private void handlerQuery2() {
        int n = Menu.getN();

        long before = System.currentTimeMillis();
        List<Long> q2 = qe.topMostActive(n);
        long after = System.currentTimeMillis();
    }

    private void handlerQuery3() {
        LocalDate begin = Menu.getData();
        LocalDate end = Menu.getData();

        long before = System.currentTimeMillis();
        Pair<Long,Long> q3 = qe.totalPosts(begin, end);
        long after = System.currentTimeMillis();
    }

    private void handlerQuery4() {
        String tag = Menu.getString();
        LocalDate begin = Menu.getData();
        LocalDate end = Menu.getData();

        try{
            long before = System.currentTimeMillis();
            List<Long> q4 = qe.questionsWithTag(tag, begin, end);
            long after = System.currentTimeMillis();
        }
        catch (TagNotFoundException e){
            System.out.println("Tag " + e.getMessage() + " não existe");
        }
    }

    private void handlerQuery5() {
        long id = Menu.getID();

        try{
            long before = System.currentTimeMillis();
            Pair<String, List<Long>> q5 = qe.getUserInfo(id);
            long after = System.currentTimeMillis();
        }
        catch (UserNotFoundException e){
            System.out.println("O User com ID: " + e.getMessage() + " não existe.");
        }
    }

    private void handlerQuery6_7(int query) {
        List<Long> result;
        LocalDate begin = Menu.getData();
        LocalDate end = Menu.getData();
        int n = Menu.getN();

        long before = System.currentTimeMillis();
        if(query == 6)
            result = qe.mostVotedAnswers(n, begin, end);
        else
            result = qe.mostAnsweredQuestions(n, begin, end);

        long after = System.currentTimeMillis();
    }

    private void handlerQuery8() {
        int n = Menu.getN();
        String word = Menu.getString();

        long before = System.currentTimeMillis();
        List<Long> q8 = qe.containsWord(n, word);
        long after = System.currentTimeMillis();
    }


    private void handlerQuery9(){
        int n = Menu.getN();
        long id1 = Menu.getID();
        long id2 = Menu.getID();

        try {
            long before = System.currentTimeMillis();
            List<Long> q9 = qe.bothParticipated(n, id1, id2);
            long after = System.currentTimeMillis();
        }
        catch (UserNotFoundException e){
            System.out.println("O User com ID: " + e.getMessage() + " não existe.");
        }
    }

    private void handlerQuery10(){
        long id = Menu.getID();

        try {
            long before = System.currentTimeMillis();
            long q10 = qe.betterAnswer(id);
            long after = System.currentTimeMillis();
        }
        catch (PostNotFoundException e){
            System.out.println("O post com ID: " + e.getMessage() + " não existe.");
        }
        catch (QuestionWithoutAnswersException e){
            System.out.println("O post com ID: " + e.getMessage() + " não tem respostas.");
        }
    }

    private void handlerQuery11(){
        int n = Menu.getN();
        LocalDate begin = Menu.getData();
        LocalDate end = Menu.getData();

        long before = System.currentTimeMillis();
        List<Long> q11 = qe.mostUsedBestRep(n, begin, end);
        long after = System.currentTimeMillis();
    }





}
