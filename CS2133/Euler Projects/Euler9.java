
// Parker Hague
// euler problem #3
// verified correct answer 6857


public class Euler9{
    public static void main(String[] args) {

        long max = 0;
        double number = 600851475143L;

        for (long i = 3; i < number; i += 2){
            while (number % i == 0){
                max = i;
                number /= i;
            }
        }
        System.out.println(number);
    }
}