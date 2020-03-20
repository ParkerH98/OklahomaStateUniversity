// CS 1113 Pa2
// Parker Hague
// 60863
// 10/7/18

public class Pa2Driver {
    public static void main(String[] args) {
        System.out.println("Pa2 for Parker Hague. CRN: 60863");
        // sets up input to be read for the functions
        double[] k = StdArrayIO.readDouble1D();
        double[] x = StdArrayIO.readDouble1D();
        double[] y = Pa2Lib.convolve(x, k);

        Pa2Lib.convolve(x, k);
        // finds min and max values for arrays x and y
        double xMin = StdStats.min(x);
        double xMax = StdStats.max(x);
        double yMin = StdStats.min(y);
        double yMax = StdStats.max(y);

        double xyMin;
        double xyMax;
        //checks x and y to find the most minimum
        if(xMin < yMin){
            xyMin = xMin;
        }
        else{
            xyMin = yMin;
        }
         //checks x and y to find the most maximum
        if(xMax > yMax){
            xyMax = xMax;
        }
        else{
            xyMax = yMax;
        }

        // sets x and y scale to the min and max of the arrays
        StdDraw.setXscale(-1, x.length);
        StdDraw.setYscale(xyMin * 1.1, xyMax * 1.1);

        StdStats.plotLines(x);

        StdDraw.setPenColor(StdDraw.BLUE);

        StdStats.plotLines(y);
    }
}