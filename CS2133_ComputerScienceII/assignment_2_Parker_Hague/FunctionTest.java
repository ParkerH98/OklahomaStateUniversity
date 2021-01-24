package CS2133.assignment_2_Parker_Hague;

public class FunctionTest {
    public static void main(String[] args) {   
        double epsilon = 0.00000001;
        System.out.println(findRoot(3, 4, epsilon)); // prints root of sin
    }

    public static double findRoot(double a, double b, double epsilon){
        double x = (a + b) / 2;
        if (Math.abs(a - x) < epsilon){
            return x;
        }
        else if(Math.sin(x) < 0  && Math.sin(a) < 0 || Math.sin(x) > 0 && Math.sin(a) > 0){
            return findRoot(x, b, epsilon);
        }
        else return findRoot(a, x, epsilon);
    }
}