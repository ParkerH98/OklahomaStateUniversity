import java.io.*;
import java.util.Random;

public class JobFileCreator {

    Random r = new Random(12345);
    public String jobName;
    public int priority;
    public int arrivalTime;
    public int length;




    public String randomJobName(){

        int min = 0;
        int max = 10000;
        int random = r.nextInt((max - min) + 1) + min;
        String rJobName = "Job" + random;
        return rJobName;
    }

    public int randomPriority(){

        int min = -10;
        int max = 10;
        int random = r.nextInt((max - min) + 1) + min;
        return random;
    }

    public int randomLength(){

        int min = 1;
        int max = 100;
        int random = r.nextInt((max - min) + 1) - min;
        return random;
    }

    public int randomArrivalTime(){

        int min = 0;
        int max = 10000000;
        int random = r.nextInt((max - min) + 1) - min; 
        return random;
    }


    public static void main(String[] args) {

        String outFileName = "JobFile.txt";
        File fileName = new File(outFileName);
        JobFileCreator test = new JobFileCreator();

        try{

            FileWriter writer = new FileWriter(fileName);
            for (int i = 0; i < 5000; i++) {

                String jobString = test.randomJobName() + " " + test.randomPriority() +  " " + test.randomArrivalTime() + " " + test.randomLength();
                writer.write(jobString);
                writer.write("\n");
            }

            writer.close();
        }

        catch(Exception e){
            e.printStackTrace();
        }
    }
}