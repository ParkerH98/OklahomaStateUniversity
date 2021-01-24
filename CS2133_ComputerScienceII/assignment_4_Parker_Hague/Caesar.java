import java.io.*;

public class Caesar{
    public static void main(String[] args) throws IOException {

        int key = Integer.parseInt(args[0]); // encryption key
        String inFileName = args[1]; // file pathname
        String outFileName = args[2]; //file pathname
  
        File inFile = new File(inFileName);
        File outFile = new File(outFileName);

        int charValue;
        char outputChar;

        try{

            BufferedReader in = new BufferedReader(new FileReader(inFile));
            PrintWriter out = new PrintWriter(outFile);

           while ((charValue = in.read()) != -1){

            if (charValue < 32 || charValue > 126){
                outputChar = (char)charValue;
            }

            charValue += key;

            if (charValue > 126){
                charValue -= 95;
            }
            else if (charValue < 32){
                charValue += 95;
            }
            
            outputChar = (char)charValue;

            // prints to file or prints to command line
            if (args.length > 2) {
				if (!args[2].contains(".txt")) {
					throw new Exception();
                }
                
                out.print(outputChar);

            }
            else System.out.print(outputChar);
           }
   
           out.close();
           in.close();
        }

        catch (FileNotFoundException e){
            System.out.println("File not  found in directory");
        }
        catch (IOException e) {
			System.out.println("File not found or readable");
        }
        catch (IllegalArgumentException e) {
			System.out.println("Illegal argument");
		}
        catch (Exception e){
            System.out.println(e.getMessage());
        }
    }
}