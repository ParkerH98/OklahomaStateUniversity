import java.awt.*;
import javax.swing.*;
public class MessagePanel extends JPanel{

    Toolkit kit = Toolkit.getDefaultToolkit();
    Dimension screenSize = kit.getScreenSize();
    int quarterWidth = screenSize.width / 4;
    int quarterHeight = screenSize.height / 4;

    public static void main(String[] args) {
        MessagePanel m = new MessagePanel();
        System.out.println(m.quarterWidth);
        System.out.println(m.quarterHeight);
    }
 
    public void paintComponent(Graphics g){
        super.paintComponent(g);
        g.drawOval(300, 300 , 50, 25); // top
        g.drawLine(300, 311 , 300, 350); // left line
        g.drawLine(350, 311, 350, 350); // right line
        g.drawLine(300, 350, 250, 350); // top-left line
        g.drawLine(350, 350, 400, 350); // top-right line
        g.drawLine(250, 350, 250, 550); // left-side line
        g.drawLine(400, 350, 400, 550); // right-side line
        g.drawLine(250, 550, 400, 550); // bottom line
        g.drawString("CS is the reason I drink.", 250, 450);
    }
}