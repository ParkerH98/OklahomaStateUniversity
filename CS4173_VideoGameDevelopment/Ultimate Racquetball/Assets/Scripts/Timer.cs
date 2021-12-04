using System.Collections;
using System.Collections.Generic;
using TMPro;
using UnityEngine;

public class Timer : MonoBehaviour
{
    public static float countdown = 4;
    public TextMeshProUGUI countdownText;
    public GameObject countdownParent;


    void Update()
    {
        if (countdown > 0 && !GameController.inGame)
        {
            countdownParent.SetActive(true);
            countdown -= Time.deltaTime;
            countdownText.text = "Round Starts in: " + countdown;
        }
        else
        {
            countdownParent.SetActive(false);
        }
    }
}
