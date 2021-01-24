// Euler problem 13
// verified correct answer 5537376230

import java.io.BufferedReader;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.math.BigInteger;

public class Euler15{
    public static void main(String[] args) {
        
        try {
            
            FileReader fileReader = new FileReader("numbers.txt");
            BufferedReader buffReader = new BufferedReader(fileReader);

            BigInteger sum = BigInteger.ZERO;

            String line;
            while ((line = buffReader.readLine()) != null){

                BigInteger number = new BigInteger(line);
                sum = sum.add(number);

            }
            buffReader.close();

            System.out.println("Sum: " + sum);

            String stringSum = String.valueOf(sum);
            String firstTen = "";
      
            firstTen = stringSum.substring(0, 10);

            System.out.println("First ten digits of sum: " + firstTen);

        } catch (FileNotFoundException e) {
            System.out.println("ERROR File not found");
        }
        catch (IOException e) {
            e.printStackTrace();
        }
    }
}