using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class ReachCollider : MonoBehaviour
{

    Rigidbody rb;
    public float pushForce = 10;


    void Start()
    {
        rb = this.GetComponentInParent<Rigidbody>();
    }

    void OnTriggerEnter(Collider coll)
    {
      
    }
}
