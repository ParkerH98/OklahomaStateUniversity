import java.awt.*;
import javax.swing.*;
public class Sierpinski extends JFrame{
    public static void main(String[] args) {
        new Sierpinski();
    }

    public Sierpinski(){
        setTitle("Sierpinski");
        Toolkit kit = Toolkit.getDefaultToolkit();
        Dimension screenSize = kit.getScreenSize();
        setSize(screenSize.width / 2, screenSize.height / 2);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        SierpinskiPanel sP = new SierpinskiPanel();
        add(sP);
        setVisible(true);
    }
}