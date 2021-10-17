using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class POVCamera : MonoBehaviour
{
    private float speed = 200;
    public GameObject player;
    public GameObject FocalPoint;

    public GameObject fixedCam;
    public GameObject pov;

    bool fixedEnabled = true;

void Start()
{
}

    // Update is called once per frame
    void Update()
    {
        float horizontalInput = Input.GetAxis("Horizontal");
        float vInput = Input.GetAxis("Vertical");

        transform.Rotate(Vector3.up, horizontalInput * speed * Time.deltaTime);
        transform.Rotate(Vector3.left, vInput * speed * Time.deltaTime);

        transform.position = player.transform.position; // Move focal point with player

        if (Input.GetKeyDown(KeyCode.Space))
        {
            print("happening");
            player.GetComponent<Rigidbody>().AddForce(FocalPoint.transform.forward * 1 * speed * Time.deltaTime, ForceMode.Impulse);

        }

        if (Input.GetKeyDown(KeyCode.F))
        {
            print("butts");
            print(fixedEnabled);

            if (fixedEnabled)
            {
                pov.SetActive(true);
                fixedCam.SetActive(false);
                fixedEnabled = false;
            }

            else if (!fixedEnabled)
            {
                pov.SetActive(false);
                fixedCam.SetActive(true);
                fixedEnabled = true;
            }
        }
    }
}
