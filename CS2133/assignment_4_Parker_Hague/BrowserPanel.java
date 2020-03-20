import java.awt.*;
import java.awt.event.*;
import javax.swing.*;

public class BrowserPanel extends JPanel implements KeyListener{
    

    BrowserFrame frame;
    JTextField addressField;
    JTextArea display;
    JScrollPane scroller;

    public BrowserPanel(BrowserFrame f){

        frame = f;

        setLayout(new BorderLayout());

        addressField = new JTextField("Type in URL");
        display = new JTextArea();

        add(addressField, BorderLayout.NORTH);
        add(display, BorderLayout.CENTER);
       
        addressField.addKeyListener(this);
        display.setEditable(false);
        display.setLineWrap(true);

        scroller = new JScrollPane(display);
        add(scroller);
    }

    public void paintComponent(Graphics g){
        super.paintComponent(g);
        display.setText(BrowserModel.getBody(BrowserModel.webText));
        frame.setTitle(BrowserModel.getTitle(BrowserModel.webText));
        
    }


    public void addNotify(){
        super.addNotify();
        requestFocus();
    }


    @Override
    public void keyPressed(KeyEvent e){

        if (e.getKeyCode() == KeyEvent.VK_ENTER){
            
            String URL = addressField.getText();

            BrowserModel.getHost(URL);
            BrowserModel.getFilePath(URL, BrowserModel.host);
            BrowserModel.sendURL(BrowserModel.filePath, BrowserModel.host);
        }
        repaint();
    }


    @Override
    public void keyTyped(KeyEvent e) {}


    @Override
    public void keyReleased(KeyEvent e) {}
}