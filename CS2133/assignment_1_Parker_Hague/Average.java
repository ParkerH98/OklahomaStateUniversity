import java.util.InputMismatchException;
import java.util.Scanner;

public class Average{
    public static void main(String[] args) {
        
        System.out.println("PLease print a number. Enter a negative to exit.");

        Scanner sc = new Scanner (System.in);
        
        try {
            double entry  = sc.nextDouble();
            
        } catch (Exception e) {
            System.out.println("Invalid entry. Please enter a number");
            sc.nextLine();
        }
        double entry  = sc.nextDouble();

        int count = 0;
        double sum = 0;

        while (entry >= 0){
            try {
                sum += entry;
                count ++;
                entry  = sc.nextDouble();
                
            } catch (Exception InputMismatchException) {
                System.out.println("Invalid entry. Please enter a number");
                sc.nextLine();
            }
        }
        sc.close();

        double average = sum / count;

        System.out.println("You entered " + count + " numbers averaging " + average);
    }
}