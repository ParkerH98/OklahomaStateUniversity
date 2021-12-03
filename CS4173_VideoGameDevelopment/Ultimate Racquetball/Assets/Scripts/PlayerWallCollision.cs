using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PlayerWallCollision : MonoBehaviour
{
    public GameObject Player;

    Rigidbody playerRB;
    public float pushForce = 4;

    void Start()
    {
        playerRB = Player.GetComponent<Rigidbody>();
    }

    void OnCollisionEnter(Collision coll)
    {
        if (coll.gameObject.tag == "Right Wall")
        {
            playerRB.AddForce(Vector3.back * pushForce, ForceMode.Impulse);
        }
        else if (coll.gameObject.tag == "Left Wall")
        {
            playerRB.AddForce(Vector3.forward * pushForce, ForceMode.Impulse);
        }
         else if (coll.gameObject.tag == "Back Wall")
        {
            playerRB.AddForce(Vector3.left * pushForce, ForceMode.Impulse);
        }
         else if (coll.gameObject.tag == "Front Wall")
        {
            playerRB.AddForce(Vector3.right * pushForce, ForceMode.Impulse);
        }
    }
}
