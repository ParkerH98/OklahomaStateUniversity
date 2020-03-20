import java.net.*;

public class WebServer{
    public static void main(String[] args) {
        
        try {

            ServerSocket server = new ServerSocket(8080);
            
            while (true){
                Thread connection = new Thread(new ClientConnection(server.accept()));
                connection.start();
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
} 