using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class MapButtonBehavior : MonoBehaviour
{
    int count;
    bool mapVisible = false;
    public GameObject mapImage;
    public GameObject icon;

    public void start()
    {
        //set to invisible at start
        mapImage.SetActive(false);
    }
    public void OnButtonPress()
    {
        //These two lines are just for testing purposes:
            count++;
            //Debug.Log("Button clicked " + count + " times.");

        //onclick swap the visiblility 
        if(mapImage.active == true) { mapVisible = true; }
        if(mapImage.active == false) { mapVisible = false; }

        mapImage.SetActive(!mapVisible);
        icon.SetActive(!mapVisible);
        mapVisible = !mapVisible;


    }
}
