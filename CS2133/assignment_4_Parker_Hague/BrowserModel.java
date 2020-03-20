import java.io.*;
import java.net.*;
import java.util.IllegalFormatException;

public class BrowserModel{

    public static String host;
    public static String filePath;
    public static String webText = "";



    public static void getHost(String input){

        host = "";

        // this assumes the user entered "http://"
        for (int i = 7; i < input.length(); i++){
            if (input.charAt(i) != '/'){
                host += input.charAt(i);
            }
            else break;
        }
    }



    public static void getFilePath(String input, String host){

		int index = 7 + host.length();
		if (input.length() != index) {
			filePath = input.substring(index);
		}
		else filePath = "";
	}

    public static void sendURL(String filePath, String host){

        String line;
        try {
        
            Socket socket = new Socket(host, 80);
            PrintWriter out = new PrintWriter(socket.getOutputStream()); 
            BufferedReader in = new BufferedReader(new InputStreamReader(socket.getInputStream()));
     
            out.print("GET /" + filePath + " HTTP/1.1\r\n");
            out.print("host: " + host + " \r\n\r\n");
            out.flush();

            while ((line = in.readLine()) != null){
                webText += (line + "\n");
            }
        }
        
        catch (UnknownHostException ex) {
			System.out.println("ERROR: Host URL not recognized.");
		}
		catch (IllegalFormatException ex) {
			System.out.println("ERROR: HTTP response not formatted correctly.");
		}
        
        catch (Exception e) {
            e.printStackTrace();
        }
    }

    public static String getTitle(String HTML){
  
         if (webText.equals("")){
            return "Browser";
        }

        int start = HTML.indexOf("<title>") + "<title>".length();
        int end = HTML.indexOf("</title>", start);
        String title = HTML.substring(start, end);
        return title;
    }


    public static String getBody(String HTML){
  
        if (webText.equals("")){
            return "";
        }
        int start = HTML.indexOf("<body>") + "<body>".length();
        int end = HTML.indexOf("</body>", start);
        String body = HTML.substring(start, end);

        body = body.replaceAll("\\<.*?\\>", "");
        //body = body.replaceAll("\\{.*?\\}", "");
        return body;
    }
}