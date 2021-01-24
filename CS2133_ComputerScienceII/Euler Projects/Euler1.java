
import java.awt.List;
import java.util.ArrayList;

public class Euler1{
    public static void main(String[] args) {

        // problem 7

        ArrayList<Integer> primes = new ArrayList<>();
        primes.add(0);
        primes.add(2);
      
        for (int i = 3; i < 104800; i++){
            boolean tf = false;
            tf = prime(i);
            if (tf){
                primes.add(i);
            }
        }

       System.out.println("The 10,001th prime number is: " + primes.get(10001));
    }

    public static boolean prime(int n){
        for (int i = 2; i < n; i++){
            if ( n % i == 0){
                return false;
            }
        }
        return true;
    }
}
