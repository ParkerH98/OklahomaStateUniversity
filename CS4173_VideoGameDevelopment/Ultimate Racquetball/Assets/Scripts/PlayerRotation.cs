using UnityEngine;

public class PlayerRotation : MonoBehaviour
{
    [SerializeField] Transform cam;
    [SerializeField] float sensitivity;
    [SerializeField] float headRotationLimit = 90f;
    float headRotation = 0f;

    void Start()
    {
        Cursor.visible = false;
        Cursor.lockState = CursorLockMode.Locked;
    }

    void Update()
    {
        float horizontal = Input.GetAxis("Mouse X") * sensitivity * Time.deltaTime;
        float vertical = Input.GetAxis("Mouse Y") * sensitivity * Time.deltaTime * -1f;
        transform.Rotate(0f, horizontal, 0f);
        headRotation += vertical;
        headRotation = Mathf.Clamp(headRotation, -headRotationLimit, headRotationLimit);
        cam.localEulerAngles = new Vector3(headRotation, 0f, 0f);
    }
}
