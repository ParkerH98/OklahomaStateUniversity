using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class TrafficLights : MonoBehaviour
{
    private float lightInterval = 3.0f; //Time between lights switching
    private float timer = 0.0f;
    private Material[] lightMats;
    private Material[] runtimeLightMats;
    private Renderer rend;

    public int lightState = 0; // Determines current light color. 0 = Green, 1 = Yellow, 2 = Red. Use this to stop traffic as needed

    void Start()
    {
        rend = this.gameObject.GetComponent<Renderer>();
        lightMats = rend.materials;
        runtimeLightMats = rend.materials;

        for (int i = 0; i < 3; i++)
        {
            runtimeLightMats[i] = rend.materials[4];
        }
    }

    void Update()
    {
        timer -= Time.deltaTime;

        if (timer <= 0.0f)
        {
            timer += lightInterval;

            runtimeLightMats[lightState] = lightMats[lightState];
            runtimeLightMats[(lightState + 2) % 3] = lightMats[4];
            rend.materials = runtimeLightMats;

            lightState = (lightState + 1) % 3;
        }
    }

    private void OnCollisionEnter(Collision collision)
    {
        if(lightState == 2)
        {
            // Stop cars here if light is Red
        }
    }
}
