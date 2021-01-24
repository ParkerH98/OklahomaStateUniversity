
// Parker Hague
// Euler problem #12
// verified correct answer 76576500



import java.util.ArrayList;

public class Euler13{
    public static void main(String[] args) {
        
        long start = System.currentTimeMillis();

        ArrayList<Long> triangleNumbers = new ArrayList<Long>();

        Long sum = 0L;

        // this part creates an ArrayList of Longs that are triangle numbers
        for (int i = 1; i <= 15000; i++){

            sum = 0L;
            for (int j = 1; j <= i; j++){

                sum += j;
            }

            triangleNumbers.add(sum);
        }

        int divisorCount = 0;
        Long number = 0L;

        // this part counts the number of divisors
        // for each Long in the ArrayList
        for (int i = 1; i <= triangleNumbers.size(); i++) {
            
            number = triangleNumbers.get(i);
            divisorCount = 0;

            for (int j = 1; j <= Math.sqrt(number); j++){

                if (number % j == 0){
                    divisorCount++;
                }
            }

            divisorCount *= 2;

            if (divisorCount >= 500){
                long finish = System.currentTimeMillis();
                System.out.println("Answer : " + triangleNumbers.get(i));
                System.out.println("Time taken: " + (finish - start) + " milliseconds");
                break;
            }
        }
    }
}