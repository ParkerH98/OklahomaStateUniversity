public class Euler5{
    public static void main(String[] args) {

        // PROBLEM 2
        // VERIFIED CORRECT ANSWER 4613732

        int wasUp = 0;
        int nextUp = 1;
        int sum = 0;
        int i = 0;
        int fibonacci = 0;

        while (fibonacci < 4000000){
            fibonacci = wasUp + nextUp;
            wasUp = nextUp;
            nextUp = fibonacci;
            if (fibonacci % 2 == 0){
                sum += fibonacci;
            }
            i++;
        }
        System.out.println("Sum of evens: " + sum);
    }
}
