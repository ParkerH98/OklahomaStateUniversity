using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class GameController : MonoBehaviour
{
    public GameObject Ball;
    public GameObject Floor;

    public static int touchCount = 0;

    bool countable = true;

    // Start is called before the first frame update
    void Start()
    {
        
    }

    // Update is called once per frame
    void Update()
    {
        if (Ball.transform.position.y <= 1.0f && countable == true)
        {
            touchCount += 1;
            countable = false;
        }

        if (Ball.transform.position.y > 1.0f)
        {
            countable = true;
        }

        print("Touch Count: " + touchCount);
    }
}
