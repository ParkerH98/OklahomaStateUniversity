using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class SpawnerController : MonoBehaviour
{
    public GameObject decor; // Empty Object containing decorative Object prefabs
    public GameObject instanceHolder; // Empty Object to hold instances (to clean up hierarchy)

    private int randomIndex; // random index
    private int totalObj; // total objects
    private GameObject randomObj; // random decorative object
    private GameObject instance; // instance of decoration object

    // Start is called before the first frame update

    void Start()
    {
        totalObj = decor.transform.childCount; // Amount of Objects
        randomIndex = Random.Range(0,totalObj); // Random Index from the amount of Objects
        randomObj = decor.transform.GetChild(randomIndex).gameObject; // Get Random child of decor based on randomIndex
        randomObj.transform.position = transform.position; // Set child Object's position to the spawner's position
        randomObj.transform.rotation = transform.rotation; // Set Child Object's rotation to the spawner's rotation

        instance = Instantiate(randomObj); // Instantiate child Object
        instance.transform.parent = instanceHolder.transform; // Sets instanceHolder as parent

    }
}
