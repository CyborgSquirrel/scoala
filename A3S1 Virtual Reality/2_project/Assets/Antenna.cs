using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Antenna : MonoBehaviour
{
    Vector3 minScale = new Vector3(1, 1, 1);
    Vector3 maxScale = new Vector3(1, 2, 1);

    public GameObject ufo;
    GameObject stick;

    // Start is called before the first frame update
    void Start()
    {
        stick = this.transform.Find("Base/Stick").gameObject;
    }

    // Update is called once per frame
    void Update()
    {
        
    }

    private void FixedUpdate()
    {
        // look at the ufo
        transform.LookAt(ufo.transform.position);

        // scale based on ufo distance
        // 15-20
        float ufoDist = Vector3.Distance(transform.position, ufo.transform.position);
        float t = Mathf.Clamp01((ufoDist - 15) / 10);
        
        stick.transform.localScale = Vector3.Lerp(minScale, maxScale, t);
    }
}
