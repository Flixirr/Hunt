using UnityEngine;

public class Izometryczny : MonoBehaviour
{

    public Transform player;
    public Vector3 offset;

    void FixedUpdate()
    {
        
            transform.position = player.position  ;

    }
}
