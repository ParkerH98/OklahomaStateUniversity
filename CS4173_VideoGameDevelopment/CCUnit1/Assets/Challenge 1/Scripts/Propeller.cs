using UnityEngine;

public class Propeller : MonoBehaviour
{
    Vector3 rotateVector = new Vector3(0, 0, 10);

    // Update is called once per frame
    void Update()
    {
        this.gameObject.transform.Rotate(rotateVector);

    }
}
