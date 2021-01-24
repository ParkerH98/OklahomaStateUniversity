package CS1113.Lab5;

// CS 1113 Lab 4a
// Parker Hague
// 60863
// 10/18/18

public class Vertex {
    // delcaring instance variables
    private double x;
    private double y;

    // creating constructor method
    public Vertex(double x, double y){
        this.x = x;
        this.y = y;
    }
    // creating constructor method
    public Vertex(double[] location){
        x = location[0];
        y = location[1];
    }
    // creates accessor method
    public double getX(){
        return x;
    }
    // creates accessor method
    public double getY(){
        return y;
    }
    // creates string representation method
    public String toString(){
        return "(" + x + "," + y + ")";
    }
    // creates method to change the existing values of the Vertex
    public void set(double x, double y){
        this.x = x;
        this.y = y;
    }
    // affine sum method
    public static Vertex affineSum(double wa, Vertex a, double wb, Vertex b){
        double first = wa * a.getX() + wb * b.getX();
        double second = wa * a.getY() + wb * b.getY();
        Vertex sum = new Vertex(first, second);
        return sum;
        
    }    public static void main(String[] args) {
        Vertex a = new Vertex(1,0);
        double[] bData = {.5,1};
        Vertex b = new Vertex(bData);
        StdOut.println("a = " + a);
        StdOut.println("b = " + b);
        StdOut.println("b.getX() = " + b.getX() +", b.getY() = "+b.getY());
        Vertex c = affineSum(.25,a,.75,b);
        StdOut.println("c = affineSum(.25,a,.75,b); c  =  " + c);
        b.set(5.0,2.0);
        StdOut.println("b = " + b);
    }
}