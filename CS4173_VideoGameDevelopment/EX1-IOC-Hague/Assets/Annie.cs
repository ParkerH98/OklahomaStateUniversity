using System.Collections;
using UnityEngine;

public class Annie : MonoBehaviour
{
    public static Bill bill;
    public static Cody cody;
    public Material orange;

    // Start is called before the first frame update
    void Start()
    {
        bill = GameObject.FindWithTag("tagB").GetComponent<Bill>();
        cody = GameObject.FindWithTag("tagC").GetComponent<Cody>();
    }

    public void OnMouseDown()
    {
        // calls methods in other classes
        cody.SetColor(orange);
        bill.StartRotatingY();
    }

    public void IncreaseSize()
    {
        float scaleX = this.transform.localScale.x + (this.transform.localScale.x / 2);
        this.transform.localScale = new Vector3(scaleX, this.transform.localScale.y, this.transform.localScale.z);
    }

    public void DecreaseSize()
    {
        float scaleX = this.transform.localScale.x - (this.transform.localScale.x / 2);
        this.transform.localScale = new Vector3(scaleX, this.transform.localScale.y, this.transform.localScale.z);
    }
}
