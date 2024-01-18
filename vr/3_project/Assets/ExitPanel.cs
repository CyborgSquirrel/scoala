using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;
using UnityEngine.UI;

public class ExitPanel : MonoBehaviour
{
    private Canvas m_canvas;
    private CursorLockMode? m_lockMode;

    private bool m_enabled
    {
        get { return m_canvas.enabled; }
        set
        {
            if (m_canvas.enabled == value)
            {
                return;
            }

            if (!m_canvas.enabled)
            {
                m_lockMode = Cursor.lockState;
                Cursor.lockState = CursorLockMode.None;
            }
            if (m_canvas.enabled)
            {
                if (m_lockMode != null)
                {
                    Cursor.lockState = (CursorLockMode)m_lockMode;
                    m_lockMode = null;
                }
            }
            m_canvas.enabled = value;
        }
    }

    // Start is called before the first frame update
    void Start()
    {
        m_canvas = GetComponent<Canvas>();
        m_canvas.enabled = false;

        GameObject buttonYes = transform.Find("Panel/ButtonYes").gameObject;
        Button buttonYesButton = buttonYes.GetComponent<Button>();
        buttonYesButton.onClick.AddListener(() =>
        {
            SceneManager.LoadScene("Scenes/MainMenu");
        });

        GameObject buttonNo = transform.Find("Panel/ButtonNo").gameObject;
        Button buttonNoButton = buttonNo.GetComponent<Button>();
        buttonNoButton.onClick.AddListener(() =>
        {
            m_enabled = false;
        });
    }

    // Update is called once per frame
    void Update()
    {
        if (Input.GetKeyUp(KeyCode.Escape))
        {
            m_enabled = !m_enabled;
        }
    }
}
