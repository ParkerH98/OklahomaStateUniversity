import java.io.Serializable;

public class MineSave implements Serializable{

  MineFrame frame;
  private int[][] field;
  private int[][] count;
  private boolean[][] revealed;
  private int bombCount;
  private MineModel model;

  public int NUMBER_OF_ROWS = 9;
  public int NUMBER_OF_COLS = 9;
  public int MINE_PERCENTAGE = 12;
  public int screenWidth = 4;
  public int screenHeight = 2;

  public MineSave(){

    /* setNumRows(MineModel.NUMBER_OF_ROWS);
    setNumCols(MineModel.NUMBER_OF_COLS);
    setMinePerc(MineModel.MINE_PERCENTAGE);
    setScreenW(MineModel.screenWidth);
    setScreenH(MineModel.screenHeight);

    field = model.getField();
    count = model.getCount();
    revealed = model.getRevealed();
    bombCount = model.getBombCount(); */

    model = frame.getModel();
  }
 

  public void setNumRows(int NUMBER_OF_ROWS) {
    this.NUMBER_OF_ROWS = NUMBER_OF_ROWS;
  }
       
    
  public void setNumCols(int NUMBER_OF_COLS) {
    this.NUMBER_OF_COLS = NUMBER_OF_COLS; 
  }
      
    
  public void setMinePerc(int MINE_PERCENTAGE) {
    this.MINE_PERCENTAGE = MINE_PERCENTAGE;
  }
      
    
  public void setScreenW(int screenWidth) {
      this.screenWidth = screenWidth;
  }
      
    
  public void setScreenH(int screenHeight) {
    this.screenHeight = screenHeight;
  }
}