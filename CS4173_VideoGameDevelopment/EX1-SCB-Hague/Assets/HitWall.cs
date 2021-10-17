using UnityEngine;

public class HitWall : MonoBehaviour
{
    float wallBounceForce = 10f;
    private void OnCollisionEnter(Collision other)
    {
        float random = Random.Range(0, 100) * .1f;
        if (other.gameObject.CompareTag("Blue Wall"))
        {
            if (random >= 5)
            {
                Destroy(gameObject);
            }
            else
            {
                gameObject.GetComponent<Rigidbody>().AddForce(wallBounceForce, 0, 0, ForceMode.Impulse);
            }
        } 

        else if (other.gameObject.CompareTag("Yellow Wall"))
        {
            if (random >= 5)
            {
                Destroy(gameObject);
            }
            else
            {
                gameObject.GetComponent<Rigidbody>().AddForce(-wallBounceForce, 0, 0, ForceMode.Impulse);
            }
        }
    }
}
