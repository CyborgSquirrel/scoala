using System.Collections;
using System.Collections.Generic;
using System.Net.NetworkInformation;
using System.Resources;
using Unity.VisualScripting;
using UnityEditor;
using UnityEngine;
using UnityEngine.SocialPlatforms;

public class AudienceMember : MonoBehaviour
{
    public float headRotationSpeed;
    public bool doesSocialize;

    private static Color m_skinColor0 = new Color(224f/255f, 172f/255f, 105f/255f);
    private static Color m_skinColor1 = new Color(255f/255f, 219f/255f, 172f/255f);

    private static Color[] m_bodyColors =
    {
        new Color(173f/255f, 216f/255f, 230f/255f), // Light Blue
        new Color(152f/255f, 255f/255f, 152f/255f), // Mint Green
        new Color(230f/255f, 230f/255f, 250f/255f), // Lavender
        new Color(255f/255f, 218f/255f, 185f/255f), // Peachy Pink
        new Color(255f/255f, 255f/255f, 153f/255f), // Pale Yellow
        new Color(144f/255f, 238f/255f, 144f/255f), // Soft Green
        new Color(204f/255f, 204f/255f, 255f/255f), // Periwinkle
        new Color(240f/255f, 128f/255f, 128f/255f), // Light Coral
    };

    // lazy-loaded face textures
    private static Texture2D[] m_faceTextures;
    private static Texture2D[] FaceTextures
    {
        get
        {
            if (m_faceTextures == null)
            {
                m_faceTextures = Resources.LoadAll<Texture2D>("Faces");
            }
            return m_faceTextures;
        }
    }

    private Game m_game;
    private GameState? m_prevGameState;

    private GameObject m_playerHead;

    private GameObject m_person;
    private GameObject m_head;
    private Animation m_headAnimation;

    private IEnumerator? m_socialize;

    // Start is called before the first frame update
    void Start()
    {
        m_person = transform.Find("Person").gameObject;
        m_head = transform.Find("Person/Head").gameObject;
        m_headAnimation = m_head.GetComponent<Animation>();
        
        // head color
        {
            Material headMaterial = m_head.GetComponent<Renderer>().material;

            float t = Random.value;
            headMaterial.color = m_skinColor0 * t + m_skinColor1 * (1-t);
        }

        // body color
        {
            GameObject body = transform.Find("Person/Body").gameObject;
            Material bodyMaterial = body.GetComponent<Renderer>().material;
            bodyMaterial.color = m_bodyColors[Random.Range(0, m_bodyColors.Length)];
        }

        // face texture
        {
            GameObject face = transform.Find("Person/Head/Face").gameObject;
            Renderer renderer = face.GetComponent<Renderer>();
            renderer.material.SetTexture("_MainTex", FaceTextures[Random.Range(0, FaceTextures.Length)]);
        }
        
        m_socialize = null;
        m_game = FindAnyObjectByType<Game>();
        m_playerHead = FindAnyObjectByType<Player>().gameObject.transform.Find("Person/Head").gameObject;
    }

    // Update is called once per frame
    void Update()
    {
        //if (m_game.State != GameState.BeforePresentation)
        //{
        //    if (m_socialize != null)
        //    {
        //        StopCoroutine(m_socialize);
        //        m_socialize = null;
        //    }
        //}

        bool stateChange = m_game.State != m_prevGameState;

        if (stateChange)
        {
            switch (m_prevGameState)
            {
                case GameState.BeforePresentation:
                    {
                        if (doesSocialize)
                        {
                            StopCoroutine(m_socialize);
                        }
                        break;
                    }
            }

            switch (m_game.State)
            {
                case GameState.BeforePresentation:
                    {
                        if (doesSocialize)
                        {
                            m_socialize = Socialize();
                            StartCoroutine(m_socialize);
                        }
                        break;
                    }
            }
        }

        switch (m_game.State)
        {
            case GameState.BeforePresentation:
                {
                    break;
                }
            case GameState.Presenting:
                {
                    Quaternion lookRotation = Quaternion.LookRotation(m_playerHead.transform.position - m_head.transform.position);
                    m_head.transform.rotation = Quaternion.RotateTowards(m_head.transform.rotation, lookRotation, headRotationSpeed * Time.deltaTime);
                    break;
                }
            case GameState.AfterPresentation:
                {
                    Quaternion lookRotation = Quaternion.LookRotation(m_playerHead.transform.position - m_head.transform.position);
                    m_head.transform.rotation = Quaternion.RotateTowards(m_head.transform.rotation, lookRotation, headRotationSpeed * Time.deltaTime);
                    break;
                }
        }

        m_prevGameState = m_game.State;
    }

    private void OnDrawGizmos()
    {
        Color gizmosColor = Color.green;
        gizmosColor.a = 0.2f;
        Gizmos.color = gizmosColor;
        
        Gizmos.matrix = transform.localToWorldMatrix;
        
        //Gizmos.DrawSphere(Vector3.zero, interactionRadius);
    }

    IEnumerator Socialize()
    {
        // this feels like quite a hack
        // but it also seems to work
        // soo... that means it's good :)
        AnimationClip[] animationClips = Resources.LoadAll<AnimationClip>("HeadAnim");
        while (true)
        {
            AnimationClip animationClip = animationClips[Random.Range(0, animationClips.Length)];
            m_headAnimation.clip = animationClip;
            m_headAnimation.Play();
            yield return new WaitForSeconds(animationClip.length);
        }
    }

    //IEnumerator Socialize()
    //{
    //    while (true)
    //    {
    //        Collider[] colliders = Physics.OverlapSphere(transform.position, interactionRadius, LayerMask.NameToLayer("Audience"));

    //        int gameObjectsLength = colliders.Length;
    //        GameObject[] gameObjects = new GameObject[gameObjectsLength];
    //        {
    //            int gameObjectsI = 0;
    //            for (int collidersI = 0; collidersI < colliders.Length; ++collidersI)
    //            {
    //                GameObject gameObject = colliders[collidersI].gameObject;

    //                // don't try to socialize with yourself :))
    //                if (gameObject == m_person)
    //                {
    //                    gameObjectsLength--;
    //                    continue;
    //                }

    //                gameObjects[gameObjectsI] = gameObject;
    //                gameObjectsI++;
    //            }
    //        }

    //        if (gameObjectsLength > 0)
    //        {
    //            GameObject gameObject = gameObjects[Random.Range(0, gameObjectsLength)];
    //            // fuk
    //            // they should really look at eachother
    //            // TODO: this
    //        }

    //        yield return new WaitForSeconds(1);
    //    }
    //}
}
