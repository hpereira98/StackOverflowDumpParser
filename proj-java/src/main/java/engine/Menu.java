package engine;

import common.Pair;

import java.io.Serializable;
import java.time.LocalDate;
import java.time.format.DateTimeFormatter;
import java.time.format.DateTimeParseException;
import java.time.format.ResolverStyle;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;
import java.util.Scanner;

public class Menu implements Serializable {

    private List<List<String>> menus;

    /**
     * Construtor default da classe Menu
     */
    public Menu(){
        this.menus = new ArrayList<>();

        this.menus.add(Arrays.asList("1 - Load",
                                     "0 - Sair"));

        this.menus.add(Arrays.asList("1 - Info From Post",
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
                                     "0 - Retroceder"));
    }


    /**
     * Método que imprime o tempo
     * @param time
     */
    public static void printTempo(long time) {
        System.out.println("Tempo em ms: ");
        System.out.println(time);
    }

    /**
     * Método que imprime o resultado da query 1
     * @param par
     */
    public static void printResultQ1(Pair<String,String> par){
        System.out.println("Resultado: ");
        System.out.println("Nome do autor: " + par.getSnd());
        System.out.println("Título do post: " + par.getFst());
        holdResultDisplay();
    }

    /**
     * Método que imprime o resultado da query 3
     * @param par
     */
    public static void printResultQ3(Pair<Long,Long> par){
        System.out.println("Resultado: ");
        System.out.println("Número de perguntas: " + par.getFst());
        System.out.println("Número de respostas: " + par.getSnd());
        holdResultDisplay();
    }

    /**
     * Método que imprime uma lista
     */
    public static void printLongList (List<Long> list){
        int i=1;
        System.out.println("Resultado: ");
        for(Long id : list){
            System.out.println((i++) + " - " + id);
        }
        holdResultDisplay();
    }

    /**
     * Método que imprime o resultado da query 5
     * @param par
     */
    public static void printResultQ5 (Pair<String, List<Long>> par){
        System.out.println("Resultado: ");
        System.out.println("Short Bio: " + par.getFst());
        System.out.println("Últimos posts:");
        printLongList(par.getSnd());
    }

    /**
     * Método que imprime o resultado da query 10
     * @param id
     */
    public static void printResultQ10 (Long id){
        System.out.println("Resultado: ");
        System.out.println("Melhor resposta: " + id);
        holdResultDisplay();
    }

    /**
     * Método que lê a opção do utilizador
     */
    public static int readOp(){
        int op=-1;
        Scanner sc = new Scanner(System.in);
        System.out.println("Operação a realizar: ");
        while(op == -1)
            op = sc.nextInt();
        return op;
    }

    /**
     * Método que imprime um separador
     */
    public static void printSeparador(){
        System.out.println("********LI3 - JAVA********");
    }

    /**
     * Método que imprime o menu inicial
     */
    public void showMainMenuOps(){
        for(String op : this.menus.get(0))
            System.out.println(op);
    }

    /**
     * Método que imprime o menu das queries disponiveis
     */
    public void showQueriesMenuOps(){
        for(String op : this.menus.get(1))
            System.out.println(op);
    }

    /**
     * Método que lê um ID
     */
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

    /**
     * Método que lê um número
     */
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

    /**
     * Método que lê uma data no formato (YYYY-MM-dd)
     */
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

    /**
     * Método que verifica se uma data é do formato (YYYY-MM-dd)
     * @param string
     * @return
     */
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

    /**
     * Método que lê uma String
     * @param tipo
     * @return
     */
    public static String getString(int tipo){ //tipo 0: tag para as query4; tipo 1: palavra para a Query8
        Scanner sc = new Scanner(System.in);
        String res ="";
        if(tipo==1) System.out.println("Insira a palavra: ");
        else System.out.println("Insira a Tag: ");

        while(res.equals(""))
            res=sc.nextLine();

        return res;
    }

    /**
     * Método que lê o path do dump
     * @return
     */
    public static String getDumpPath(){ //tipo 0: tag para as query4; tipo 1: palavra para a Query8
        Scanner sc = new Scanner(System.in);
        String path ="";
        System.out.println("Insira o Path do Dump a carregar: ");

        while(path.equals(""))
            path=sc.nextLine();

        return path;
    }

    /**
     *
     */
    private static void holdResultDisplay(){
        Scanner sc = new Scanner(System.in);
        System.out.println("0 - Retroceder");
        int opcao;
        do{
            opcao = sc.nextInt();
        }while(opcao!=0);
    }

}
