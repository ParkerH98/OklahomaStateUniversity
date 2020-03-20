// CS 1113 Pa3
// Parker Hague
// 60863
// 11/18/18

public class SparseVector
{
    private final double[] coords;

    public SparseVector(double[] a){
        coords = new double[a.length];
        for (int i = 0; i < a.length; i++){
            coords[i] = a[i];
        }
    }


    public void put(int i, double v){
        this.coords[i] = v;
    }


    public double get(int i){
        return this.coords[i];
    }


    public double dot(SparseVector b)
   {  // Dot product of this vector and that.
      double sum = 0.0;
      for (int i = 0; i < coords.length; i++)
         sum += this.coords[i] * b.coords[i];
      return sum;
   }


    public SparseVector plus(SparseVector b)
   {  // Sum of this vector and that.
      double[] result = new double[coords.length];
      for (int i = 0; i < coords.length; i++)
         result[i] = this.coords[i] + b.coords[i];
      return new SparseVector(result);
   }
}