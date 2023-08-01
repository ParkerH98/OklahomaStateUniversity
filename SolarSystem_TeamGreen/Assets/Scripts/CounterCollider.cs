using UnityEngine;
using System;
public class CounterCollider : MonoBehaviour
{
    float seconds;
    float temp;
    float diff;
    void OnTriggerEnter(Collider c)
    {
        seconds = Time.fixedTime;
        diff = seconds - temp;
        print(diff);
        temp = seconds;

    }
}
