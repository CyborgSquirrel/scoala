using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class UI : MonoBehaviour
{
    GameObject trebuchet;
    void Start()
    {
        trebuchet = GameObject.Find("Trebuchet");
    }

    public void Pandemonium()
    {
        Trebuchet trebuchetScript = (Trebuchet) trebuchet.GetComponent<MonoBehaviour>();
        trebuchetScript.Launch();
    }
}
