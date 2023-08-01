using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class StreetLightController : MonoBehaviour
{
    public Light light;
    public float brightness;
    private DayCycleController script;
    private const byte OFF = 0;

    // Start is called before the first frame update

    void Start()
    {
        script = GameObject.Find("Directional Light").GetComponent<DayCycleController>();
    }

    // Update is called once per frame
    
    void Update()
    {
        if (script.day) light.intensity = OFF;
        else light.intensity = brightness;
    }
}
