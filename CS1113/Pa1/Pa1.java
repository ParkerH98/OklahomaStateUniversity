// CS 1113 Lab 2
// Parker Hague
// 60863
// September 13, 2018
public class Pa1 {
    public static void main(String [] args){
        System.out.println("Pa1 for Parker Hague, Lab CRN 60863");

        int n = Integer.parseInt(args [0]);
            if (n <= 0)
            {
                System.out.println("Invalid number of samples");
                System.exit(0);
            }
        double r = Double.parseDouble(args [1]);
            if (r <= 0)
            {
                System.out.print("Invalid radius");
                System.exit(0);
            }

            double sum = 0;

            for (int i = 0; i < n; i++){
               double zi = r * Math.random();

                sum += Math.sqrt(r * r - zi * zi);
            }
            double area = (sum * r) / n;

            System.out.println(area+" estimated for radius "+r+" from "+n+" samples.");
    }
}