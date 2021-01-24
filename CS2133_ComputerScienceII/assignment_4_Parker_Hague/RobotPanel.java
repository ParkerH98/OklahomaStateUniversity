import javax.swing.*;
import java.awt.*;
import java.awt.event.*;

public class RobotPanel extends JPanel{


    public JLabel linearVelocity;
    public JLabel angularVelocity;

    public RobotPanel() {

        setLayout(new GridLayout(8, 3));

        JButton takeoffButton = new JButton("TAKEOFF");
        JButton landButton = new JButton("LAND");
        JButton forwardButton = new JButton("FORWARD");
        JButton backwardButton = new JButton("BACKWARD");
        JButton ascendButton = new JButton("ASCEND");
        JButton descendButton = new JButton("DESCEND");
        JButton leftButton = new JButton("LEFT");
        JButton rightButton = new JButton("RIGHT");
        JButton turnLeftButton = new JButton("TURN LEFT");
        JButton turnRightButton = new JButton("TURN RIGHT");
        
        linearVelocity = new JLabel();
        angularVelocity = new JLabel();
        JButton increaseAngularVelocityButton = new JButton("INCREASE ANGULAR VELOCITY");
        JButton decreaseAngularVelocityButton = new JButton("DECREASE ANGULAR VELOCITY");
        JButton increaseLinearVelocityButton = new JButton("INCREASE LINEAR VELOCITY");
        JButton decreaseLinearVelocityButton = new JButton("DECREASE LINEAR VELOCITY");

        add(landButton);
        add(new JLabel());
        add(takeoffButton);
        add(new JLabel());
        add(ascendButton);
        add(new JLabel());
        add(leftButton);
        add(new JLabel());
        add(rightButton);
        add(new JLabel());
        add(descendButton);
        add(new JLabel());
        add(backwardButton);
        add(new JLabel());
        add(forwardButton);
        add(turnLeftButton);
        add(new JLabel());
        add(turnRightButton);
        add(increaseLinearVelocityButton);
        add(linearVelocity);
        add(decreaseLinearVelocityButton);
        add(increaseAngularVelocityButton);
        add(angularVelocity);
        add(decreaseAngularVelocityButton);


        takeoffButton.addActionListener(new ButtonHandler());
        landButton.addActionListener(new ButtonHandler());
        forwardButton.addMouseListener(new MouseHandler());
        backwardButton.addMouseListener(new MouseHandler());
        ascendButton.addMouseListener(new MouseHandler());
        descendButton.addMouseListener(new MouseHandler());
        leftButton.addMouseListener(new MouseHandler());
        rightButton.addMouseListener(new MouseHandler());
        turnLeftButton.addMouseListener(new MouseHandler());
        turnRightButton.addMouseListener(new MouseHandler());
        increaseLinearVelocityButton.addActionListener(new ButtonHandler());
        decreaseLinearVelocityButton.addActionListener(new ButtonHandler());
        increaseAngularVelocityButton.addActionListener(new ButtonHandler());
        decreaseAngularVelocityButton.addActionListener(new ButtonHandler());
    }

    public void paintComponent(Graphics g){

        super.paintComponent(g);
        linearVelocity.setText(RobotModel.getLinVelocity());
        angularVelocity.setText(RobotModel.getAngVelocity());
    }


    private class ButtonHandler implements ActionListener{

        @Override
        public void actionPerformed(ActionEvent e) {
            

            String button = e.getActionCommand();

            if (button.equals("TAKEOFF")){
                RobotModel.takeoff();
            }
            else if (button.equals("LAND")){
				RobotModel.land();
            }
            else if (button.equals("INCREASE LINEAR VELOCITY")) {
				RobotModel.increaseLinearVelocity();
			}
			else if (button.equals("DECREASE LINEAR VELOCITY")) {
				RobotModel.decreaseLinearVelocity();
			}
			else if (button.equals("INCREASE ANGULAR VELOCITY")) {
				RobotModel.increaseAngularVelocity();
			}
			else if (button.equals("DECREASE ANGULAR VELOCITY")) {
				RobotModel.decreaseAngularVelocity();
            }
            
            repaint();
        }
    }


    private class MouseHandler extends MouseAdapter implements MouseListener{

        public void mousePressed(MouseEvent e){

            JButton button = (JButton)(e.getSource());

            if (button.getActionCommand().equals("FORWARD")) {
                RobotModel.forward();
            }
            else if (button.getActionCommand().equals("BACKWARD")) {
				RobotModel.backward();
            }
            else if (button.getActionCommand().equals("ASCEND")) {
				RobotModel.ascend();
            }
            else if (button.getActionCommand().equals("DESCEND")) {
				RobotModel.descend();
            }
            else if (button.getActionCommand().equals("LEFT")) {
				RobotModel.left();
            }
            else if (button.getActionCommand().equals("RIGHT")) {
				RobotModel.right();
			}
			else if (button.getActionCommand().equals("TURN LEFT")) {
				RobotModel.turnLeft();
			}
			else if (button.getActionCommand().equals("TURN RIGHT")) {
				RobotModel.turnRight();
            }	
            
            repaint();
        }


        public void mouseReleased(MouseEvent e){

            JButton button = (JButton)(e.getSource());

            if (!button.getActionCommand().equals(null)){
                RobotModel.stop();
                System.out.println("released");
            }

            repaint();
        }
    }
}