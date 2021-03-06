package CS1113.Lab5;

// CS 1113 Lab 4a
// Parker Hague
// 60863
// 10/18/18

public class RecursiveSierpinskiV2
{
    // declares instance variable;
    private Triangle[] leafTriangles;
    // delcares counter
    private int nextT;
    // draws the array of triangles
    public RecursiveSierpinskiV2 (int order, Triangle T){
        nextT = 0;
        leafTriangles = new Triangle[(int) Math.pow(3,order)];
        build(order,T); 
    }
    // creates triangles and stores in array
    private void build(int order, Triangle T){
        if (order == 0) {
            leafTriangles[nextT] = T;
            nextT++;
            return;
        }
        else{
            // creates midpoints
            Vertex m01 = Vertex.affineSum(0.5, T.getVertex(0),0.5, T.getVertex(1));
            Vertex m02 = Vertex.affineSum(0.5, T.getVertex(1),0.5, T.getVertex(2));                
            Vertex m03 = Vertex.affineSum(0.5, T.getVertex(2),0.5, T.getVertex(0));

            build(order-1,new Triangle(T.getVertex(0), m01,m03));
            build(order-1,new Triangle(T.getVertex(1), m02,m01));            
            build(order-1,new Triangle(T.getVertex(2), m03,m02));
        }
    }
    // draws each triangle i
    public void draw() {
        for (int i=0; i  < leafTriangles.length; ++i) {
           leafTriangles[i].draw();
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
        StdDraw.enableDoubleBuffering();
        RecursiveSierpinskiV2 rs = new RecursiveSierpinskiV2(n,T);
        rs.draw();
        StdDraw.show();
    }
}