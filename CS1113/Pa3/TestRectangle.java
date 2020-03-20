import java.awt.Color;
import java.util.Random;

/*
  Write a test client for Rectangle that takes three command-line arguments
  n, min, and max; generates n random rectangles whose width and height are 
  uniformly distributed between min and max in the unit square; draws them 
  on standard drawing; and prints their average area and perimeter to standard
   output.
   */

// CS 1113 Pa3
// Parker Hague
// 60863
// 11/18/18

public class TestRectangle
{
    public static void main(String[] args) {
        System.out.println("Pa3 for Parker Hague, Lab CRN 60863");
        // command line parameters
        int n = Integer.parseInt(args[0]);
        double min = Double.parseDouble(args[1]);
        double max = Double.parseDouble(args[2]);
        boolean isFilled = Boolean.parseBoolean(args[3]);
        long seed = Long.parseLong(args[4]);
        StdRandom.setSeed(seed);

        double perimeter = 0.0;
        double area = 0.0;
        double xMin = 0.0;
        double xMax = 1.0;
        double yMin = 0.0;
        double yMax = 1.0;
        double sum = 0.0;
        Rectangle[] rectangles = new Rectangle[n];

        for (int i = 0; i < n; i++){
            // creates random rectangle
            double x = StdRandom.uniform(0.0, 1.0);
            double y = StdRandom.uniform(0.0, 1.0);
            double width = StdRandom.uniform(min, max);
            double height = StdRandom.uniform(min, max);
            rectangles[i] = new Rectangle(x, y, width, height);

            Color c = new Color(StdRandom.uniform(255),StdRandom.uniform(255),StdRandom.uniform(255));
            StdDraw.setPenColor(c);
            rectangles[i].draw(isFilled);
            StdDraw.setXscale(xMin-0.1,xMax+0.1);
            StdDraw.setYscale(yMin-0.1,yMax+0.1);

            perimeter += rectangles[i].perimeter();
            area += rectangles[i].area();
        }
        for (int j = 0; j < n; j++){
            for (int k = n-1; k>= 0; k--){
                if (j == k){
                    sum -= 1;
                }
                if (rectangles[j].intersects(rectangles[k])){
                    sum += 1;
                }
            }
        }
        System.out.println("average intersects = " + sum / n);
        System.out.println("average perimeter = " + perimeter / n);
        System.out.println("average area = " + area / n);

    }
}