using UnityEngine;

public class Spawner : MonoBehaviour
{
    public GameObject BallPrefab;
    public GameObject SpawnPoint;
    float spawnInterval = (1.0f / 6);
    public float force = 20;

    void Start()
    {
        Invoke("SpawnBall", spawnInterval);
    }

    void SpawnBall ()
    {
        GameObject ball = Instantiate(BallPrefab, SpawnPoint.transform.position, BallPrefab.transform.rotation);
        Vector3 direction = new Vector3(ball.transform.position.x, ball.transform.position.y, ball.transform.position.y);
        ball.GetComponent<Rigidbody>().AddForce(force, 0, 0, ForceMode.Impulse);
        Invoke("SpawnBall", spawnInterval);
    }
}
