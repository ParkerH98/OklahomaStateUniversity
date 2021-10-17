using System.Collections;
using UnityEngine;

public class Bill : MonoBehaviour
{
    public Annie CubeAnnie;
    public Cody CubeCody;
    public Material yellow;

    public bool rotate = false;
    public bool yRotate = false;
    public bool zRotate = false;

    void Update()
    {
        if (rotate && yRotate)
        {
            this.transform.RotateAround(this.transform.position, Vector3.up, 90 * Time.deltaTime);
        }

        else if(rotate && zRotate)
        {
            this.transform.RotateAround(this.transform.position, Vector3.forward, 90 * Time.deltaTime);
        }
    }

    public void OnMouseDown()
    {
        // calls methods in other classes
        CubeAnnie.IncreaseSize();
        CubeCody.SetColor(yellow);
    }

    public void StartRotatingY()
    {
        rotate = true;
        yRotate = true;
        StartCoroutine(Timer4());
    }

    public IEnumerator Timer4()
    {
        yield return new WaitForSeconds(4f);
        rotate = false;
        yRotate = false;
    }


    public void StartRotatingZ()
    {
        rotate = true;
        zRotate = true;
        StartCoroutine(Timer5());
    }

    IEnumerator Timer5()
    {
        yield return new WaitForSeconds(5f);
        rotate = false;
        zRotate = false;
    }
}
