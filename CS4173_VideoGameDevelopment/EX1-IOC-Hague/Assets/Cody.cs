using UnityEngine;

public class Cody : MonoBehaviour
{
    private Annie annie;
    private Bill bill;

    // Start is called before the first frame update
    void Start()
    {
        annie = GameObject.Find("Annie").GetComponent<Annie>();
        bill = GameObject.Find("Bill").GetComponent<Bill>();
    }

    public void OnMouseDown()
    {
        // calls methods in other classes
        annie.DecreaseSize();
        bill.StartRotatingZ();
    }

    public void SetColor(Material color)
    {
        this.GetComponent<Renderer>().material = color;
    }
}
