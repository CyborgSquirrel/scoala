using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class UFO : MonoBehaviour
{
    float noiseX = 0;

    // Start is called before the first frame update
    void Start()
    {
        
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
        float noiseSample = Mathf.PerlinNoise1D(noiseX);
        noiseX += 0.05f;

        float directionRad = noiseSample * Mathf.PI * 2f;
        float moveX = Mathf.Cos(directionRad);
        float moveZ = Mathf.Sin(directionRad);
        transform.Translate(new Vector3(moveX, 0, moveZ) * 0.5f);
    }
}
