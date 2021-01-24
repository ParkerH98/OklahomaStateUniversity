package geography;
import java.util.ArrayList;

/** 
 * This class serves as a blueprint for a
 * Country object. A country object is what the real life perception of 
 * a country is.
 */
public class Country implements GeoCalculate, Boundry{ 

	private String name;
	private String capital;
	private ArrayList<State> states;
	private ArrayList<Boundry> boundries;
	private ArrayList<String> neighbors;
	private double area;
	private double population;


	/** 
	 * A constructor for a Country object.
	 * @param name is a Country's name
	 */
	public Country(String name) {
	
		this.name = name;
	}


	/** 
	 * A constructor for a Country object. This constructor 
	 * has the ability to pass in an array of states
	 * along with the name.
	 * @param name is a country's name
	 * @param states is an ArrayList of states that make up a country
	 * @see State
	 */
	public Country(String name, ArrayList<State> states) {
		this.name = name;
		this.states = states;
	}


	/** 
	 * Gets a list of states that make up a country
	 * @return an ArrayList of states
	 */
	public ArrayList<State> getStates(){
		return states;
	}


	/** 
	 * Sets an ArrayList of states to a country.
	 * The states are meant to be the states that
	 * make up a country.
	 * @param states is an ArrayList of states that makes up a country
	 */
	public void setStates(ArrayList<State> states){
		this.states = states;
	}


	/** 
	 * Searches for a state in an ArrayList of states
	 * @param state a String value of a state
	 * @return a State object of the searched state 
	 */
	public State findState(String state){
		return null;
	}


	/** 
	 * Adds a state to an ArrayList of states
	 * @param state a State object of the state intended to be added
	 */
	public void addState(State state){
		this.states.add(state);
	}


	/** 
	 * Removes a state from an ArrayList of states
	 * @param state the State object intended to be removed
	 */
	public void removeState(State state){
		this.states.remove(state);
	}


	/** 
	 * Gets the capital of the country
	 * @return a string value of the country's capital
	 */
	public String getCapital(){
		return this.capital;
	}


	/** 
	 * Sets a capital to the country
	 * @param capitalName is a string value of the capital intended to be set
	 */
	public void setCapital(String capitalName){
		this.capital = captialName;
	}


	/** 
	 * Gets the name of the country
	 * @return returns the name of the country
	 */
	public String getName(){
		return this.name;
	}


	/** 
	 * Gets the population of the country
	 * @return returns a double value of the country's population
	 */
	public double getPopulation(){
		return this.population;
	}


	/** 
	 * Sets a population to a country
	 * @param population is a double value of a country's population
	 */
	public void setPopulation(double population){
		this.population = population;
	}


	/** 
	 * Adds a city to a country's ArrayList of cities
	 * @param city is the City object that you wish to add
	 * @param state is the State that contains the given city
	 */
	public void addCity(City city, State state){
		// adds a city to the ArrayList
	}


	/**  
	 * Sets a boundry's length
	 * @return a double value of a boundry's length
	 */
	public void setBoundryLength(){ 
		 // sum of boundries
	}


	/** 
	 * Gets a boundry's length
	 * @return a double value of a boundry's length
	 */
	public double getBoundryLength(){ 
		return 1;
	}

	/** 
	 * Gets a list of all of a country's boundries
	 * @return an ArrayList of Boundries
	 */
	public ArrayList<Boundry> getBoundries(){
		return this.boundries;
	}


	/** 
	 * Sets an ArrayList of strings to a country's neighbors
	 * @param neighbors are an ArrayList of Strings that are neighbors
	 */
	public void setNeighbors(ArrayList<String> neighbors){
		// sets a list of neighbors that touch a country
	}

	/** 
	 * Gets an ArrayList of a country's neighbors
	 * @return an ArrayList of neighbors
	 */
	public ArrayList<String> getNeighbors(){
		return this.neighbors;
	}


	/** 
	 * Calculates a country's area
	 * @return a double value of a country's area
	 */
	public double area(){
		return area; // length x width. Could find distance between boundries to calculate
	}



	/** 
	 * Calculates the distance between two countries
	 * @param country_1 is the first country being measured
	 * @param country_2 is the second country being measured 
	 * @return the distance between two countries
	 */
	public double distanceBetween(Country country_1, Country country_2){
		return 1; // use general distance formula from middle school math
	}
}
