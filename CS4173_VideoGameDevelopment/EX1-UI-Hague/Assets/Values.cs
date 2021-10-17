using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class Values : MonoBehaviour
{
    private Button button;
    public string status;
    private TextManager textManager;


    // Start is called before the first frame update
    void Start()
    {

        textManager = GameObject.Find("TextManager").GetComponent<TextManager>();
        button = GetComponent<Button>();
        button.onClick.AddListener(SetStatus);
        
    }


     void SetStatus()
    {
        Debug.Log(button.gameObject.name + " was clicked");
        textManager.ChangeText(status);
    }
}
