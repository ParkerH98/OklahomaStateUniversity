using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using Vuforia;

public class ButtonController : MonoBehaviour
{
    GameObject speedUpButton;
    GameObject slowDownButton;


    // Start is called before the first frame update
    void Start()
    {
        speedUpButton = GameObject.Find("SpeedUpButton");
        slowDownButton = GameObject.Find("SlowDownButton");

        speedUpButton.GetComponent<VirtualButtonBehaviour>().RegisterOnButtonPressed(VirtualButtonPressed);
        slowDownButton.GetComponent<VirtualButtonBehaviour>().RegisterOnButtonPressed(VirtualButtonPressed);


    }

    public void VirtualButtonPressed(VirtualButtonBehaviour button) 
        {
            if (button == speedUpButton){
                print("SPEED UP PRESSED");
            }
            else if (button == slowDownButton){
                print("SLOW DOWN PRESSED");
            }
            

        }
    

 
}
