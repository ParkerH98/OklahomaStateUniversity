using UnityEngine;

public class PlayerMovement : MonoBehaviour
{
    [SerializeField] float speed;
    private Rigidbody playerRB;

    public void Start()
    {
        playerRB = this.gameObject.GetComponent<Rigidbody>();
    }

    private void FixedUpdate()
    {
        float horizontal = Input.GetAxis("Horizontal");
        float vertical = Input.GetAxis("Vertical");
        Vector3 moveVector = transform.right * horizontal + transform.forward * vertical;

        playerRB.MovePosition(transform.position + moveVector.normalized * speed * Time.deltaTime);



        Ray ray = Camera.main.ScreenPointToRay(Input.mousePosition);
        RaycastHit hit;

        if (Physics.Raycast(ray, out hit, 1000))
        {
            Debug.Log("Hit" + hit.transform.name);
            Debug.DrawRay(ray.origin, ray.direction * hit.distance, Color.yellow);
        }
    }
}
