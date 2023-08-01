using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class DayCycleController : MonoBehaviour
{
    public bool day; // Boolean to determine if its day or night
    public float rpm; // Revolutions per minute
    public int fade; // Length of fade for the light's intenisty to transition between day and night
    public int offset; // How far off from being parallel to the ground is it considered night
    public float nightIntensity; // Light's intensity at night
    public float dayIntensity; // Light's intensity during the day

    private float xRotation; // Rotation of x in Euler Angles
    private Light light; // Directional light component

    // Start is called before the first frame update

    void Start()
    {
        day = true; // Day by default
        light = GetComponent<Light>();
    }

    // Update is called once per frame

    void Update()
    {

        transform.Rotate(0,6*rpm*Time.deltaTime,0); // Continuously rotate by changing the y angle
        xRotation = transform.localRotation.eulerAngles.x;

        // Functionality for adjusting light intensity

        if (xRotation < 180 && xRotation > offset){
            day = true;
            if (xRotation-offset > fade) light.intensity = dayIntensity; // intesity during day
            else light.intensity = ((dayIntensity-nightIntensity)*(xRotation-offset)/fade)+nightIntensity;
        } else { // night
            day = false;
            light.intensity = nightIntensity; //night light intesity level
        }
        
    }
}
