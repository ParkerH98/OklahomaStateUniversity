
// Euiler problem 56
// verified correct answer 972



import java.math.BigInteger;

public class Euler16{
    




    public static void main(String[] args) {
        

        BigInteger product = BigInteger.ZERO;
        long maxDigitSum = 0;
        long digitSum = 0;
        String temp = "";

   
        for (int a = 1; a < 100; a++){
            
            for (int b = 1; b < 100; b++){

                product = BigInteger.valueOf(a).pow(b);
                
                temp = product.toString();

                digitSum = 0;
                for (int i = 0; i < temp.length(); i++){

                    digitSum += temp.charAt(i) - '0';
                }

                if (digitSum > maxDigitSum) maxDigitSum = digitSum;
            }
        }

        System.out.println(maxDigitSum);
    }
}