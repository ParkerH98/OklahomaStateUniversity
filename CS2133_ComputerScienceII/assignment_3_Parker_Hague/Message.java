import java.awt.*;
import javax.swing.*;
public class Message extends JFrame{
    public static void main(String[] args) {
        new Message();
    }

    public Message(){
        setTitle("Message in a Bottle");
        Toolkit kit = Toolkit.getDefaultToolkit();
        Dimension screenSize = kit.getScreenSize();
        setSize(screenSize.width / 2, screenSize.height / 2);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        MessagePanel panel = new MessagePanel();
        add(panel);
        setVisible(true);
    }
}