package CS3353.PA5;

import java.io.*;
import java.util.Random;

public class NumberGenerator {

    Random r = new Random(12345);
    public String jobName;
    public int priority;
    public int arrivalTime;
    public int length;




    public int randomNumber(){

        int min = 0;
        int max = 10000;
        int random = r.nextInt((max - min) + 1) + min;
        return random;
    }

   

    public static void main(String[] args) {

        String outFileName = "Numbers.txt";
        File fileName = new File(outFileName);
        NumberGenerator test = new NumberGenerator();

        try{

            FileWriter writer = new FileWriter(fileName);
            for (int i = 0; i < 20; i++) {

               
                int randomNum = test.randomNumber();
                writer.write(randomNum);
                writer.write("\n");
            }

            writer.close();
        }

        catch(Exception e){
            e.printStackTrace();
        }
    }
}