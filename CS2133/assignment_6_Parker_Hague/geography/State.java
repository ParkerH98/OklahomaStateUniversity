package geography;
import java.util.ArrayList;


/** 
 * This class serves as a blueprint for a
 * State object. A State object is what the real life perception of 
 * a state is.
 * @see Country
 */


public class State extends Country implements GeoCalculate{

	private String name;
	private String capital;
	private Country country;
	private ArrayList<City> cities;
	private ArrayList<River> rivers;
	private ArrayList<Boundry> boundries;
	private ArrayList<String> neighbors;
	private double area;
	private double population;


	/**  
	 * A constructor for a State object
	 * @param name is a state's name
	 */
    public State(String name) {
		super(name);
		this.name = name;
	}


	/** 
	 * A constructor for a State object with the
	 * option to pass in an ArrayList of City
	 * objects that make up the state
	 * @param name is the name of a state
	 * @param cities is an ArrayList of cities that make up a state
	 */
	public State(String name, ArrayList<City> cities) { 
		super(name);
		this.name = name;
		this.cities = cities;
	}


	/** 
	 * Gets a list of cities that make up a state
	 * @return an ArrayList of cities
	 */
	public ArrayList<City> getCities(){
		return cities;
	}


	/** 
	 * Sets a list of cities to a state
	 * @param cities is an ArrayList of cities that make a state
	 */
	public void setCities(ArrayList<City> cities){
		this.cities = cities;
	}


	/**  
	 * Finds a city in an ArrayList of cities
	 * @param city a string value of the city being searched
	 * @return a String value of the searched city
	 */
	public State findCity(String city){
		return null;
	}


	/** 
	 * Adds a city to an ArrayList of cities
	 * @param city is the City intended to add
	 */
	public void addCity(City city){
		this.cities.add(city);
	}


	/**  
	 * Removes a city from a list of cities
	 * @param city is the city intended to be removed
	 */
	public void removeCity(City city){
		this.cities.remove(city);
	}


	/** 
	 * Gets the capital of a state
	 * @return the capital of a state
	 */
	public String getCapital(){
		return this.capital;
	}


	/** 
	 * Sets a capital to a state
	 * @param capitalName a string value of a state's capital
	 */
	public void setCapital(String capitalName){
		this.capital = captialName;
	}


	/** 
	 * Gets the name of a state
	 * @return the name of a state
	 */
	public String getName(){
		return this.name;
	}


	/** 
	 * Gets the population of a state
	 * @return a state's population
	 */
	public double getPopulation(){
		return this.population;
	}


	/** 
	 * Sets the population of a state
	 * @param population is a double value of a state's population
	 */
	public void setPopulation(double population){
		this.population = population;
	}


	/** 
	 * Adds a city to an ArrayList of cities
	 * @param city is the city intended to be added
	 * @param state is the state the city resides in
	 */
	public void addCity(City city, State state){
		//adds a city
	}


	/** 
	 * Searches for a river in an ArrayList of River objects
	 * @param riverName is a string value of a river's name
	 */
	public void searchRiver(String riverName) {
		//searches for a river
	}

	/**  
	 * Gets a list of rivers contained in a state
	 * @return an ArrayList of rivers
	 */
	public ArrayList<River> getRivers(){
		return this.rivers;
	}


	/** 
	 * Gets the country a state is contained in
	 * @return a state's country
	 */
	public Country getCountry() {
		return this.country;
	}


	/** 
	 * Sets a state's country
	 * @param country is the country bing set
	 */
	public void setCountry(Country country) {
		this.country = country;
	}


	/** 
	 * Sets the length of a states boundry
	 */
	public void setBoundryLength(){ 
		 // sets a bundry length
	}

	/** 
	 * Gets a list of a state's boundries
	 * @return an ArrayList of boundries
	 */
	public ArrayList<Boundry> getBoundries(){
		return this.boundries;
	}


	/** 
	 * Sets an ArrayList of neighbors to a state
	 */
	public void setNeighbors(ArrayList<String> neighbors){
		//sets neighbors
	}


	/** 
	 * Gets all neighbors of a state
	 * @return an ArrayList of strings of neighbors
	 */
	public ArrayList<String> getNeighbors(){
		return this.neighbors;
	}


	/**  
	 * Calculates a states area
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