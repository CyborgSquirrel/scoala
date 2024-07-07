using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Person : MonoBehaviour
{
    [HideInInspector]
    public Vector2 move;

    Rigidbody m_rigidbody;
    Collider m_collider;

    // Start is called before the first frame update
    void Start()
    {
        m_rigidbody = GetComponent<Rigidbody>();
        m_collider = GetComponent<CapsuleCollider>();

        move = Vector2.zero;
    }

    // Update is called once per frame
    void Update()
    {

    }

    private void FixedUpdate()
    {
        m_rigidbody.velocity = new Vector3(move.x, m_rigidbody.velocity.y, move.y);
    }
}
