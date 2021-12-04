using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class ReachColliderAI : MonoBehaviour
{

    Ray AIToWallRay;
    public GameObject Ball;
    public GameObject Player;
    public float hittingForce = 35f;
    public bool inReach = false;

    void OnTriggerEnter(Collider coll)
    {
        if (coll.gameObject.tag == "Ball")
        {
            inReach = true;
            ReachCollider.playerLastTouched = false;
            FrontWallCollider.hitFrontWall = false;

            float randomY = Random.Range(10, 20);
            float randomZ = Random.Range(-12, 12);
            Vector3 randomPoint = new Vector3(-17.5f, randomY, randomZ);

            AIToWallRay = new Ray(Player.transform.position, randomPoint);
            Debug.DrawRay(AIToWallRay.origin, AIToWallRay.direction * 50, Color.magenta);

            Ball.GetComponent<Rigidbody>().AddForce((AIToWallRay.direction * hittingForce) + Vector3.left, ForceMode.Impulse);
        }
    }

    void OnTriggerExit(Collider coll)
    {
        if (coll.gameObject.tag == "Ball")
        {
            inReach = false;
        }
    }
}
