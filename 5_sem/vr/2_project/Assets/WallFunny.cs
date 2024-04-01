using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class WallFunny : MonoBehaviour
{
    private void Awake()
    {
    }

    // Start is called before the first frame update
    void Start()
    {
    }

    // Update is called once per frame
    void Update()
    {
        
    }

    private void OnTriggerEnter(Collider other)
    {
        AudioSource audioSource = GetComponent<AudioSource>();
        audioSource.Play();
    }
}
