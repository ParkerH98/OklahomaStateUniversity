using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class ReachCollider : MonoBehaviour
{

    Ray cameraToCursorRay;
    Ray playerToCurorRay;
    RaycastHit cursorPos;
    public GameObject Ball;
    public GameObject Player;
    public float hittingForce = 20f;
    public bool inReach = false;


    public static bool playerLastTouched = false;


    void FixedUpdate()
    {
        cameraToCursorRay = Camera.main.ScreenPointToRay(Input.mousePosition);

        if (Physics.Raycast(cameraToCursorRay, out cursorPos, 1000))
        {
            Debug.DrawRay(cameraToCursorRay.origin, cameraToCursorRay.direction * cursorPos.distance, Color.yellow);
        }


        playerToCurorRay = new Ray(Player.transform.position, cursorPos.point);
        Debug.DrawRay(playerToCurorRay.origin, playerToCurorRay.direction * cursorPos.distance, Color.green);
        
        // if(Input.GetMouseButtonDown(0) && inReach)
        // {
        //     print(playerToCurorRay.direction);
        //     // Ball.GetComponent<Rigidbody>().AddForce(playerToCurorRay.direction * hittingForce, ForceMode.Impulse);
        //     // Ball.GetComponent<Rigidbody>().AddForce(Vector3.left * hittingForce, ForceMode.Impulse);
        // }
    }

    void OnTriggerEnter(Collider coll)
    {
        if (coll.gameObject.tag == "Ball")
        {
            inReach = true;
            playerLastTouched = true;
            FrontWallCollider.hitFrontWall = false;


            // Ball.GetComponent<Rigidbody>().AddForce(playerToCurorRay.direction * hittingForce, ForceMode.Impulse);
            Ball.GetComponent<Rigidbody>().AddForce((playerToCurorRay.direction * hittingForce) + Vector3.left, ForceMode.Impulse);


        }
    }

    void OnTriggerExit(Collider coll)
    {
        if (coll.gameObject.tag == "Ball")
        {
            inReach = false;
        }
    }
}
