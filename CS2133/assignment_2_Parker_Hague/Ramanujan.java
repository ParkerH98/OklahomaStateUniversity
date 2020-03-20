public class Ramanujan{
    public static void main(String[] args) {

        int n = Integer.parseInt(args[0]);
        double[] pi = new double[n];
        double[] num = new double[n];
        double[] den = new double[n];
        double sum = 0;
        double form = (2 * Math.sqrt(2)) / 9801; // used to multiply final sum

        for (int i = 0; i < n ; i++){
            num[i] = Factorial.calculate(4 * i) * (1103 + (26390 * i)); // numerator
            den[i] = (Math.pow(Factorial.calculate(i), 4) * (Math.pow(396, 4 * i)));  // denominator
            pi[i] = (num[i] / den[i]); // runs calculation
            sum += pi[i]; // adds each term
        }

        sum = sum * form;  // multiplying the sum by the missing part of the equation

        sum = Math.pow(sum, -1); // gets the reciprocal of pi
       
        double diff = 100 - ((sum / Math.PI) * 100);
        StdOut.printf("Pi according to Ramanujan series: %.16f%n", sum);     
        StdOut.printf("This differs from Java's value by: %.16f percent %n", diff);
    }
}