package CS2133.assignment_2_Parker_Hague;

public class Factorial {
    
    public static void main(String[] args) {

        long n = Long.parseLong(args[0]);

        try {
            if (n < 0 || n > 20){
                throw new Exception("Please enter a number, greater than -1 and less than 21, and try again.");
            }
            
        } catch (Exception e) {
            System.out.println(e.getMessage());
            System.exit(1);
        }

        System.out.println(Factorial.calculate(n));        
    }


    public static long calculate(long n){
        if (n < 0 || n > 20){
            return -1; // need to write exit code
        }
        else if (n == 0 || n == 1){
            return 1;
        }
        else return n * Factorial.calculate(n-1);   
    }
}