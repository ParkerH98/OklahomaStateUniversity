using System.Collections;
using System.Collections.Generic;
using UnityEngine;

//trying to change things so I can push to Git

public class AvatarScript : MonoBehaviour
{
    private Transform[] waypoints;
    private int currentWaypoint = 0;
    private float rotationSpeed = 4f;

    public GameObject waypointContainer;
    public float speed = 500f;
    public float neighborhood = 0.6f;

    // Use this for initialization
    void Start()
    {
        // Copy waypoint info from public variable.  The container itself is among the transforms
        // in the container.
        Transform[] potentialWaypoints = waypointContainer.GetComponentsInChildren<Transform>();

        // Create the private waypoint array; it is one smaller than the potential array,
        // since we do not want to include the container itself.
        waypoints = new Transform[potentialWaypoints.Length - 1];

        // Loop through the potential array, only copying actual waypoints into the private array.
        for (int i = 0, j = 0; i < potentialWaypoints.Length; i++)
        {
            if (potentialWaypoints[i] != waypointContainer.transform)
            {
                // This is a waypoint rather than the container;
                // add the waypoint to the array.
                waypoints[j++] = potentialWaypoints[i];
            }
        }

        // Set the velocity of the player.
        //GetComponent<Rigidbody>().velocity = Vector3.up * speed;
    }

    //  void Update() {
    //      transform.position = Vector3.MoveTowards (transform.position, waypoints [currentWaypoint].position, speed * Time.deltaTime);
    //  }

    void FixedUpdate()
    {

        Vector3 movementVector = NavigateTowardWaypoint();

        // Set velocity to direction * speed * deltaTime.
        GetComponent<Rigidbody>().velocity = movementVector.normalized * speed * Time.fixedDeltaTime;
    }

    Vector3 NavigateTowardWaypoint()
    {
        // This tells us how close we get to a waypoint before we turn our attention
        // to the next waypoint.
        //float neighborhood = 0.6f;
        /*
        Vector3 targetDir = waypoints[currentWaypoint].position - transform.position;
        float step = speed * -2 * Time.deltaTime;
        Vector3 newDir = Vector3.RotateTowards(transform.forward, targetDir, step, 0.0F);
        transform.rotation = Quaternion.LookRotation(newDir);
        */
        Vector3 movementVector = waypoints[currentWaypoint].position - transform.position;

        //Vector3 relativePos = movementVector - transform.position;
        //transform.rotation = Quaternion.LookRotation(relativePos);
        transform.LookAt(waypoints[currentWaypoint]);

        // print("*** Distance: " + movementVector.magnitude);

        // Are we in the neighborhood of the target waypoint?
        if (movementVector.magnitude <= neighborhood)
        {
        

            // Yes; focus our attention on the next waypoint in the path.
            currentWaypoint = (currentWaypoint + 1) % waypoints.Length;
            //          int rand = Random.Range(1, waypoints.Length -1);
            //          currentWaypoint = (currentWaypoint + rand) % waypoints.Length;

            //print("Current waypoint: " + currentWaypoint + "    Relative Position: " + movementVector);
        }

        return movementVector;
    }
}