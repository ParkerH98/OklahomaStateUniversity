// CS 1113 Pa2
// Parker Hague
// 60863
// 10/7/18

public class Pa2Lib {

    public static double[] firstDerivative(double[] x, double h){
        double[] dx = new double[x.length];
        if (dx.length == 0){
            return dx;
        }
        else if(dx.length == 1){
            dx[0] = 0.0;
            return dx;
        }
        else if(dx.length > 1){
            // forward derivative at x[0]
            dx[0] = ((x[1] - x[0]) / h);
            // backwards derivative at x[x.length - 1] (last element)
            dx[x.length -1] = ((x[x.length - 1] - x[x.length - 2]) / h);
           for (int i = 1; i < x.length -1; i++){
                
                // central difference at dx[i]
                dx[i] = ((x[i +1] - x[i - 1]) / (2 * h));
           }
        }
        return dx;
    }

    public static double[] secondDerivative(double[] x, double h){
        double[] ddx = new double[x.length];
        if (ddx.length == 0){
            return ddx;
        }
        else if(ddx.length == 1){
            ddx[0] = 0.0;
            return ddx;
        }
        else if(ddx.length > 1){
            // setting first element to 0
            ddx[0] = 0;
            // setting last element to 0
            ddx[x.length -1] = 0;
            for(int i = 1; i < x.length -1; i++){
                // central difference at ddx[i]
                ddx[i] = (x[i - 1] - 2 * x[i] + x[i + 1]) / (h * h);
                
            }
        }
        return ddx;
    }

    public static double[] convolve(double[] x, double[] k){
        int c = k.length / 2;
        double [] y = new double[x.length];
       
        for (int i = c; i < x.length - c; i++){
            double sum = 0;
            for (int j = -c; j <= c; j++){ 
                sum += x[i + j] * k[c + j];
                y[i] = sum;
            }
        }
        return y;
    }
    public static void main(String[] args) {
        System.out.println("Pa2 for Parker Hague. CRN: 60863");

        double h = Double.parseDouble(args[0]);
        double[] data = StdArrayIO.readDouble1D();
        double[] kernal1 = {-0.5, 0.0, 0.5};
        double[] kernal2 = { 1.0, -2.0, 1.0 };

        StdArrayIO.print(data);

        StdArrayIO.print(firstDerivative(data, h));
        
        StdArrayIO.print(secondDerivative(data, h));
        
        StdArrayIO.print(convolve(data, kernal1));

        StdArrayIO.print(convolve(data, kernal2));
    }
}
