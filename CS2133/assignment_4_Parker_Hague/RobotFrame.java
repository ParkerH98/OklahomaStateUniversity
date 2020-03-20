import java.awt.*;
import javax.swing.*;

public class RobotFrame extends JFrame{

    public RobotPanel panel;

    public RobotFrame(){

        setTitle("Robot Controller");
        Toolkit kit = Toolkit.getDefaultToolkit();
        Dimension screenSize = kit.getScreenSize();
        setSize(screenSize.width / 2 , screenSize.height / 2);
        
        panel = new RobotPanel();
        add(panel);

        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setVisible(true);

    }
}