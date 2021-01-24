
import java.awt.List;
import java.util.ArrayList;

public class Euler2{
    public static void main(String[] args) {

        // problem 10

        ArrayList<Integer> primes = new ArrayList<>();
        primes.add(0);
        primes.add(2);
        long primeSum = 2;
      
        for (int i = 3; i < 2000000; i++){
            boolean tf = false;
            tf = prime(i);
            if (tf){
                primes.add(i);
                primeSum += i;
            }
        }

       System.out.println("The 148,933th prime number is: " + primes.get(148933));
       System.out.println("The sum of the primes: " + primeSum);
    }

    public static boolean prime(int n){
        for (int i = 2; i < Math.sqrt(n) + 1; i++){
            if ( n % i == 0) return false;
        }
        return true;
    }
}
