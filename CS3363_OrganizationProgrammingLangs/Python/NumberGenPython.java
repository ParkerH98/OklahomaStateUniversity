
import java.io.*;
import java.util.Random;

public class NumberGenPython {

    public Random r = new Random(12345);
    public Integer randomNum;


    public Integer randomNumber(){

        int min = 0;
        int max = 100000;
        Integer random = r.nextInt((max - min) + 1) + min;
        return random;
    }

    public void writeFile(int inputSize){

        String outFileName = "NumbersForPy.txt";
        File fileName = new File(outFileName);

            try{

                FileWriter writer = new FileWriter(fileName);
                for (int i = 0; i < inputSize; i++) {

                    if (i == inputSize - 1) {

                        randomNum = randomNumber();
    
                        writer.write(String.valueOf(randomNum));
                        writer.write("\n");
                        break;
                        
                    }
                   
                    randomNum = randomNumber();
    
                    writer.write(String.valueOf(randomNum) + ",");
                    writer.write("\n");
                }
    
                writer.close();
            }
    
            catch(Exception e){
                e.printStackTrace();
            }
    }

    public static void main(String[] args) {
        NumberGenPython test = new NumberGenPython();

        test.writeFile(200000);
    }
}