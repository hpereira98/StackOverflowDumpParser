package engine;

public class PostNotFoundException extends Exception {
    PostNotFoundException(String msg) {
        super(msg);
    }
    PostNotFoundException(){super();}
}
