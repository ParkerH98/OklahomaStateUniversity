package geography;
import java.util.ArrayList;


/**
 * This interface serves the purpose dealing with boundries
 * for various different geographic objects.
 * 
 * 
 */

public interface Boundry{ 
    
    /**
     * Sets the length of an arbitrary geographic object.
     */
    public void setBoundryLength();


    /** 
     * Sets an ArrayList of neighbors to an arbitrary geographic object.
     * @param neighbors ArrayList of neighbors
     */
    public void setNeighbors(ArrayList<String> neighbors);
} 


