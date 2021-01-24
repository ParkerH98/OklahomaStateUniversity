import java.math.BigInteger;

public class Euler3{
    public static void main(String[] args) {

        // PROBLEM 16
        // VERIFIED CORRECT ANSWER 1366

        BigInteger number = new BigInteger("2");
        BigInteger power = number.pow(1000);
        String powerSting = power.toString();

        System.out.println("String Value: "  + powerSting);

        System.out.println("Sum of digits: " + digitSum(powerSting));

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
