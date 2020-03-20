public class FibTest{
    public static void main(String[] args) {

        

        boolean iterTestPassed = false;
        boolean recurTestPassed = false;

        if (fibIter(10) == 55){
            iterTestPassed = true;
        }

        if (fibRecur(10) == 55){
            recurTestPassed = true;
        }

        if (iterTestPassed == false){
            System.out.println(iterTestPassed);
        }

        if (recurTestPassed == false){
            System.out.println(recurTestPassed);
        }

        long iterStart = System.currentTimeMillis();
        FibTest.fibIter(40);
        long iterEnd = System.currentTimeMillis();
        long iterTime = iterEnd - iterStart;

        long recurStart = System.currentTimeMillis();
        FibTest.fibRecur(40);
        long recurEnd = System.currentTimeMillis();
        long recurTime = recurEnd - recurStart;

        System.out.println("Execution Time for Iterative: " + iterTime);
        System.out.println("Execution Time for Recursive: " + recurTime);
    }

    public static int fibIter(int n){
        int[] fib = new int[n + 2];
        fib[0] = 1;
        fib[1] = 1;

        for(int i = 2; i < n; i++){
            fib[i] = fib[i - 1] + fib[i - 2];
        }
        return fib[n - 1];
    }

    public static int fibRecur(int n){
        if (n == 0 || n == 1){
            return n;
        }
        return fibRecur(n-1) + fibRecur(n-2);
    }
}