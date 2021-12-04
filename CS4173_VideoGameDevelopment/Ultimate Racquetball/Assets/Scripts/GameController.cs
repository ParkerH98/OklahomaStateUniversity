using System.Collections;
using System.Collections.Generic;
using TMPro;
using UnityEngine;

public class GameController : MonoBehaviour
{

    public TextMeshProUGUI playerText;
    public TextMeshProUGUI aiText;


    public GameObject Ball;
    public GameObject Player;
    public GameObject AI_Opponent;
    public GameObject ServerSpawn;
    public GameObject DefenderSpawn;
    public GameObject BallSpawn;

    private int playerScore = 0;
    private int aiScore = 0;
    public static int touchCount = 0;
    bool countable = true;
    public static bool inGame = false;

    // Start is called before the first frame update
    void Start()
    {
        inGame = true;
    }

    // Update is called once per frame
    void Update()
    {
        if (touchCount >= 2 || Ball.transform.position.y < -1)
        {
            restartGame(ReachCollider.playerLastTouched, FrontWallCollider.hitFrontWall);
        }

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

    public void restartGame(bool playerLastTouched, bool hitFrontWall)
    {
        Timer.countdown = 4;
        inGame = false;

        if (playerLastTouched && hitFrontWall)
        {
            playerWinsRound();
        }
        else if (playerLastTouched && !hitFrontWall)
        {
            aiWinsRound();
        }

        else if (!playerLastTouched && hitFrontWall)
        {
            aiWinsRound();
        }

        else if (!playerLastTouched && !hitFrontWall)
        {
            playerWinsRound();
        }
    }


    public void playerWinsRound()
    {
        touchCount = 0;
        playerScore += 1;
        UpdateCanvasScores();
        playerServe();
    }

    public void aiWinsRound()
    {
        touchCount = 0;
        aiScore += 1;
        UpdateCanvasScores();
        aiServe();
    }

    public void playerServe()
    {
        DisablePlayers();
        StartCoroutine(TimeBetweenRounds());

        Ball.GetComponent<Rigidbody>().velocity = new Vector3(0, 0, 0);
        Ball.transform.localPosition = BallSpawn.transform.position;

        Player.transform.localPosition = ServerSpawn.transform.position;
        Player.GetComponent<Rigidbody>().velocity = new Vector3(0, 0, 0);

        AI_Opponent.transform.localPosition = DefenderSpawn.transform.position;
        AI_Opponent.GetComponent<Rigidbody>().velocity = new Vector3(0, 0, 0);


    }

    public void aiServe()
    {
        DisablePlayers();
        StartCoroutine(TimeBetweenRounds());

        Ball.GetComponent<Rigidbody>().velocity = new Vector3(0, 0, 0);
        Ball.transform.localPosition = BallSpawn.transform.position;

        Player.transform.localPosition = DefenderSpawn.transform.position;
        Player.GetComponent<Rigidbody>().velocity = new Vector3(0, 0, 0);

        AI_Opponent.transform.localPosition = ServerSpawn.transform.position;
        AI_Opponent.GetComponent<Rigidbody>().velocity = new Vector3(0, 0, 0);

    }

    public void UpdateCanvasScores()
    {
        playerText.text = "Player Score: " + playerScore;
        aiText.text = "Opponent Score: " + aiScore;
    }


    IEnumerator TimeBetweenRounds()
    {
        yield return new WaitForSeconds(5);
        EnablePlayers();
    }

    public void DisablePlayers()
    {
        Player.SetActive(false);
        AI_Opponent.SetActive(false);
        Ball.SetActive(false);
    }

    public void EnablePlayers()
    {
        Player.SetActive(true);
        AI_Opponent.SetActive(true);
        Ball.SetActive(true);
    }



}
