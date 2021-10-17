using UnityEngine;

public class DestroyObject : MonoBehaviour
{
    private float bottomLimit = 0;

    // Update is called once per frame
    void Update()
    {
        if (transform.position.y < bottomLimit)
        {
            Destroy(gameObject);
        }
    }
}
