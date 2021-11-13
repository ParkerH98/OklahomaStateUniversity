using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class ReachCollider : MonoBehaviour
{

    void OnTriggerEnter(Collider coll)
    {
        if (coll.gameObject.tag == "Ball")
        {
            print("One Vote Added");

            if (Input.GetKeyDown(KeyCode.Space))
            {

            }
        }
    }
}



