package engine;

import common.MyLog;
import common.Pair;

import javax.xml.stream.XMLStreamException;
import java.io.FileNotFoundException;
import java.time.LocalDate;
import java.time.LocalDateTime;
import java.time.Month;
import java.time.format.DateTimeFormatter;
import java.util.List;
import java.util.Scanner;


public class Controller {
    private li3.TADCommunity qe;
    private MyLog log;
    private  MyLog logtime;

    public Controller(){ // ver com o stor se esta correto e ver como é que faz print dos resultados !!!!!!!!!!!!!!!!!!!
        this.qe = new TCD();
        this.log = new MyLog("results");
        this.logtime = new MyLog("times");
    }

    public void start(){
        int opcao;

        do{
            Menu.printSeparador();
            Menu.showMainMenuOps();
            opcao = Menu.readOp();
            switch(opcao){
                case 0:  System.out.println("\nAté à próxima!"); break;
                case 1:  loadMenu(); break;
                default: System.out.println("Insira uma opção correta");
            }
        }while(opcao != 0);
    }

    private void loadMenu(){
        long before, after;
        String path="";
        while(path.equals("")) {
            Menu.printSeparador();
            path = Menu.getDumpPath();
        }

        if(!path.equals("")) {
            try {
                before = System.currentTimeMillis();
                qe.load(path);
                after = System.currentTimeMillis();
                logtime.writeLog("LOAD -> " + (after - before) + " ms");
                Menu.printTempo(after - before); // PRINT TEMPO
                execQueriesMenu();
            }
            catch (LoadDataErrorException e) {
                System.out.println("Erro ao carregar os dados");
            }
        }


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
            Pair<String, String> q1 = qe.infoFromPost(id);
            after = System.currentTimeMillis();
            logtime.writeLog("Query 1: -> " + (after - before) + " ms");
            log.writeLog("Query1 -> " + q1);
            Menu.printTempo(after-before); // PRINT TEMPO
            Menu.printResultQ1(q1); // PRINT RESULT
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
        logtime.writeLog("Query 2: -> " + (after - before) + " ms");
        log.writeLog("Query2 -> " + q2);
        Menu.printTempo(after-before); // PRINT TEMPO
        Menu.printLongList(q2); // PRINT RESULT
    }

    private void handlerQuery3() {
        LocalDate begin = Menu.getData(0);
        LocalDate end = Menu.getData(1);

        long before = System.currentTimeMillis();
        Pair<Long,Long> q3 = qe.totalPosts(begin, end);
        long after = System.currentTimeMillis();
        logtime.writeLog("Query 3: -> " + (after - before) + " ms");
        log.writeLog("Query3 -> " + q3);
        Menu.printTempo(after-before); // PRINT TEMPO
        Menu.printResultQ3(q3); // PRINT RESULT
    }

    private void handlerQuery4() {
        String tag = Menu.getString(0);
        LocalDate begin = Menu.getData(0);
        LocalDate end = Menu.getData(1);

        try{
            long before = System.currentTimeMillis();
            List<Long> q4 = qe.questionsWithTag(tag, begin, end);
            long after = System.currentTimeMillis();
            logtime.writeLog("Query 4: -> " + (after - before) + " ms");
            log.writeLog("Query4 -> " + q4);
            Menu.printTempo(after-before); // PRINT TEMPO
            Menu.printLongList(q4); // PRINT RESULT
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
            logtime.writeLog("Query 5: -> " + (after - before) + " ms");
            log.writeLog("Query5 -> " + q5);
            Menu.printTempo(after-before); // PRINT TEMPO
            Menu.printResultQ5(q5); // PRINT RESULT
        }
        catch (UserNotFoundException e){
            System.out.println("O User com ID: " + e.getMessage() + " não existe.");
        }
    }

    private void handlerQuery6_7(int query) {
        List<Long> result;
        LocalDate begin = Menu.getData(0);
        LocalDate end = Menu.getData(1);
        int n = Menu.getN();

        long before = System.currentTimeMillis();
        if(query == 6)
            result = qe.mostVotedAnswers(n, begin, end);
        else
            result = qe.mostAnsweredQuestions(n, begin, end);

        long after = System.currentTimeMillis();
        logtime.writeLog("Query "+query+": -> " + (after - before) + " ms");
        log.writeLog("Query"+query+" -> " + qe);
        Menu.printTempo(after-before); // PRINT TEMPO
        Menu.printLongList(result); // PRINT RESULT
    }

    private void handlerQuery8() {
        int n = Menu.getN();
        String word = Menu.getString(1);

        long before = System.currentTimeMillis();
        List<Long> q8 = qe.containsWord(n, word);
        long after = System.currentTimeMillis();
        logtime.writeLog("Query 8: -> " + (after - before) + " ms");
        log.writeLog("Query8 -> " + q8);
        Menu.printTempo(after-before); // PRINT TEMPO
        Menu.printLongList(q8); // PRINT RESULT
    }


    private void handlerQuery9(){
        int n = Menu.getN();
        long id1 = Menu.getID();
        long id2 = Menu.getID();

        try {
            long before = System.currentTimeMillis();
            List<Long> q9 = qe.bothParticipated(n, id1, id2);
            long after = System.currentTimeMillis();
            logtime.writeLog("Query 9: -> " + (after - before) + " ms");
            log.writeLog("Query9 -> " + q9);
            Menu.printTempo(after-before); // PRINT TEMPO
            Menu.printLongList(q9); // PRINT RESULT
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
            logtime.writeLog("Query 10: -> " + (after - before) + " ms");
            log.writeLog("Query10 -> " + q10);
            Menu.printTempo(after-before); // PRINT TEMPO
            Menu.printResultQ10(q10); // PRINT RESULT
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
        LocalDate begin = Menu.getData(0);
        LocalDate end = Menu.getData(1);

        long before = System.currentTimeMillis();
        List<Long> q11 = qe.mostUsedBestRep(n, begin, end);
        long after = System.currentTimeMillis();
        logtime.writeLog("Query 11: -> " + (after - before) + " ms");
        log.writeLog("Query11 -> " + q11);
        Menu.printTempo(after-before); // PRINT TEMPO
        Menu.printLongList(q11); // PRINT RESULT
    }

}
