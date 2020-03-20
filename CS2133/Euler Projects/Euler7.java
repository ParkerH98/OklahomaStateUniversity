import java.math.BigInteger;

// problem 20
// verified correct answer 648

public class Euler7{
    public static void main(String[] args) {

        BigInteger sum = new BigInteger("1");

        for (int i = 99; i > 0; i--){
            sum = sum.multiply(BigInteger.valueOf(i));
        }

        System.out.println( "100 Factorial : " + sum);
        String sumString = sum.toString();
        System.out.println("The sum of the digits: " + digitSum(sumString));
    }

    public static int digitSum(String n){
        int sum = 0;
        for (int i = 0; i < n.length(); i++){
            int temp = Character.getNumericValue(n.charAt(i));
            sum += temp;
        }
        return sum;
    }
}