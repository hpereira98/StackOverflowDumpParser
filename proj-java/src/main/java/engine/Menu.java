package engine;

import java.io.Serializable;
import java.time.LocalDate;
import java.time.format.DateTimeFormatter;
import java.util.Scanner;

public class Menu implements Serializable {

    private static String[][] operacoes = {
                {//Menu inicial
                 "1 - Load Data",
                 "0 - Exit"},
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
                 "0 - Back"}
    };

    public static int readOp(){
        int op;
        Scanner sc = new Scanner(System.in);
        System.out.println("Operação a realizar: ");
        op = sc.nextInt();
        sc.close();
        return op;
    }

    public static void printSeparador(){
        System.out.println("********LI3 - JAVA********");
    }

    public static void showMainMenuOps(){
        for(String op : operacoes[0])
            System.out.println(op);
    }

    public static void showQueriesMenuOps(){
        for(String op : operacoes[1])
            System.out.println(op);
    }


    public static String getDumpPath(){
        Scanner sc = new Scanner(System.in);
        System.out.println("Insira o path do dump a carregar: ");
        String path = "";

        while(path.equals(""))
            path=sc.nextLine();

        return path;
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

    public static LocalDate getData(){
        Scanner sc = new Scanner(System.in);
        DateTimeFormatter dateFormat = DateTimeFormatter.ofPattern("YYYY-MM-dd");
        String aux="";
        LocalDate data = null;
        while(aux.equals("") && data==null) {
            aux = sc.nextLine();
            try {
                data= LocalDate.parse(aux,dateFormat);
            } catch (Exception e) {
                System.out.println("Insira a data num formato correto");
            }
        }
        return data;
    }

    public static String getString(){
        Scanner sc = new Scanner(System.in);
        String res ="";

        while(res.equals(""))
            res=sc.nextLine();

        return res;
    }

}
