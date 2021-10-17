using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class ShooterArm : MonoBehaviour
{
    public GameObject RotationPoint;
    float dir = 30;
    
    // Update is called once per frame
    void Update()
    {
        this.transform.RotateAround(RotationPoint.transform.position, Vector3.up, dir * Time.deltaTime);

        if (this.transform.localRotation.y >= .60){
            dir = -30;
        }

        if (this.transform.localRotation.y <= -.60){
            dir = 30;
        }
    }
}
