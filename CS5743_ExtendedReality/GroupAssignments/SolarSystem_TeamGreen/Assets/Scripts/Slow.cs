using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using Vuforia;

public class Slow : MonoBehaviour
{
    public GameObject slow;
    Controller controller;
    //public Controller controller;

    // Start is called before the first frame update
    void Start()
    {
        slow = GameObject.Find("SlowDownButton");
        slow.GetComponent<VirtualButtonBehaviour>().RegisterOnButtonPressed(OnButtonPressed);
        slow.gameObject.GetComponent<VirtualButtonBehaviour>().RegisterOnButtonReleased(OnButtonReleased);
        controller = GameObject.FindGameObjectWithTag("GameController").GetComponent<Controller>();


    }

    public void OnButtonPressed(VirtualButtonBehaviour vb)
    {
            //Add slow code here
            controller.slowDown();

            print("Slowing");
            Debug.Log("Slowing");

    }

    public void OnButtonReleased(VirtualButtonBehaviour vb)
    {
        print("Not Slowing");
        Debug.Log("Not Slowing");
    }

    // Update is called once per frame
    void Update()
    {
        
    }
}
