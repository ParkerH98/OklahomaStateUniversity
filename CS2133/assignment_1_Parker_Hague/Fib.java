public class Fib{
    public static void main(String[] args) {
        
        int n = Integer.parseInt(args[0]);

        int[] fib = new int[n + 2];
        fib[0] = 1;
        fib[1] = 1;

        for (int i = 2; i < n; i++){
            fib[i] = fib[i-1] + fib[i - 2];
        }

        System.out.println("The nth Fibonacci number is: " +fib[n - 1]);
    }
}