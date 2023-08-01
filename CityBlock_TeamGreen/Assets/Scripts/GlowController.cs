using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class GlowController : MonoBehaviour
{

    public bool isGlowing; // Boolean to keep track of glow state

    // Start is called before the first frame update

    void Start()
    {
        gameObject.SetActive(isGlowing); // Sets whether its glowing based on "isGlowing"
        transform.parent = GameObject.Find("userCar(Clone)").transform; // Finds User's car and makes it the parent
        transform.position = transform.parent.transform.position; // Set's its position to the User's car
    }

    // Toggles Glow On/Off

    public void toggleGlow(){
        isGlowing = !isGlowing; // Change glow state
        gameObject.SetActive(isGlowing); // Enables/Disables based on glow state
    }
}