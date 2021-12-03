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


        // Vector3 inputVector = new Vector3(horizontal, 0, Input.GetAxisRaw("Vertical"));
        // playerRB.velocity = (inputVector  * speed) + new Vector3(0, playerRB.velocity.y, 0);


    }

    // public void Update()
    // {
    // 	float horizontalInput = Input.GetAxis("Horizontal");
    // 	float verticalInput = Input.GetAxis("Vertical");

    // 	Vector3 movement = new Vector3(horizontalInput, verticalInput, 0);
    // 	movement = movement.normalized * speed * Time.deltaTime;

    // 	transform.position += movement;
    // }
}
