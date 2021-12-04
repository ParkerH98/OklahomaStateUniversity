using UnityEngine;
using UnityEngine.AI;

public class AgentController : MonoBehaviour
{
    public GameObject Ball;
    public NavMeshAgent agent;

    void Update()
    {
        agent.SetDestination(Ball.transform.position);
    }
}
