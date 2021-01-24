package CS1113.Lab5;

// CS 1113 Lab 4a
// Parker Hague
// 60863
// 10/18/18

public class Triangle
{
    // creates instance variables
    private Vertex[] vertices;
    // creates constructor method with three objects of type Vertex
    public Triangle (Vertex v0, Vertex v1, Vertex v2){
        vertices = new Vertex[3];
        vertices[0] = v0;
        vertices[1] = v1;
        vertices[2] = v2;
    }
    // creates constructor method with double array
    public Triangle(double[][] locations){
        vertices = new Vertex[3];
        vertices[0] = new Vertex(locations[0]);
        vertices[1] = new Vertex(locations[1]);
        vertices[2] = new Vertex(locations[2]);
    }
    // creates accessor method
    public Vertex getVertex(int i){
        return vertices[i];
    }
    // string representation of the triangle
    public String toString(){
        return "T<" +vertices[0]+"," +vertices[1]+"," +vertices[2]+">";
    }
    // draws triangle
    public void draw() {
        double [] x = {vertices[0].getX(),vertices[1].getX(),vertices[2].getX()};
        double [] y = {vertices[0].getY(),vertices[1].getY(),vertices[2].getY()};
        StdDraw.filledPolygon(x,y);
    }
    public static void main(String[] args) {
        Vertex va = new Vertex(1,2);
        Vertex vb = new Vertex(4,2);
        Vertex vc = new Vertex(3,0);
        Triangle a = new Triangle(va,vb,vc);
        double[][] bData = { {0.1,0.1},{.9,.1},{0.5,.9}};
        Triangle b = new Triangle(bData);
        StdOut.println("a = " + a);
        StdOut.println("b = " + b);
        StdOut.println("a.getVertex(0) = " + a.getVertex(0));
        StdOut.println("a.getVertex(1) = " + a.getVertex(1));
        StdOut.println("a.getVertex(2) = " + a.getVertex(2));
        b.draw();
        StdDraw.show();
    }   
}
