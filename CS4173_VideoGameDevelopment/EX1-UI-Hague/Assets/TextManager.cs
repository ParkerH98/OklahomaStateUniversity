using UnityEngine;
using TMPro;

public class TextManager : MonoBehaviour
{
    public TextMeshProUGUI titleText;
    public TextMeshProUGUI pointsText;

    public GameObject titleScreen;
    public GameObject points;
    bool hidden = false;
    int pointValue = 0;
    int pIncrement = 0;
    int qDecrement = 0;

    // Update is called once per frame
    void Update()
    {
        if (Input.GetKeyDown(KeyCode.P) && hidden)
        {
            pointValue += pIncrement;
            pointsText.text = "Points: " + pointValue;
        }

        if (Input.GetKeyDown(KeyCode.Q) && hidden)
        {
            pointValue += qDecrement;
            pointsText.text = "Points: " + pointValue;
        }

        if (Input.GetKeyDown(KeyCode.X) && hidden)
        {
            pointValue = 0;
            titleScreen.SetActive(true);
            points.SetActive(false);
            hidden = false;
            pointsText.text = "Points: " + pointValue;
        }
    }

    public void ChangeText(string status)
    {
        titleScreen.SetActive(false);
        points.SetActive(true);
        hidden = true;

        if (status == "bar")
        {
            pIncrement = 1;
            qDecrement = -1;
        }
        else if(status == "baz")
        {
            pIncrement = 2;
            qDecrement = -2;
        }
        else if(status == "faz")
        {
            pIncrement = 10;
            qDecrement = -3;
        }
        else if(status == "foo")
        {
            pIncrement = 20;
            qDecrement = -30;
        }
    }
}
