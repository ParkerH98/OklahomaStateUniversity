using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class FrontWallCollider : MonoBehaviour
{


    public GameObject Ball;
    bool countable = true;

    void Update()
    {
        if (Ball.transform.position.x <= -16.5f && countable == true)
        {
            GameController.touchCount = 0;
            countable = false;
        }

        if (Ball.transform.position.y > -16.5f)
        {
            countable = true;
        }

        print("Touch Count: " + GameController.touchCount);
    }



}
