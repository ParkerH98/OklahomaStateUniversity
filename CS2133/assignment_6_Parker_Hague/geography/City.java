package geography;
import java.util.ArrayList;

/** 
 * This class serves as a blueprint for a
 * City object. A City object is what the real life perception of 
 * a city is.
 * @see State
 * @see Country
 */

public class City extends State implements GeoCalculate, Boundry{ 

    private String name;
	private String stateCapital;
    private Country country;
    private State state;
	private double area;
	private double population;


	/** 
	 * Constructor for City.
	 * @param name is the name of a city
	 */
    public City(String name) {
        super(name);
        
    }


	/**
	 * A constructor for city that also inccludes the option 
	 * to put a name and an area.
	 * @param name is the name of a city
	 * @param area is a city's area
	 */
    public City(String name, double area){
        super(name);
        this.name = name;
        this.area = area;
    }


	/** 
	 * Returns a state's capital
	 * @return the state's capital
	 */
	public String getCapital(){
		return this.stateCapital;
	}


	/** 
	 * Sets a city's capital
	 * @param capitalName is the name of a city's capital
	 */
	public void setCapital(String capitalName){
		this.stateCapital = capitalName;
	}


	/** 
	 * Returns a city's name
	 * @return a state's name
	 */
	public String getName(){
		return this.name;
	}


	/** 
	 * Gets a city's population
	 * @return a city's population
	 */
	public double getPopulation(){
		return this.population;
	}


	/** 
	 * Sets a city's population
	 * @param population is the numerical value of a city's population
	 */
	public void setPopulation(double population){
		this.population = population;
	}


	/** 
	 * Looks through an ArrayList of rivers and returns if the river exists
	 * @param riverName is a String value of a river's name
	 */
	public void searchRiver(String riverName) {
		//find river by name
    }
    

	/** 
	 * Gets a city's country
	 * @return the country of the city
	 */
	public Country getCountry() {
		return country;
	}


	/**  
	 * Sets the country of the city
	 * @param country is a city's country
	 */
	public void setCountry(Country country) {
		this.country = country;
    }
    

	/** 
	 * Returns the state of the city
	 * @return a city's state
	 */
    public State getState() {
		return state;
	}


	/** 
	 * Sets a city's state
	 * @param state is a city's state
	 */
	public void setState(State state) {
		this.state = state;
	}

    /** 
	 * Returns the length of a boundry
	 * @return a boundry length
	 */
	public double boundryLength(){ 
		return 1;
		// could use the distance formula with two different (x, y) points
    }


	/** 
	 * Calculates the area of a city
	 * @return the area of a city
	 */
	public double area(){
		return area; // length x width. Could find distance between boundries to calculate
	}


	/** 
	 * Calculates the distance between two cities
	 * @param city_1 is one of two cities being measured
	 * @param city_2 is the second city being measured
	 * @return the distance between two cities
	 */
	public double distanceBetween(City city_1, City city_2){
		return 1; // use general distance formula from middle school math
	}
} 