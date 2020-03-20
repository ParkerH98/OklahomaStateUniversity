public class Lab3a {
    public static void main(String [] args){
        for (int r=1; r <=5; ++r) 
        {
            double x = 4.0+r;
            for (int c=1; c<=5; ++c) 
            {
                StdOut.printf("%5.2f",c/x);
            }
        }
StdOut.println();
    }
}

