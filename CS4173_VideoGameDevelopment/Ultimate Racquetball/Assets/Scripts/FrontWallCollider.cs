using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class FrontWallCollider : MonoBehaviour
{


    public GameObject Ball;
    bool countable = true;
    public static bool hitFrontWall = false;

    void Update()
    {
        if (Ball.transform.position.x <= -16.5f && countable == true)
        {
            GameController.touchCount = 0;
            countable = false;
            hitFrontWall = true;
        }

        if (Ball.transform.position.y > -16.5f)
        {
            countable = true;
        }

        print("Touch Count: " + GameController.touchCount);
    }



}
