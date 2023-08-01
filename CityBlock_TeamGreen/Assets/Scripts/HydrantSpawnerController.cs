using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class HydrantSpawnerController : MonoBehaviour
{

    public GameObject fireHydrants; // Empty to hold all fire hydrants
    public GameObject instanceHolder; // Empty to hold all instances (to clean up hierarchy)

    private GameObject randomObj; // Random fire hydrant
    private GameObject instance; // Instance of fire hydrant
    private int randomIndex; // Random Index (pick fire hydrant prefab)
    
    // Start is called before the first frame update

    void Start()
    {

        // Choose random fire hydrant

        randomIndex = Random.Range(0,2);
        randomObj = fireHydrants.transform.GetChild(randomIndex).gameObject;

        // Set its transform and rotation to that of its spawner

        randomObj.transform.position = transform.position;
        randomObj.transform.rotation = transform.rotation;

        // Instantiate it

        instance = Instantiate(randomObj);
        
        // Set its parent as the instanceHolder

        instance.transform.parent = instanceHolder.transform;
    }
}