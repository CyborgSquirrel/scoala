using System.Collections;
using System.Collections.Generic;
using TMPro;
using UnityEngine;
using UnityEngine.SceneManagement;
using UnityEngine.UI;

public class LevelButton : MonoBehaviour
{
    public int level;
    public string name;

    Button m_button;
    TextMeshProUGUI m_text;

    // Start is called before the first frame update
    void Start()
    {
        m_button = GetComponent<Button>();
        m_button.onClick.AddListener(() =>
        {
            SceneManager.LoadScene("Scenes/Level" + level);
        });

        GameObject text = transform.Find("Text").gameObject;
        m_text = text.GetComponent<TextMeshProUGUI>();
        m_text.text = "Level " + level + ": " + name;
    }

    // Update is called once per frame
    void Update()
    {
        
    }
}
