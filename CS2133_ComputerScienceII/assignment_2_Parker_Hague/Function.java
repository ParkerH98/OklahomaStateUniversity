package CS2133.assignment_2_Parker_Hague;

public abstract class Function {
    public static void main(String[] args) {
        double epsilon = 0.00000001;

        SinFunc sin = new SinFunc();
        System.out.println(sin.findRoot(3, 4, epsilon));


        CosFunc cos = new CosFunc();
        System.out.println(cos.findRoot(1, 3, epsilon));


        int[] aNumbers = {-3, 0, 1};
        PolyFunc a = new PolyFunc(aNumbers);
        System.out.println(a.findRoot(0, 3, epsilon));

        int[] bNumbers = {-2, -1, 1};
        PolyFunc b = new PolyFunc(bNumbers);
        System.out.println(b.findRoot(0, 3, epsilon));
    }
    public abstract double evaluate(double x);

    public double findRoot(double a, double b, double epsilon){
        double x = (a + b) / 2;
        if (Math.abs(a - x) < epsilon){
            return x;
        }
        else if(this.evaluate(x) < 0  && this.evaluate(a) < 0 || this.evaluate(x) > 0 && this.evaluate(a) > 0){
            return findRoot(x, b, epsilon);
        }
        else return findRoot(a, x, epsilon);
    }
}


/**
 * This class serves to calculate many
 * different kinds of functions. Each class
 * has its own evaluate() and is called upon
 * by findRoot(). findRoot() will find the roots
 * of any function because of the implementation 
 * of this.evaluate().
 */