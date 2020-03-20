import java.util.*;

// TODO set game win or lose
// TODO reveal game on win or lose
// TODO add game timer
// TODO add difficulty options
// TODO add game board size options
// TODO add save game option

// TODO fix flood fill repaint bug


public class MineModel{

    // initial game settings
    static final int NUMBER_OF_SQUARES = 15;
    static final int MINE_PERCENTAGE = 10;
    
    // instance variables
    private int[][] field;
    private int[][] count;
    private int row;
    private int col;
    private boolean[][] revealed;
    private int bombCount;

    // used for generateMineField()
    Random random = new Random();

    // possible states of a cell
    public static final int UNMINED = 1;
    public static final int MINED = 2;
    public static final int FLAGGED_MINED = 3;
    public static final int FLAGGED_UNMINED = 4;
    public static final int REVEALED = 5;
    
    
    // creates and mines game field
    public MineModel(){
        row = NUMBER_OF_SQUARES + 1;
        col = NUMBER_OF_SQUARES + 1; 

        field = new int[row][col];
        count = new int[row][col];
        revealed = new boolean[row][col];
        this.generateMineField();
        this.neighborCount();
        this.setUnrevealed();
        this.bombCount();
    }


    // adds mines to the game field ( field[][] )
    public void generateMineField(){

        for (int row = 1; row < NUMBER_OF_SQUARES + 1; row++){
            for (int col = 1; col < NUMBER_OF_SQUARES + 1; col ++){
                if (random.nextInt(100) < MINE_PERCENTAGE){
                    this.field[row][col] = MINED;
                }
                else this.field[row][col] = UNMINED;
            }
        }
    }


    // returns current state of cell
    public int getStatus(int row, int col){
        return this.field[row][col];
    }


    // gets this.row
    public int getRow(){
        return this.row;
    }


    // gets this.col
    public int getCol(){
        return this.col;
    }

    
    // gets this.count
    public int getCount(int row, int col){
        return this.count[row][col];
    }


    // changes states when stepping on a mine
    public void stepOnto(int row, int col){

        if (this.field[row][col] == UNMINED){
            this.field[row][col] = REVEALED;
        }
    }


    // changes states when planting a flag
    public void plantFlag(int row, int col){
   
        if (this.field[row][col] == UNMINED){
            this.field[row][col] = FLAGGED_UNMINED;
        }
        else if (this.field[row][col] == MINED){
            this.field[row][col] = FLAGGED_MINED;
        }
    }


    // removes flag from cell (when right clicking a flag)
    public void removeFlag(int row, int col){

        if (this.field[row][col] == FLAGGED_UNMINED){
            this.field[row][col] = UNMINED;
        }
        else if (this.field[row][col] == FLAGGED_MINED){
            this.field[row][col] = MINED;
        }
    }


    // counts and stores the number of bombs a square is touching
    public void neighborCount(){

        int count;
        int rowPos;
        int colPos;

        for (int row = 1; row < NUMBER_OF_SQUARES + 1; row++){
            for (int col = 1; col < NUMBER_OF_SQUARES + 1; col ++){
                
                count = 0;
                rowPos = 0;
                colPos = 0;

                for (int i = -1; i < 2; i++){
                    for (int j = -1; j < 2; j++){

                        rowPos = row + i;
                        colPos = col + j;
                        if (inBounds(rowPos, colPos) == true){
                            if (this.field[rowPos][colPos] == MINED){
                                count++;
                            }
                            else continue;
                        }
                        else continue;

                    }
                }
                this.count[row][col] = count;       
            }
        }
    }


    // counts the initial amount of bombs on the board
    public int bombCount(){

        this.bombCount = 0;

        for (int row = 1; row < NUMBER_OF_SQUARES + 1; row++){
            for (int col = 1; col < NUMBER_OF_SQUARES + 1; col ++){
                
                if (this.field[row][col] == MINED) this.bombCount++;
            }
        }

        return this.bombCount;
    }


    // checks if square is in the bounds of the gameboard
    public boolean inBounds(int row, int col){
        
        boolean bounds = true;
        if (row < 1 || row > NUMBER_OF_SQUARES || col < 1 || col > NUMBER_OF_SQUARES){

            bounds = false;
        }

        return bounds;
    }

    // resets all game arrays, counts, and fields
    public void restartGame(){

        this.resetMineField();
        this.resetCount();
        this.setUnrevealed();
        this.bombCount();
    }


    // sets field to UNMINED, then remines field
    public void resetMineField(){

        for (int row = 1; row < NUMBER_OF_SQUARES + 1; row++){
            for (int col = 1; col < NUMBER_OF_SQUARES + 1; col ++){
                this.field[row][col] = UNMINED;
            }
        }
     
        this.generateMineField();
    }

    // resets neighbor count array
    public void resetCount(){

        for (int row = 1; row < NUMBER_OF_SQUARES + 1; row++){
            for (int col = 1; col < NUMBER_OF_SQUARES + 1; col ++){
                this.count[row][col] = 0;
            }
        }
     
       this.neighborCount();
    }

    // sets all cells to unrevealed
    public void setUnrevealed(){

        for (int row = 1; row < NUMBER_OF_SQUARES + 1; row++){
            for (int col = 1; col < NUMBER_OF_SQUARES + 1; col ++){
                
                this.revealed[row][col] = false;
            }
        }
    }


    // gets revealed value of this.revealed
    public boolean getRevealed(int row, int col){
        return this.revealed[row][col];
    }


    // sets this.revealed to true
    public void setRevealed(int row, int col){
        this.revealed[row][col] = true;
    }


    // sets this.revealed to false
    public void setUnrevealed(int row, int col){
        this.revealed[row][col] = false;
    }


    // reveals all neighboring zeros of clicked cell
    public void floodReveal(int row, int col){

        if (inBounds(row, col) ==  false) return;

        if (this.count[row][col] == 0 && this.revealed[row][col] == false){
            setRevealed(row, col);

            floodReveal( row - 1, col - 1);
            floodReveal( row, col - 1);
            floodReveal( row + 1, col - 1);
            floodReveal( row - 1, col);
            floodReveal( row + 1, col);
            floodReveal( row - 1, col);
            floodReveal( row, col + 1);
            floodReveal( row + 1, col + 1);
        }

        else if (this.count[row][col] != 0 && this.revealed[row][col] == false){
            setRevealed(row, col);
        }
        else return;
    }


    // decrements bombCount
    public void decrementBombCount(){
        
        int tempCount = this.bombCount;
        tempCount -= 1;
        this.bombCount = tempCount;
    }


    // increments bombCount
    public void incrementBombCount(){
        
        int tempCount = this.bombCount;
        tempCount += 1;
        this.bombCount = tempCount;
    }


    // gets current bombCount


    public int getBombCount(){
        return this.bombCount;
    }

}           
