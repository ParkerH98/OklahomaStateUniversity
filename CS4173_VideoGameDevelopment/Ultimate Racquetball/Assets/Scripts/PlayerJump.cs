using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PlayerJump : MonoBehaviour
{
    Rigidbody rb;
    [SerializeField] Transform groundChecker;
    [SerializeField] float checkRadius;
    [SerializeField] LayerMask groundLayer;
    [SerializeField] float jumpForce;

    void Start()
    {
        rb = GetComponent<Rigidbody>();
    }


    void Update()
    {
        if (Input.GetKeyDown(KeyCode.Space) && IsOnGround())
        {
            rb.AddForce(Vector3.up * jumpForce, ForceMode.Impulse);
        }
    }


    bool IsOnGround()
    {
        Collider[] colliders = Physics.OverlapSphere(groundChecker.position, checkRadius, groundLayer);
        if (colliders.Length > 0)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
}
