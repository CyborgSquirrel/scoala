using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public enum GameState
{
    BeforePresentation,
    Presenting,
    AfterPresentation,
}

public class Game : MonoBehaviour
{
    public AudioClip backgroundNoise;
    public AudioClip applauseSound;

    IEnumerator m_fadeOut;

    AudioSource m_audioSource;
    GameState m_state;
    GameState? m_prevState;

    Canvas m_canvasPresenting;

    public GameState State { get => m_state; }

    // Start is called before the first frame update
    void Start()
    {
        m_state = GameState.BeforePresentation;

        m_audioSource = GetComponent<AudioSource>();

        m_canvasPresenting = transform.Find("CanvasPresenting").GetComponent<Canvas>();
        m_canvasPresenting.enabled = false;
    }

    // Update is called once per frame
    void Update()
    {
        GameState currentState = m_state;

        bool stateChange = m_prevState != m_state;

        if (stateChange)
        {
            switch (m_state)
            {
                case GameState.BeforePresentation:
                    {
                        m_audioSource.loop = true;
                        m_audioSource.clip = backgroundNoise;
                        m_audioSource.Play();

                        break;
                    }
                case GameState.AfterPresentation:
                    {
                        m_canvasPresenting.enabled = false;

                        if (m_fadeOut != null)
                        {
                            StopCoroutine(m_fadeOut);
                        }

                        m_audioSource.loop = false;
                        m_audioSource.volume = 0.5f;
                        m_audioSource.clip = applauseSound;
                        m_audioSource.Play();

                        break;
                    }
            }
        }

        switch (m_state)
        {
            case GameState.BeforePresentation:
                {
                    m_canvasPresenting.enabled = false;
                    if (Input.GetKeyUp(KeyCode.Return))
                    {
                        m_state = GameState.Presenting;
                        m_fadeOut = FadeOut(m_audioSource, 1f);
                        StartCoroutine(m_fadeOut);
                    }
                    break;
                }
            case GameState.Presenting:
                {
                    m_canvasPresenting.enabled = true;
                    if (Input.GetKeyUp(KeyCode.Return))
                    {
                        m_state = GameState.AfterPresentation;
                    }
                    break;
                }
            case GameState.AfterPresentation:
                {
                    break;
                }
        }

        m_prevState = currentState;
    }

    static IEnumerator FadeOut(AudioSource audioSource, float time)
    {
        float startVolume = audioSource.volume;

        while (audioSource.volume > 0)
        {
            audioSource.volume -= startVolume * Time.deltaTime / time;

            yield return null;
        }

        audioSource.Stop();
    }
}
