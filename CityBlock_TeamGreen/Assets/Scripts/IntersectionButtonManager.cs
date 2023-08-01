using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class IntersectionButtonManager : MonoBehaviour
{
    int count;
    public float closeEnough = 0.5f;
    public GameObject targetLoc;
    public Text message;
    public GameObject mapImage;
    GameObject userCar; //= GameObject.Find("userCar(clone)");

    public void start()
    {
        
        message.text = "No user input recieved yet.";
    }
    public void OnButtonPress()
    {
        //userCar = GameObject.Find("userCar(Clone)");
        //These two lines are just for testing purposes:
        count++;
        //Debug.Log("Button clicked " + count + " times.");

        //on click, change the minimap back to invisible
        mapImage.SetActive(false);

        //identify and output when userCar has reached the user inputted destination (using a neighborhood value of closeEnough):
        userCar = GameObject.Find("userCar(clone)");
        Vector3 diff = targetLoc.transform.position - userCar.transform.position;
        if (diff.magnitude <= closeEnough){
            message.text = "userCar has reached the inputted destination of intersection " + targetLoc.name;
            Debug.Log("userCar has reached the inputted destination of intersection " + targetLoc.name);
        }

    }
}
