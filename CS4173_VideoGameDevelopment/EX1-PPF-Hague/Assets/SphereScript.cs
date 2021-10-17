using System.Collections.Generic;
using UnityEngine;

public class SphereScript : MonoBehaviour
{
    public GameObject ballPrefab;
    public GameObject SpawnPoint;
    public List<Material> colors = new List<Material>();
    public ParticleSystem smoke;
    ParticleSystem.EmissionModule emissionModule;
    private GameObject ball;

    private float spawnInterval = .5f;
    public float force = 50;

    void Start()
    {
        emissionModule = smoke.emission;
        Invoke("SpawnBall", spawnInterval);
    }

    void Update()
    {
        if (ball)
        {
            // sets smoke direction and energy
            Vector3 negdir = new Vector3(-ball.transform.position.x, -ball.transform.position.y, -ball.transform.position.z);
            smoke.transform.localPosition = negdir;
            emissionModule.rateOverTime = force;
        }
    }

    void SpawnBall ()
    {
        ball = Instantiate(ballPrefab, SpawnPoint.transform.position, ballPrefab.transform.rotation);

        int r = Random.Range(0, 3);
        ball.GetComponent<Renderer>().material = colors[r];

        Vector3 direction = new Vector3((float)Random.Range(-10,10), 0, (float)Random.Range(-10,10));
        ball.GetComponent<Rigidbody>().AddForce(direction * force); 

        Invoke("SpawnBall", spawnInterval);
        Destroy(ball, 6);
    }
}
