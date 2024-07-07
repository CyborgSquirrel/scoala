using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class AntennaTopper : MonoBehaviour
{
    private float elapsed = 0;

    private Renderer renderer;

    // Start is called before the first frame update
    void Start()
    {
        renderer = GetComponent<Renderer>();
    }

    // Update is called once per frame
    void Update()
    {
        elapsed += Time.deltaTime;

        //material = renderer.material;
        renderer.material.SetColor("_Color", new Color((elapsed % 2) / 2, 0, 0));
    }
}
