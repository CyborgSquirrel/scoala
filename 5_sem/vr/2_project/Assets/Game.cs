using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Game : MonoBehaviour
{
    GameObject trebuchet;
    // Start is called before the first frame update
    void Start()
    {
        trebuchet = GameObject.Find("Trebuchet");
    }

    // Update is called once per frame
    void Update()
    {
        
    }

    public void ActivateTrebuchet()
    {
        Trebuchet trebuchetScript = (Trebuchet)trebuchet.GetComponent<MonoBehaviour>();
        trebuchetScript.Launch();
     }
}
