using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Robot : MonoBehaviour
{
    public float speed;

    Vector2 point;

    // Start is called before the first frame update
    void Start()
    {
        point = new Vector2(-6.65f, -26.7f);
    }

    // Update is called once per frame
    void FixedUpdate()
    {
        Vector2 delta = point - new Vector2(transform.position.x, transform.position.z);
        float dist = delta.magnitude;
        if (dist > 0.0001)
        {
            Vector2 vel = delta / dist;
            float mag = Mathf.Min(speed, dist);
            transform.position = transform.position + new Vector3(vel.x, 0, vel.y) * mag;
        } else
        {
            Animation animation = GetComponent<Animation>();
            animation.Stop();
        }
    }
}
