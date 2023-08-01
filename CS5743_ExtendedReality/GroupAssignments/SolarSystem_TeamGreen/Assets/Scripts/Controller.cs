using UnityEngine;
using System.Collections.Generic;

public class Controller : MonoBehaviour
{
    // references to each planet/star
    public GameObject sun;
    public Planet mercury;
    public Planet venus;
    public Planet earth;
    public Planet mars;
    public Planet jupiter;
    public Planet saturn;
    public Planet uranus;
    public Planet neptune;
    public Planet pluto;

    // list containing all the planets
    public List<Planet> planets = new List<Planet>();

    void Start()
    {
        // assigns planets to their respective objects
        sun = GameObject.Find("Sun");
        mercury = GameObject.Find("Mercury").GetComponent<Planet>();
        venus = GameObject.Find("Venus").GetComponent<Planet>();
        earth = GameObject.Find("Earth").GetComponent<Planet>();
        mars = GameObject.Find("Mars").GetComponent<Planet>();
        jupiter = GameObject.Find("Jupiter").GetComponent<Planet>();
        saturn = GameObject.Find("Saturn").GetComponent<Planet>();
        uranus = GameObject.Find("Uranus").GetComponent<Planet>();
        neptune = GameObject.Find("Neptune").GetComponent<Planet>();
        pluto = GameObject.Find("Pluto").GetComponent<Planet>();

        // sets initial values of the speed the planets rotate around the sun
        mercury.initialSunRotationalSpeed = 3.217927778f;
        venus.initialSunRotationalSpeed = 2.354122222f;
        earth.initialSunRotationalSpeed = 2.001877778f;
        mars.initialSunRotationalSpeed = 1.618509444f;
        jupiter.initialSunRotationalSpeed = 0.878594444f;
        saturn.initialSunRotationalSpeed = 0.651383333f;
        uranus.initialSunRotationalSpeed = 0.457783333f;
        neptune.initialSunRotationalSpeed = 0.365016667f;
        pluto.initialSunRotationalSpeed = 0.313255556f;

        // sets the initial speed of each planet (speed rotating about the sun)
        mercury.sunRotationalSpeed = mercury.initialSunRotationalSpeed;
        venus.sunRotationalSpeed = venus.initialSunRotationalSpeed;
        earth.sunRotationalSpeed = earth.initialSunRotationalSpeed;
        mars.sunRotationalSpeed = mars.initialSunRotationalSpeed;
        jupiter.sunRotationalSpeed = jupiter.initialSunRotationalSpeed;
        saturn.sunRotationalSpeed = saturn.initialSunRotationalSpeed;
        uranus.sunRotationalSpeed = uranus.initialSunRotationalSpeed;
        neptune.sunRotationalSpeed = neptune.initialSunRotationalSpeed;
        pluto.sunRotationalSpeed = pluto.initialSunRotationalSpeed;

        // sets the rotational speed of each planet (speed the planet is rotating about itself)
        mercury.selfRotationalSpeed = .02f;
        venus.selfRotationalSpeed = .03f;
        earth.selfRotationalSpeed = .025f;
        mars.selfRotationalSpeed = .02f;
        jupiter.selfRotationalSpeed = .05f;
        saturn.selfRotationalSpeed = .1f;
        uranus.selfRotationalSpeed = .015f;
        neptune.selfRotationalSpeed = .01f;
        pluto.selfRotationalSpeed = .01f;
    }

    // proportionally increases the speed that the planets orbit the sun by 10%
    public void speedUp()
    {
        float fractionOfSpeed;
        foreach (Planet planet in planets)
        {
            // if already at max speed
            if (earth.sunRotationalSpeed >= (earth.initialSunRotationalSpeed * 18)) 
            {
                print("WE ARE ALREADY AT MAX SPEED");
            }
            
            fractionOfSpeed = planet.initialSunRotationalSpeed / 5;
            planet.sunRotationalSpeed += fractionOfSpeed;

            // if we accidentlely went above the max speed, set the new speed to be the max speed
            if (earth.sunRotationalSpeed >= (earth.initialSunRotationalSpeed * 18)) 
            {
                planet.sunRotationalSpeed = planet.initialSunRotationalSpeed * 18;
                print("WE HIT MAX SPEED");
            }
        }
    }

    // proportionally decreases the speed that the planets orbit the sun by 10%
    public void slowDown()
    {
        float fractionOfSpeed;
        foreach (Planet planet in planets)
        {
            // if already at max speed
            if (earth.sunRotationalSpeed <= (earth.initialSunRotationalSpeed / 2)) 
            {
                print("WE ARE ALREADY AT MIN SPEED");
            }
            
            fractionOfSpeed = planet.initialSunRotationalSpeed / 5;
            planet.sunRotationalSpeed -= fractionOfSpeed;

            // if we accidentlely went above the max speed, set the new speed to be the min speed
            if (earth.sunRotationalSpeed <= (earth.initialSunRotationalSpeed / 2)) 
            {
                planet.sunRotationalSpeed = planet.initialSunRotationalSpeed / 2 ;
                print("WE HIT MIN SPEED");
            }
        }
    }

    // sets initital speed to 1 earth rotation per 10 seconds --> multiplies the initial speed by 18
    public void setMaxSpeed()
    {
        foreach (Planet planet in planets)
        {
            planet.sunRotationalSpeed = planet.initialSunRotationalSpeed * 18;
        }
    }

    // sets initital speed to 1 earth rotation per 360 seconds --> dividing the initial speed by 2
    public void setMinSpeed()
    {
        foreach (Planet planet in planets)
        {
            planet.sunRotationalSpeed = planet.initialSunRotationalSpeed / 2;
        }
    }

    // sets initital speed to 1 earth rotation per 180 seconds
    public void setInitialSpeed()
    {
        foreach (Planet planet in planets)
        {
            planet.sunRotationalSpeed = planet.initialSunRotationalSpeed;
        }
    }
}