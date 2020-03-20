import java.awt.*;
import javax.swing.*;
import javax.swing.border.EmptyBorder;
import java.awt.event.*;
import java.io.*;

public class MineFrame extends JFrame{
 
    // used for reference
    MineModel model;
    MinePanel panel;
    CountPanel cPanel;

    JMenuItem beginnerDifficulty;
    JMenuItem intermediateDifficulty;
    JMenuItem expertDifficulty;
    JMenuItem saveFile;
    JMenuItem loadFile;
    JMenuItem quit;
    JFileChooser fileChooser;

    static Toolkit kit;
    static Dimension screenSize;
 
    public MineFrame(MineModel savedGame){
        
        // sets up game frame
        setTitle("Minesweeper");
        kit = Toolkit.getDefaultToolkit();
        pack();
        screenSize = kit.getScreenSize();
        setSize(screenSize.width / MineModel.getScreenWidth(), screenSize.height / MineModel.getScreenHeight());
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setLayout(new BorderLayout());
        this.setLocation(screenSize.width / 4, screenSize.height / 8);
 

        // created to create gap between frame and panels
        int hSpace = this.getWidth() / 35;
        int vSpace = this.getHeight() / 35;
        Insets space = new Insets(vSpace, hSpace, vSpace, hSpace);
        EmptyBorder border = new EmptyBorder(space);

        // creating components
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

   

        JMenuBar menuBar = new JMenuBar();

        JMenu fileMenu = new JMenu("File");
        JMenu newGameMenu = new JMenu("New Game");

        saveFile = new JMenuItem("Save Game");
        loadFile = new JMenuItem("Load Game");
        quit = new JMenuItem("Quit Game");

        beginnerDifficulty = new JMenuItem("Beginner");
        intermediateDifficulty = new JMenuItem("Intermediate");
        expertDifficulty = new JMenuItem("Expert");

        setJMenuBar(menuBar);
        menuBar.add(fileMenu);

        fileMenu.add(newGameMenu);
        fileMenu.addSeparator();
        fileMenu.add(saveFile);
        fileMenu.addSeparator();
        fileMenu.add(loadFile);
        fileMenu.addSeparator();
        fileMenu.add(quit);

        newGameMenu.add(beginnerDifficulty);
        newGameMenu.addSeparator();
        newGameMenu.add(intermediateDifficulty);
        newGameMenu.addSeparator();
        newGameMenu.add(expertDifficulty);

        beginnerDifficulty.addActionListener(new MenuHandler());
        intermediateDifficulty.addActionListener(new MenuHandler());
        expertDifficulty.addActionListener(new MenuHandler());
        saveFile.addActionListener(new MenuHandler());
        loadFile.addActionListener(new MenuHandler());
        quit.addActionListener(new MenuHandler());


        model = new MineModel();
        setVisible(true);
    }

    public MineModel getModel(){
        return model;
    }



    private class MenuHandler implements ActionListener{

		@Override
		public void actionPerformed(java.awt.event.ActionEvent e) { 
            
            if (e.getSource() == beginnerDifficulty){
                dispose();
                getModel().setBeginner();
                new MineFrame(null);    
			}
			else if (e.getSource() == intermediateDifficulty){
				dispose();
                getModel().setIntermediate();
                new MineFrame(null);
			}
			else if (e.getSource() == expertDifficulty){
                dispose();
                getModel().setExpert();
                new MineFrame(null);
            }

            else if (e.getSource() == saveFile) {
                fileChooser = new JFileChooser();
				if (fileChooser.showSaveDialog(null) == JFileChooser.APPROVE_OPTION){ 
					try {
						ObjectOutputStream out = new ObjectOutputStream(new FileOutputStream(fileChooser.getSelectedFile()));

                        out.writeObject(model);
                        
						out.flush();
						out.close();
					}
					catch(IOException ex) {
						ex.printStackTrace();
					}
				}
				else{}
			}

            else if (e.getSource() == loadFile){
                fileChooser = new JFileChooser();
				if (fileChooser.showOpenDialog(null) == JFileChooser.APPROVE_OPTION){
					try {
						ObjectInputStream in = new ObjectInputStream(new FileInputStream(fileChooser.getSelectedFile()));
                       
                        model = (MineModel)in.readObject();
                        
					}
					catch(IOException ex){
						System.out.println("ERROR: could not read save.");
					}
					catch(ClassNotFoundException ex){
						System.out.println("ERROR: file is not a valid save file.");
					}
				}
				else{}
			}
            
            else if (e.getSource() == quit){
                System.exit(0);
            }
		}
    }
}