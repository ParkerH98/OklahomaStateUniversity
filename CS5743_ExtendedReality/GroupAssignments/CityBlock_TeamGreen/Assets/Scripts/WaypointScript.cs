using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class WaypointScript : MonoBehaviour
{
    // The next waypoint.
    public GameObject next;
    public bool isStart = false;

    void Awake()
    {
        // Verify that each waypoint has a next waypoint specified.
        if (!next)
        {
            print("This waypoint is not connected; fix the problem" + this);
        }
    }

    void OnDrawGizmos()
    {
        // Draw waypoints and connections in the scene view for easier debugging.
        Gizmos.color = new Color(1, 0, 0, 0.3f);
        Gizmos.DrawCube(transform.position, new Vector3(1, 1, 1));

        if (next)
        {
            Gizmos.color = new Color(0, 1, 0, 1f);
            Gizmos.DrawLine(transform.position, next.transform.position);
        }
    }
}