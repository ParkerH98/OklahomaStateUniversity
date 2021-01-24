package CS2133.assignment_1_Parker_Hague;

public class Gregory {
    public static void main(String[] args) {
        
        int n = Integer.parseInt(args[0]);
        double sum = 0;

        for (int i = 1; i <= n; i++){
            double num = Math.pow(-1, i + 1);
            double den = (2 * i) - 1;
            double term = num / den;
            sum += term;
        }

        sum *= 4;
        double difference = 100 - ((sum / Math.PI) * 100);

        StdOut.printf("Pi according to Gregory series: %.16f%n", sum);   
        StdOut.printf("This differs from Java's value by: %.16f percent %n", difference);
    }
}

// cricks value is 3.175237710923643
// my value is     3.1752377109236390