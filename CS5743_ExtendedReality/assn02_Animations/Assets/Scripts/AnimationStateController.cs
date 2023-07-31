using System.Collections;
using System.Collections.Generic;
using UnityEngine;
// using UnityEngine.InputSystem;


public class AnimationStateController : MonoBehaviour
{
    Animator animator;

    // Start is called before the first frame update
    void Start()
    {
        animator = GetComponent<Animator>();
    }

    // Update is called once per frame
    void Update()
    {
        bool isWalking = animator.GetBool("isWalking");
        bool isRunning = animator.GetBool("isRunning");
        bool isDancing = animator.GetBool("isDancing");

        bool pressedW = Input.GetKey("w");
        bool pressedQ = Input.GetKey("q");
        bool pressedE = Input.GetKey("e");


        if (TargetActive.active == true){

            

            if (!isWalking && pressedW){

                animator.SetBool("isWalking", true);
            } 

            if (isWalking && !pressedW){

                animator.SetBool("isWalking", false);
            } 

            if (!isRunning && (pressedW && pressedQ)){

                animator.SetBool("isRunning", true);
            }

            if (isRunning && (!pressedW || !pressedQ)){

                animator.SetBool("isRunning", false);
            }

            if ( !isWalking && Input.GetKey("e")){

                animator.SetBool("isDancing", true);
            } 

            if ( isDancing && !pressedE){

                animator.SetBool("isDancing", false);
            }

            if (isWalking && !pressedW){

                animator.SetBool("isWalking", false);
            } 
        }

        else{

            animator.SetBool("isWalking", false);
            animator.SetBool("isDancing", false);
            animator.SetBool("isRunning", false);
        }
    }
}
