import java.awt.*;
import javax.swing.*;

public class BrowserFrame extends JFrame{

    public BrowserModel model;
    public BrowserPanel panel;

    public BrowserFrame(){

        setTitle("Browser");
        Toolkit kit = Toolkit.getDefaultToolkit();
        Dimension screenSize = kit.getScreenSize();
        setSize(screenSize.width / 2 , screenSize.height / 2);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

        model = new BrowserModel();
        panel = new BrowserPanel(this);
      
        add(panel);
        setVisible(true);
    }

    public BrowserModel getModel(){
        return model;
    }
}