import java.net.Socket;
import java.io.*;

public class ClientConnection implements Runnable{
    
    private Socket socket;
    static String fileName;
	static final String DEFAULT_FILE = "index.html";
	static final String FILE_NOT_FOUND = "HTTP/1.1 404 Not Found\r\n\r\n";
    final static String OK = "HTTP/1.1 200 OK\r\n";
	final static String TYPE_TEXT = "Content-type: text/html\r\n\r\n";
	final static String ERROR = "HTTP/1.1 500 Internal Server Error\r\n\r\n";

    File requestedFile;
    static BufferedInputStream txtIn;
    private static PrintStream out;


    public ClientConnection(Socket socket){
        this.socket = socket;
    }

    @Override
    public void run() {
        
        try {
            BufferedReader in = new BufferedReader(new InputStreamReader(socket.getInputStream()));
            String line;
            String fileName = "";
            String prompt = "";

            while((line = in.readLine()) != null){
                if (line.contains("GET")){
                    prompt = line;
                }
                System.out.println(line);
            }

            out = new PrintStream(new BufferedOutputStream(socket.getOutputStream()));

            fileName = prompt.substring(4, prompt.indexOf("HTTP") - 1);

            if (fileName.equals("/")){
                fileName = DEFAULT_FILE;
            }

            if (fileName.contains("..")) {
				out.println(ERROR);
			}

            requestedFile = new File(fileName);
           
            if (requestedFile.exists()){
                out.println(OK);
                out.println(TYPE_TEXT);

                txtIn = new BufferedInputStream(new FileInputStream(requestedFile));
                byte[] bytes = new byte[(int)requestedFile.length()];
                txtIn.read(bytes, 0, bytes.length);


                out.write(bytes, 0, bytes.length);
                out.flush();
                txtIn.close();
            }

            else if (!requestedFile.exists()) {
				out.println(FILE_NOT_FOUND);
				out.flush();
			}
			else {
				out.println(ERROR);
				out.flush();
            }

            out.close();
        } 

        catch (FileNotFoundException e) {
			System.out.println("ERROR: file not found");
		}
        catch (IOException e) {
            System.out.println("ERROR IOException: the socket is closed, not connected, or the socket input has been shutdown");
        }
        catch (Exception e) {
            e.printStackTrace();
        }
    }
}