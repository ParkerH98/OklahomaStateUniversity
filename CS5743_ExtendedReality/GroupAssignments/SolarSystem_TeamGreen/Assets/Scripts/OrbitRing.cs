using System.Collections;
using UnityEngine;



public class OrbitRing : MonoBehaviour
{
    void Start()
    {
        StartCoroutine(turnTrue()); // runs the thread when the ptogram starts
    }

    // thread to turn off the TrailRenderer emitter off for 3 seconds
    public IEnumerator turnTrue()
    {
        const int TIME_TO_WAIT = 5;
        TrailRenderer tr = GetComponent<TrailRenderer>();

        tr.emitting = false; // sets emitter to false
        yield return new WaitForSeconds(TIME_TO_WAIT); // waits for three seconds
        tr.emitting = true; // sets emitter to true
    }
}
