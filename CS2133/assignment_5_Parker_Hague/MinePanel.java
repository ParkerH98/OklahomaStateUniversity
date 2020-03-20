import java.awt.*;
import java.awt.event.*;
import javax.swing.*;
import java.io.Serializable;
import javax.swing.border.EmptyBorder;

public class MinePanel extends JPanel{

    MineFrame frame;
    MineButton buttons;

    public MinePanel(MineFrame f){
        frame = f;
        setLayout(new GridLayout(MineModel.NUMBER_OF_ROWS, MineModel.NUMBER_OF_COLS));

        for (int row = 1; row < MineModel.NUMBER_OF_ROWS + 1; row++){
            for (int col = 1; col < MineModel.NUMBER_OF_COLS + 1; col++){

                buttons = new MineButton(row, col, frame);
                add(buttons);
            }
        }

        Timer timer = new Timer(100, new ActionHandler());
        timer.start();
    }


    public class MineButton extends JButton{

        private int row;
        private int col;
        MineFrame frame;
        ImageIcon icon;
        int count; 
        CountPanel cpanel = new CountPanel(frame);
         
        ImageIcon unrevealed = new ImageIcon("facingDown.png");
        ImageIcon bomb = new ImageIcon("bomb.png");
        ImageIcon boom = new ImageIcon("boom.png");
        ImageIcon flagged = new ImageIcon("flagged.png"); 

        ImageIcon count0 = new ImageIcon("0.png");
        ImageIcon count1 = new ImageIcon("1.png");
        ImageIcon count2 = new ImageIcon("2.png");
        ImageIcon count3 = new ImageIcon("3.png");
        ImageIcon count4 = new ImageIcon("4.png");
        ImageIcon count5 = new ImageIcon("5.png");
        ImageIcon count6 = new ImageIcon("6.png");
        ImageIcon count7 = new ImageIcon("7.png");
        ImageIcon count8 = new ImageIcon("8.png");
        ImageIcon[] countIcons = new ImageIcon[]{count0, count1, count2, count3, count4, count5, count6, count7, count8};
  
    
        public MineButton(int r, int c, MineFrame f){
            frame = f;
            row = r;
            col = c;
            addMouseMotionListener(new MouseHandler());
            addMouseListener(new MouseHandler());
            setIcon(unrevealed);
            setBorder(BorderFactory.createEmptyBorder());
        }


        public void paintComponent(Graphics g){
            super.paintComponent(g);

            count = frame.getModel().getCount(this.row, this.col);
            

            if (frame.getModel().getRevealed(this.row, this.col) == false){
                this.setIcon(unrevealed);
            }

            else if (frame.getModel().getStatus(this.row, this.col) == MineModel.UNMINED || frame.getModel().getStatus(this.row, this.col) == MineModel.REVEALED){

                if (frame.getModel().getRevealed(this.row, this.col) == true){
                    
                    this.setIcon(countIcons[count]);
                }
                else this.setIcon(unrevealed);
            }
            
            else if (frame.getModel().getStatus(this.row, this.col) == MineModel.FLAGGED_UNMINED || frame.getModel().getStatus(this.row, this.col) == MineModel.FLAGGED_MINED){

                this.setIcon(flagged);
            }
            

            //if (frame.getModel().getStatus(this.row, this.col) == MineModel.MINED) this.setIcon(bomb);
              else if (frame.getModel().getStatus(this.row, this.col) == MineModel.MINED){
                if (frame.getModel().getRevealed(this.row, this.col) == true){
                    this.setIcon(boom);
                } 
            } 
        }
    
    
        // contains handlers for buttons clicks
        public class MouseHandler extends MouseAdapter { 
    
            public void mouseClicked(MouseEvent e){
    
                MineButton clicked = (MineButton) e.getSource();
                int clickedRow = clicked.row;
                int clickedCol = clicked.col;

                // handles right clicks
                if (e.getButton() == MouseEvent.BUTTON3){

                    if (frame.getModel().getStatus(clickedRow, clickedCol) == MineModel.FLAGGED_MINED || frame.getModel().getStatus(clickedRow, clickedCol) == MineModel.FLAGGED_UNMINED){

                        frame.getModel().setUnrevealed(clickedRow, clickedCol);
                        frame.getModel().removeFlag(clickedRow, clickedCol);
                        frame.getModel().incrementBombCount();
                        frame.repaint();
                    }

                    else {

                        frame.getModel().setRevealed(clickedRow, clickedCol);

                        // updates state in MineModel
                        frame.getModel().plantFlag(clickedRow, clickedCol);
                        frame.getModel().decrementBombCount();
                        cpanel.repaint();
                    }
                   
                }

                // handles left clicks
                else if (e.getButton() == MouseEvent.BUTTON1){
                    
                    // restarts game if stepped on mine
                    if (frame.getModel().getStatus(clickedRow, clickedCol) == MineModel.MINED){

                        frame.getModel().setRevealed(clickedRow, clickedCol);
                        frame.getModel().revealAll();
                        try {

                            JOptionPane.showMessageDialog(frame, "You stepped on a mine. \n \n GAME OVER!", "GAME OVER", JOptionPane.OK_OPTION);

                        } catch (HeadlessException ex) {
                            
                        }

                        frame.getModel().revealAll();
                        frame.getModel().restartGame();
                        frame.repaint();
                        frame.validate();
                    }

                    else if (frame.getModel().getStatus(clickedRow, clickedCol) == MineModel.UNMINED){

                        frame.getModel().floodReveal(clickedRow, clickedCol);
                        frame.getModel().setRevealed(clickedRow, clickedCol);
                        frame.repaint();
                        frame.validate();
                    }

                    // updates state in MineModel
                    frame.getModel().stepOnto(clickedRow, clickedCol);
                    frame.repaint();
                    frame.validate();
                }  

                frame.repaint();
                frame.validate();
            }
        }
    }

    private class ActionHandler implements ActionListener{

		@Override
		public void actionPerformed(ActionEvent e) {
        repaint();
		}
        
    }
}