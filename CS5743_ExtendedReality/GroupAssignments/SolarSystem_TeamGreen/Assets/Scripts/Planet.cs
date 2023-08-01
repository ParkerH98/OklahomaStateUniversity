using UnityEngine;
using System.Collections;

public class Planet : MonoBehaviour
{
    private GameObject sun; // reference to the Sun GameObject

    public float initialSunRotationalSpeed; // this is needed to store the initial speed so we can reference it to calculate (total speed / 10)
    public float sunRotationalSpeed; // speed a planet rotates around the sun
    public float selfRotationalSpeed; // speed a planet rotates about itself

    void Start()
    {
        sun = GameObject.Find("Sun"); // allows all planets to have knowledge of the sun
    }

    // Update is called once per frame
    void Update()
    {
        transform.RotateAround(sun.transform.position, Vector3.up, sunRotationalSpeed * Time.deltaTime); // rotates the planets about the sun
        transform.Rotate(0, selfRotationalSpeed, 0, Space.Self); // rotates the planets about themselves
    }
}
