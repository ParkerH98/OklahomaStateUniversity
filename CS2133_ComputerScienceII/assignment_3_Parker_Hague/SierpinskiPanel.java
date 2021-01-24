import java.awt.*;
import javax.swing.*;

public class SierpinskiPanel extends JPanel{

    public void paintComponent(Graphics g){
        super.paintComponent(g);
        drawSierpinski(g, 0, 0, squareWidth());
        repaint();
    }

    public void drawSierpinski(Graphics g, int x, int y, int width){

        if (width == 1){
            g.drawRect(x, y, 1, 1);
        }

        else{
            //recursion
            drawSierpinski(g, x, y + (width / 2), width / 2); // lower left
            drawSierpinski(g, x + (width / 2), y + (width / 2), width / 2); // lower right
            drawSierpinski(g, x + (width / 4), y, width / 2); // top
        }
    }
     
    private int squareWidth(){
        int w = getWidth();
        int h = getHeight();
        int squareWidth;
        if (w < h){
            squareWidth = w;
        }
        else squareWidth = h;
        return squareWidth;
    }
}