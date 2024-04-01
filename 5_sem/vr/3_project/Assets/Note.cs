using System.Collections;
using System.Collections.Generic;
using TMPro;
using UnityEngine;

public class Note : MonoBehaviour
{
    public string[] topics;

    GameObject m_text;

    // Start is called before the first frame update
    void Start()
    {
        int topicIndex = Random.Range(0, topics.Length);
        string topic = topics[topicIndex];

        string text = $"Talk about...\n{topic}";
        m_text = transform.Find("Canvas/Text").gameObject;
        m_text.GetComponent<TextMeshProUGUI>().text = text;
    }

    // Update is called once per frame
    void Update()
    {
        
    }
}
