using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class ReachCollider : MonoBehaviour
{

    void OnTriggerEnter(Collider coll)
    {
        if (coll.gameObject.tag == "Wall")
        {
            print("One Vote Added");
        }
    }
}
