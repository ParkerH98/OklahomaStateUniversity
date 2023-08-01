using System.Collections.Generic;
using UnityEngine;

public class BuildingController : MonoBehaviour
{
    public GameObject buildingsController;

    // list of each building in the scene -- used to assign random heights and textures
    public List<GameObject> buildings = new List<GameObject>();
    // list of possible textures for each building -- Indices: SM: 0-4 -- MD: 5-6 -- LG: 7-9
    public List<Material> buildingTextures = new List<Material>();

    // lists to store each roof in the scene and its accompanying textures
    public List<GameObject> roofs = new List<GameObject>();
    public List<Material> roofTextures = new List<Material>();

    // holds random values for each iteration of the for loop
    float randomHeight;
    int randomTexture;
    int randomRoof;

    void Start()
    {
        for (int i = 0; i < buildings.Count; i++) // loops through all buildings
        {
            // gets random height
            randomHeight = Random.Range(7f, 100f); 

            // assigns random height to building
            buildings[i].transform.localScale = new Vector3(buildings[i].transform.localScale.x, randomHeight, buildings[i].transform.localScale.z);

            // this is because when a cube sits at (0, 0, 0), half of the building's height will be below the plane and half will be above
            // so we can add half the magnitude of the building in the y direction and add it to the building's original position
            float correctedHeight = randomHeight / 2; 

            // this moves each building up the y axis half the distance of the height
            buildings[i].transform.localPosition = new Vector3(buildings[i].transform.localPosition.x, correctedHeight, buildings[i].transform.localPosition.z); 

            // this is so taller buildings will have different textures than shorter buildings 
            if (randomHeight <= 30){ // small
                randomTexture = Random.Range(0, 5); // gets random number in range of textures indices
                randomRoof = Random.Range(0, 1); // gets random number in range of roofs indices

            }
            else if (randomHeight > 30 && randomHeight <= 50){ // medium
                randomTexture = Random.Range(5, 7); // gets random number in range of textures indices
                randomRoof = Random.Range(0, 1); // gets random number in range of roofs indices

            }
            else if (randomHeight > 50){ // large
                randomTexture = Random.Range(7, 10); // gets random number in range of textures indices
                randomRoof = Random.Range(1, 3); // gets random number in range of roofs indices
            }

            // assigns random texture to building
            buildings[i].GetComponent<Renderer>().material = buildingTextures[randomTexture]; 
            // assigns random texture to roof
            roofs[i].GetComponent<Renderer>().material = roofTextures[randomRoof]; 
        }
    }

    // toggles the visibility of the buildings on the scene -- mostly used for debugging
    public void toggleBuildings()
    {
        // if true, set false
        if (buildingsController.activeSelf == true)
        {
            buildingsController.SetActive(false);
        }
        else
        {
            buildingsController.SetActive(true);
        }
    }
}
