// CS 1113 Lab 3
// Parker Hague
// 60863
// 9/21/18
public class Lab3b{ 
   public static void main(String[] args) { 
      System.out.println("Lab 3b for Parker Hague, Lab CRN 60863");
      int count = 0;       // number input values
      double sum = 0.0;    // sum of input values
      double minValue = Double.MAX_VALUE;  //init with largest possible value
      double maxValue = -Double.MAX_VALUE; //init with most negative value
      // read data and compute statistics
      while (!StdIn.isEmpty()) {
         double value = StdIn.readDouble();
         if (value < minValue)
         {
            minValue = value;
         }
         if (value > maxValue)
         {
            maxValue = value;
         }
         sum += value;
         count++;
      }
      double mean = sum / count;
      StdOut.printf("Mean = %15.8e with Max = %15.8e and Min = %15.8e \n",mean,maxValue,minValue);
   }
}
