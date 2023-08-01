using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using Vuforia;

public class Fast : MonoBehaviour
{
    public GameObject fast;
    Controller controller;

    // Start is called before the first frame update
    void Start()
    {
        fast = GameObject.Find("SpeedUpButton");
        fast.GetComponent<VirtualButtonBehaviour>().RegisterOnButtonPressed(OnButtonPressed);
        fast.gameObject.GetComponent<VirtualButtonBehaviour>().RegisterOnButtonReleased(OnButtonReleased);
        controller = GameObject.FindGameObjectWithTag("GameController").GetComponent<Controller>();
    }//End Start

    public void OnButtonPressed(VirtualButtonBehaviour vb)
    {
        //Add fast code here
        controller.speedUp();

        //controller.speedUp();
        print("Speeding");
        Debug.Log("Speeding");

    }//End OnButtonPressed

    public void OnButtonReleased(VirtualButtonBehaviour vb)
    {
        print("Not Speeding");
        Debug.Log("Not Speeding");
    }//End OnButtonReleased

    // Update is called once per frame
    void Update()
    {
        
    }
}
