import java.awt.*;
import javax.swing.*;
import javax.swing.border.EmptyBorder;
import java.util.*;

public class MineFrame extends JFrame{
 
    // used for reference
    MineModel model;
    MinePanel panel;
    CountPanel cPanel;
   
    public MineFrame(){
        
        // sets up game frame
        setTitle("Minesweeper");
        Toolkit kit = Toolkit.getDefaultToolkit();
        Dimension screenSize = kit.getScreenSize();
        setSize(screenSize.width / 4, screenSize.height / 2);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setLayout(new BorderLayout());
        this.setLocation(screenSize.width / 4, screenSize.height / 8);


        // created to create gap between frame and panels
        int hSpace = this.getWidth() / 35;
        int vSpace = this.getHeight() / 35;
        Insets space = new Insets(vSpace, hSpace, vSpace, hSpace);
        EmptyBorder border = new EmptyBorder(space);

        // creating panels
        cPanel = new CountPanel(this);
        panel = new MinePanel(this);
        JPanel panelLeft = new JPanel();
        JPanel panelRight = new JPanel();
        JPanel panelBottom = new JPanel();

        // setting background color
        panelLeft.setBackground(Color.RED);
        panelRight.setBackground(Color.RED);
        panelBottom.setBackground(Color.RED);
        cPanel.setBackground(Color.RED);

        // setting spacing
        panelLeft.setBorder(border);
        panelRight.setBorder(border);
        panelBottom.setBorder(border);
        cPanel.setBorder(border);
 
        // setting loaction of panels
        add(panel, BorderLayout.CENTER);
        add(panelLeft, BorderLayout.WEST);
        add(panelRight, BorderLayout.EAST);
        add(cPanel, BorderLayout.NORTH);
        add(panelBottom, BorderLayout.SOUTH);
        
        model = new MineModel();
        setVisible(true);
    }

    public MineModel getModel(){
        return model;
    }
}