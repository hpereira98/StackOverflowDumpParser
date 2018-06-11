package engine;

import java.io.Serializable;

public class Menu implements Serializable {

        private static String[][] operacoes = { // Menu inicial
                {"1 - Load Data",
                 "0 - Exit"},
                {"1 - Info From Post",
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

    public static String[] getMainMenu(){
        return operacoes[0];
    }

    public static String[] getMenuQueries(){
        return operacoes[1];
    }
}
