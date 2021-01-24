
// Parker Hague
// Euler problem #15
// Verified correct answer 
// 137846528820

import java.math.*;

public class Euler10{
    
    public static void main(String[] args) {
    
        int n = 40;
        int r = 20;

        BigInteger combo = factorial(n).divide(factorial(r).multiply(factorial(n - r)));
        System.out.println(combo);
    }


    public static BigInteger factorial(int n)
    {
        BigInteger big_n = BigInteger.ONE;

        for (int i = 1; i <= n; i ++) {
            big_n = big_n.multiply(BigInteger.valueOf(i));          
        }
        return big_n;
    }
}