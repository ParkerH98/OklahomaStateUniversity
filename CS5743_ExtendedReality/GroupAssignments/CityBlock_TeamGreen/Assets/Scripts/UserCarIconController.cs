using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class UserCarIconController : MonoBehaviour
{
    private bool noNewParent; // boolean to check for parent to avoid unnecessary processing
    private Transform currParent, newParent; // Current and new parents

    // Start is called before the first frame update

    void Start(){
        currParent = transform.parent; // Gets parent
        currParent.DetachChildren(); // Detaches Children
        noNewParent = true; // By default doesn't have a new parent
        gameObject.SetActive(false); // Not active by default
    }

    void LateUpdate(){
        if (noNewParent){ // Checks if a new parent has been assigned to avoid unnecessary processing
            newParent = currParent.parent;

            // If new parent isn't null, set it as the parent and move to its position
            
            if (newParent != null){
                noNewParent = false;
                transform.rotation = newParent.rotation;
                transform.parent = newParent;
                transform.position = newParent.position;
            }
        }
    }
}
