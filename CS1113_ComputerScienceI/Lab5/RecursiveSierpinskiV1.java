package CS1113.Lab5;

// CS 1113 Lab 4a
// Parker Hague
// 60863
// 10/18/18

public class RecursiveSierpinskiV1
{
    public static void drawSierpinski(int order, Triangle T){
        if (order == 0){
             T.draw();
        }
        else{
            // creates midpoints
            Vertex m01 = Vertex.affineSum(0.5, T.getVertex(0),0.5, T.getVertex(1));
            Vertex m02 = Vertex.affineSum(0.5, T.getVertex(1),0.5, T.getVertex(2));                
            Vertex m03 = Vertex.affineSum(0.5, T.getVertex(2),0.5, T.getVertex(0));

            drawSierpinski(order-1,new Triangle(T.getVertex(0), m01,m03));
            drawSierpinski(order-1,new Triangle(T.getVertex(1), m02,m01));  
            drawSierpinski(order-1,new Triangle(T.getVertex(2), m03,m02));
        }   
    }
    public static void main(String[] args) {
        int n = Integer.parseInt(args[0]);
        double s = Math.sqrt(3)/2;
        double[][] initTData = { {-s,-0.5},{s,-0.5},{0.0,1} };
        Triangle T = new Triangle(initTData);
        StdDraw.setCanvasSize(600,600);
        StdDraw.setYscale(-1,1.0);
        StdDraw.setXscale(-1,1.0);
        StdDraw.setPenColor(StdDraw.BLUE);
        drawSierpinski(n,T);
    }
}