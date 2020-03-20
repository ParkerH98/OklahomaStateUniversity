import java.awt.*;
import java.io.Serializable;

import javax.swing.*;
public class CountPanel extends JPanel implements Serializable{

    JLabel bombCount;
    MineFrame frame;

    public CountPanel(MineFrame f){

        frame = f;

        setLayout(new BorderLayout());
        bombCount = new JLabel();
        JLabel label = new JLabel("BOMBS REMAINING: ");
        label.setFont(new Font(Font.SERIF, Font.BOLD, 24));
        bombCount.setFont(new Font(Font.SERIF, Font.BOLD, 24));


        JPanel panelLeft = new JPanel();
        panelLeft.add(label, BorderLayout.NORTH);
        panelLeft.add(bombCount, BorderLayout.CENTER);

   
        add(panelLeft, BorderLayout.CENTER);
    }

    public void paintComponent(Graphics g){

        super.paintComponent(g);
        bombCount.setText(Integer.toString(frame.getModel().getBombCount()));
    }
}