import java.math.BigInteger;
import java.util.ArrayList;

// Euler problem 29
// verified correct answer 9183

public class Euler12{
    public static void main(String[] args) {
        
        ArrayList<BigInteger> values = new ArrayList<>();

        BigInteger temp;

        for (int i = 2; i <= 100; i++){
            for (int j = 2; j <= 100; j++){
                temp = BigInteger.valueOf(i).pow(j);

                if (!values.contains(temp)){
                    values.add(temp);
                }
            }
        }
        System.out.println(values.size());
    }
}