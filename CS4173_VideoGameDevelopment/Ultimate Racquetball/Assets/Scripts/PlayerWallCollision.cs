using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PlayerWallCollision : MonoBehaviour
{
    Rigidbody rb;
    public float pushForce = 4;

    void Start()
    {
        rb = this.GetComponentInParent<Rigidbody>();
    }

    void OnCollisionEnter(Collision coll)
    {
        if (coll.gameObject.tag == "Right Wall")
        {
            Debug.Log("pushLeft");
            rb.AddForce(Vector3.back * pushForce, ForceMode.Impulse);
        }
        else if (coll.gameObject.tag == "Left Wall")
        {
            Debug.Log("pushRight");
            rb.AddForce(Vector3.forward * pushForce, ForceMode.Impulse);
        }
         else if (coll.gameObject.tag == "Back Wall")
        {
            Debug.Log("pushRight");
            rb.AddForce(Vector3.left * pushForce, ForceMode.Impulse);
        }
         else if (coll.gameObject.tag == "Front Wall")
        {
            Debug.Log("pushRight");
            rb.AddForce(Vector3.right * pushForce, ForceMode.Impulse);
        }
    }
}
