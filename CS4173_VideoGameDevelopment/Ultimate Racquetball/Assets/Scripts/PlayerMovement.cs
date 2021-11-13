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
        // Vector3 moveVector = new Vector3(Input.GetAxis("Horizontal"), 0, Input.GetAxis("Vertical"));


        // playerRB.MovePosition(transform.position + moveVector.normalized * speed * Time.deltaTime);
        playerRB.MovePosition(transform.position + moveVector * speed * Time.deltaTime);

    }
}
