using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class UFO : MonoBehaviour
{
    public float circleRadius;
    public float radPerUpdate;
    public float noiseStrength;

    Vector3 center;
    float circleRad = 0;

    // Start is called before the first frame update
    void Start()
    {
        center = transform.position;
    }

    // Update is called once per frame
    void Update()
    {
        
    }

    private void FixedUpdate()
    {
        // rotation
        transform.Rotate(0, 2f, 0);

        // movement
        Vector3 circlePos = new Vector3(Mathf.Cos(circleRad), 0, Mathf.Sin(circleRad));
        circlePos += new Vector3(Mathf.PerlinNoise(circlePos.x, circlePos.z), 0, Mathf.PerlinNoise(circlePos.x + 10, circlePos.z)) * noiseStrength;
        transform.position = center + circlePos * circleRadius;
        circleRad += radPerUpdate;
    }
}
