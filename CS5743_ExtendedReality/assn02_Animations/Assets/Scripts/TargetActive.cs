using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class TargetActive : MonoBehaviour
{
    // Start is called before the first frame update
    void Start()
    {
        
    }

    // Update is called once per frame
    void Update()
    {
        
    }

    public static bool active = false;

    public void setInactive(){
        active = false;
    }

    public void setActive(){
        active = true;
    }
}
