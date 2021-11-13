using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class ReachCollider : MonoBehaviour
{

    Ray ray;

    Ray r;
    RaycastHit hit;
    public GameObject Ball;
    public GameObject Player;
    public float hittingForce = 15f;
    public bool inReach = false;


    void FixedUpdate()
    {
        ray = Camera.main.ScreenPointToRay(Input.mousePosition);

       

        if (Physics.Raycast(ray, out hit, 1000))
        {
            // Debug.Log("Hit" + hit.transform.name);
            Debug.DrawRay(ray.origin, ray.direction * hit.distance, Color.yellow);
        }

        r = new Ray(Player.transform.position, hit.point);
        Debug.DrawRay(r.origin, r.direction * hit.distance, Color.green);
        
        if(Input.GetMouseButtonDown(0) && inReach)
        {
            print(r.direction);
            Ball.GetComponent<Rigidbody>().AddForce(r.direction * hittingForce, ForceMode.Impulse);
            // Ball.GetComponent<Rigidbody>().AddForce(Vector3.left * hittingForce, ForceMode.Impulse);

            
        }
    }

    void OnTriggerEnter(Collider coll)
    {
        if (coll.gameObject.tag == "Ball")
        {
            print("IN REACH");
            inReach = true;
        }
    }

    void OnTriggerExit(Collider coll)
    {
        if (coll.gameObject.tag == "Ball")
        {
            inReach = false;
            print("EXITED");
        }
    }
}
