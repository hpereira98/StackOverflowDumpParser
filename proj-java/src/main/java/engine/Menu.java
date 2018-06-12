package engine;

import common.Pair;

import java.io.Serializable;
import java.time.LocalDate;
import java.time.format.DateTimeFormatter;
import java.time.format.DateTimeParseException;
import java.time.format.ResolverStyle;
import java.util.List;
import java.util.Scanner;

public class Menu implements Serializable {

    private static String[][] operacoes = {
                {//Menu inicial
                 "1 - Load",
                 "0 - Sair"},
                {//Menu Load
                 "1 - Android Dump",
                 "2 - Ubuntu Dump",
                 "0 - Retroceder"},
                {//Menu queries
                 "1 - Info From Post",
                 "2 - Top Most Active",
                 "3 - Total Posts",
                 "4 - Questions With Tag",
                 "5 - Get User Info",
                 "6 - Most Voted Answers",
                 "7 - Most Answered Questions",
                 "8 - Contains Word",
                 "9 - Both Participated",
                 "10 - Better Answer",
                 "11 - Most Used Best Rep",
                 "0 - Retroceder"}
    };

    public static void printTempo(long time) {
        System.out.println("Tempo em ms: ");
        System.out.println(time);
    }

    public static void printResultQ1(Pair<String,String> par){
        System.out.println("Resultado: ");
        System.out.println("Nome do autor: " + par.getSnd());
        System.out.println("Título do post: " + par.getFst());
        holdResultDisplay();
    }

    public static void printResultQ3(Pair<Long,Long> par){
        System.out.println("Resultado: ");
        System.out.println("Número de perguntas: " + par.getFst());
        System.out.println("Número de respostas: " + par.getSnd());
        holdResultDisplay();
    }

    public static void printLongList (List<Long> list){
        int i=1;
        System.out.println("Resultado: ");
        for(Long id : list){
            System.out.println((i++) + " - " + id);
        }
        holdResultDisplay();
    }

    public static void printResultQ5 (Pair<String, List<Long>> par){
        System.out.println("Resultado: ");
        System.out.println("Short Bio: " + par.getFst());
        System.out.println("Últimos posts:");
        printLongList(par.getSnd());
    }

    public static void printResultQ10 (Long id){
        System.out.println("Resultado: ");
        System.out.println("Melhor resposta: " + id);
        holdResultDisplay();
    }

    public static int readOp(){
        int op=-1;
        Scanner sc = new Scanner(System.in);
        System.out.println("Operação a realizar: ");
        while(op == -1)
            op = sc.nextInt();
        return op;
    }

    public static void printSeparador(){
        System.out.println("********LI3 - JAVA********");
    }

    public static void showMainMenuOps(){
        for(String op : operacoes[0])
            System.out.println(op);
    }

    public static void showLoadMenuOps(){
        for(String op : operacoes[1])
            System.out.println(op);
    }

    public static void showQueriesMenuOps(){
        for(String op : operacoes[2])
            System.out.println(op);
    }

    public static long getID(){
        Scanner sc = new Scanner(System.in);
        System.out.println("Insira o ID: ");
        long id = -2;

        while(id<=0) {
            id = sc.nextLong();
            if(id<=0) System.out.println("Insira uma ID válido");
        }

        return id;
    }

    public static int getN(){
        Scanner sc = new Scanner(System.in);
        System.out.println("Insira o N: ");
        int n = 0;

        while(n<=0) {
            n = sc.nextInt();
            if(n<=0) System.out.println("Insira um valor válido");
        }

        return n;
    }

    private static boolean isDate(String string){
            LocalDate data = null;
            DateTimeFormatter dateFormat = DateTimeFormatter.ofPattern("uuuu-MM-dd").withResolverStyle(ResolverStyle.STRICT);;
            try {
                data = LocalDate.parse(string, dateFormat);
                return true;
            }
            catch (DateTimeParseException e) {
                return false;
            }
    }

    public static LocalDate getData(int tipo){ //tipo 0: begin date, tipo 1: end date
        Scanner sc = new Scanner(System.in);
        String aux="";
        LocalDate data = null;
        boolean flag = false;

        if (tipo==0) System.out.println("Insira a data de início: (YYYY-MM-dd)");
        else System.out.println("Insira a data de fim: (YYYY-MM-dd)");

        while(aux.equals("") || !flag) {
            aux = sc.nextLine();
            flag=isDate(aux);
            if (!flag) System.out.println("Insira uma data válida");
        }
        data = LocalDate.parse(aux);
        return data;
    }

    public static String getString(int tipo){ //tipo 0: tag para as query4; tipo 1: palavra para a Query8
        Scanner sc = new Scanner(System.in);
        String res ="";
        if(tipo==1) System.out.println("Insira a palavra: ");
        else System.out.println("Insira a Tag: ");

        while(res.equals(""))
            res=sc.nextLine();

        return res;
    }

    public static String getDumpPath(){ //tipo 0: tag para as query4; tipo 1: palavra para a Query8
        Scanner sc = new Scanner(System.in);
        String path ="";
        System.out.println("Insira o Path do Dump a carregar: ");

        while(path.equals(""))
            path=sc.nextLine();

        return path;
    }

    private static void holdResultDisplay(){
        Scanner sc = new Scanner(System.in);
        System.out.println("0 - Retroceder");
        int opcao;
        do{
            opcao = sc.nextInt();
        }while(opcao!=0);
    }

}
