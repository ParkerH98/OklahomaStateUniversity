// CS 1113 Lab 4a
// Parker Hague
// 60863
// 10/4/18

public class Lab4a {
    public static double[] overdrive(double[] x, double clip){
            double[] y = new double[x.length];
            for (int i = 0; i < y.length; i++)
            if(Math.abs(x[i]) < clip)
            {
                y[i] = x[i];
            }
            else 
            {
                y[i] = Math.copySign(clip, x[i]);
            }
            return y;
        }
        public static double[] echo(double[] x, double[] lag){
            double[] y = new double[x.length];
            for(int i = 0; i < x.length; i++){
            if(i < lag.length){
                y[i] = (x[i] + lag[i]) / 2.0;
            }
            else{
                y[i] = (x[i] + x[i-lag.length])/2.0;
            }
        }
        int shift = x.length - lag.length;
             for(int i=0; i< lag.length; ++i) {
                if (shift + i   < 0) {
                   // not long enough, shift end of lag
                   lag[i] = lag[x.length +i];
                } else {
                   lag[i] = x[shift + i];
} }
            return y;
        }

    public static void main(String [] args){
        // usage: java Lab4a < datafile
        // where data file is in 1D array format expected by StdArrayIO
        StdOut.printf("Lab %2s for %12s, Lab CRN %5s\n","4a",
                      "Parker Hague", "60863");
                      
        double[] lag = new double[3];
        
        while (!StdIn.isEmpty()) { 
            double[] data = StdArrayIO.readDouble1D();
            StdOut.println("Original data array is ");
            StdArrayIO.print(data);

            double[] result = overdrive(data,3.5);
             StdOut.println("overdrive of data array with clip 3.5 is ");
             StdArrayIO.print(result);

             result = echo(data,lag);
             StdOut.println("echo of data with lag length of 3 is  ");
             StdArrayIO.print(result);

        }
    }
}
