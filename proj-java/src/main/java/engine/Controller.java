package engine;

import java.time.LocalDate;
import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;
import java.util.Scanner;

public class Controller {
    private li3.TADCommunity qe;

    public Controller(TCD com){
        qe = new TCD(com);
    }

    private int readOp(){
        int op;
        Scanner sc = new Scanner(System.in);
        System.out.println("Operação a realizar: ");
        op = sc.nextInt();
        sc.close();
        return op;
    }

    private void showOps(String[] ops){
        for(String op : ops)
            System.out.println(op);
    }

    private static void printSeparador(){
        System.out.println("********LI3 - JAVA********");
    }

    public void start(){
        int opcao;
        String[] menu = Menu.getMainMenu();

        do{
            printSeparador();
            showOps(menu);
            opcao = readOp();
            printSeparador();
            switch(opcao){
                case 0: break;
                case 1: qe.load(getDumpPath()); execMenuQueries(); break;
                default: System.out.println("Insira uma opção correta");
            }
        }while(opcao != 0);
    }

    private String getDumpPath(){
        Scanner sc = new Scanner(System.in);
        System.out.println("Insira o path do dump a carregar: ");
        String path = "";

        while(path.equals(""))
            path=sc.nextLine();

        return path;
    }

    private long getID(){
        Scanner sc = new Scanner(System.in);
        System.out.println("Insira o ID: ");
        long id = -2;

        while(id<=-2)
            id=sc.nextLong();

        return id;
    }

    private int getN(){
        Scanner sc = new Scanner(System.in);
        System.out.println("Insira o N: ");
        int n = 0;

        while(n<=0)
            n=sc.nextInt();

        return n;
    }

    private LocalDate getData(){
        Scanner sc = new Scanner(System.in);
        DateTimeFormatter dateFormat = DateTimeFormatter.ofPattern("YYYY-MM-dd");
        String aux="";
        LocalDate data = null;
        while(aux.equals("") && data==null) {
            aux = sc.nextLine();
            try {
                data= LocalDate.parse(aux,dateFormat);
            } catch (Exception e) {
                System.out.println("Wrong Date Format");
            }
        }
        return data;
    }

    private String getString(){
        Scanner sc = new Scanner(System.in);
        String res ="";

        while(res.equals(""))
            res=sc.nextLine();

        return res;
    }

    //definir funções de get em baixo usadas

    public void execMenuQueries(){
        int opcao;
        String[] menu = Menu.getMenuQueries();
        do{
            printSeparador();
            showOps(menu);
            opcao = readOp();
            if(opcao!=0)printSeparador();
            switch(opcao){
                case 0: break;
                case 1: qe.infoFromPost(getID()); break;
                case 2: qe.topMostActive(getN()); break;
                case 3: qe.totalPosts(getData(),getData()); break;
                case 4: qe.questionsWithTag(getString(),getData(),getData()); break;
                case 5: qe.getUserInfo(getID()); break;
                case 6: qe.mostVotedAnswers(getN(),getData(),getData()); break;
                case 7: qe.mostAnsweredQuestions(getN(),getData(),getData()); break;
                case 8: qe.containsWord(getN(),getString()); break;
                case 9: qe.bothParticipated(getN(),getID(),getID()); break;
                case 10: qe.betterAnswer(getID()); break;
                case 11: qe.mostUsedBestRep(getN(),getData(),getData()); break;
                default: System.out.println("Insira uma opção correta");
            }
        }while(opcao != 0);
    }

}
