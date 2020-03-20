package geography;



/** 
 * This class serves as a blueprint for a
 * River object. A River object is what the real life perception of 
 * a river is.
 */




public class River{

  private String name;
  private double riverLength;


  /** 
   * Constructor for a River object.
   * @param name is a river's name
   * @param length is a double value of a river's length
   */
  public River(String name, double length){

    this.name = name;
    this.riverLength = length;
  }


  /** 
   * Gets a river's name
   * @return a String value of a river's name
   */
  public String getName(){
    return name;
  }


  /** 
   * Sets the name of a river
   * @param name is a name of a river
   */
  public void setName(String name){

    this.name = name;
  }


  /**  
   * Gets the length of a river
   * @return a double value of a river's length
   */
  public double getRiverLength(){

    return this.riverLength;
  }


  /** 
   * Sets the length of a river
   * @param riverLength is the length of a river
   */
  public void setLength(double riverLength){

    this.riverLength = riverLength;
  }
}