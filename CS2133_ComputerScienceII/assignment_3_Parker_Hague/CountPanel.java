import java.awt.*;
import javax.swing.*;
public class CountPanel extends JPanel{

    JLabel bombCount;
    MineFrame frame;

    public CountPanel(MineFrame f){

        frame = f;

        setLayout(new BorderLayout());
        bombCount = new JLabel();
        JLabel label = new JLabel("Bombs Remaining: ");


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