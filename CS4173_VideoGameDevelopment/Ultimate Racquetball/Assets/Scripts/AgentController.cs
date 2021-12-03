using UnityEngine;
using UnityEngine.AI;

public class AgentController : MonoBehaviour
{
    public GameObject Ball;
    public NavMeshAgent agent;

    // Update is called once per frame
    void Update()
    {
        agent.SetDestination(Ball.transform.position);
    }
}
