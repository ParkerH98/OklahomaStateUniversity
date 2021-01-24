import java.math.BigInteger;

public class Euler4{
    public static void main(String[] args) {

        // PROBLEM 6
        // VERIFIED CORRECT ANSWER 25164150
        

       Long sumOfSquares = Euler4.sumOfSquares();
       Long squareOfSums = Euler4.squareOfSums();
       Long diff = squareOfSums - sumOfSquares();

        System.out.println("Sum of the squares: " + sumOfSquares);
        System.out.println("Square of the sums: " + squareOfSums);
        System.out.println("Difference of the sums: " + diff);     
    }

    public static long sumOfSquares(){
        long sum = 0;
        for (int i = 1; i < 101; i++){
            sum += Double.valueOf(Math.pow(i, 2)).longValue();
        }
        return sum;
    }

    public static long squareOfSums(){
        long sum = 0;
        for (int i = 1; i < 101; i++){
            sum += i;
        }
        return sum * sum;
    }
}