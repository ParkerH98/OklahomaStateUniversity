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
    }
}
