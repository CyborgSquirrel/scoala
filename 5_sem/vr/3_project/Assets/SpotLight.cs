using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class SpotLight : MonoBehaviour
{
    GameObject m_player;

    // Start is called before the first frame update
    void Start()
    {
        m_player = FindAnyObjectByType<Player>().gameObject.transform.Find("Person/Body").gameObject;
    }

    // Update is called once per frame
    void Update()
    {
        transform.LookAt(m_player.transform.position);
    }
}
