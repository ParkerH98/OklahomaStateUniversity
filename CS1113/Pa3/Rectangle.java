// CS 1113 Pa3
// Parker Hague
// 60863
// 11/18/18

public class Rectangle
{
   private final double x, y;    // center of rectangle
   private final double width;   // width of rectangle
   private final double height;  // height of rectangle

   private double x1;
   private double x2;
   private double x3;
   private double x4;

   private double y1;
   private double y2;
   private double y3;
   private double y4;

   private double [] xCo = new double[4]; // stores x coords.
   private double [] yCo = new double[4]; // stores y coords.

   public Rectangle(double x0, double y0, double w, double h){
      x = x0;
      y = y0;
      width = w;
      height = h;


      x1 = x0 - (width / 2);
      x2 = x0 + (width / 2);
      x3 = x0 - (width / 2);
      x4 = x0 + (width / 2);

      y1 = y0 - (height / 2);
      y2 = y0 - (height / 2);
      y3 = y0 + (height / 2);
      y4 = y0 + (height / 2);

      xCo[0] = x1;
      xCo[1] = x2;
      xCo[2] = x4;
      xCo[3] = x3;
      yCo[0] = y1;
      yCo[1] = y2;
      yCo[2] = y4;
      yCo[3] = y3;        
   }

   public double area(){
    return width * height;
   }

   public double perimeter(){
    return (height * 2) + (width * 2);
   }

   public boolean intersects(Rectangle b){
       if (b.y1 < y3 || b.x1 > x2 || b.y2 > y1 || b.x2 < x1){
           return false;
       }
       else{
           return true;
       }
   }

   public boolean contains(Rectangle b){
      if (b.x1 >= x1 && b.x2 <= x2 && b.y1 <= y1 && b.y3 >=y3){
          return true;
      }
      else{
          return false;
      }
   }

   public void draw(boolean filled){
       if (filled == true){
           StdDraw.filledPolygon(xCo, yCo);
       }
       else{
           StdDraw.polygon(xCo, yCo);
       }
   }

   public String toString(){
        return "Rectangle<("+x+", "+y+"), "+width +", "+height+">";
   }


    public static void main(String[] args) {
        System.out.println("Pa3 for Example Solution, Lab CRN 60863");
        Rectangle a = new Rectangle(0.5, 0.5, 0.2, 0.4);
        Rectangle b = new Rectangle(0.2, 0.6, 0.2, 0.6);
        Rectangle c = new Rectangle(0.65, 0.5, 0.2, 0.2);
        Rectangle d = new Rectangle(0.5, 0.4, 0.1, 0.1);
        StdOut.println(a.intersects(b));
        StdOut.println(a.intersects(c));
        StdOut.println(a.intersects(d));
        StdOut.println(c.intersects(b));
        StdOut.println(c.intersects(d));
        StdOut.println(a.contains(b));
        StdOut.println(a.contains(d));
        StdOut.println("area of a :" + a.area());
        StdOut.println("perimeter of b :" + b.perimeter());
        a.draw(false);
        b.draw(false);
        c.draw(false);
        d.draw(false);
    }
}