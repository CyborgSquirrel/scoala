using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.Events;

public class PressurePlate : MonoBehaviour
{
    public float delaySeconds;
    public float depressSpeed;
    public UnityEvent onActivated;

    HashSet<int> gameObjectsInTrigger;
    bool runningCoro = false;

    GameObject cube;
    float cubeRaised = 0;
    float cubeDepressed = -0.075f;

    private void Awake()
    {
        gameObjectsInTrigger = new HashSet<int>();
        cube = transform.Find("Cube").gameObject;
    }

    // Start is called before the first frame update
    void Start()
    {
        
    }

    // Update is called once per frame
    void FixedUpdate()
    {
        {
            float cubeTarget;
            if (gameObjectsInTrigger.Count <= 0)
            {
                cubeTarget = cubeRaised;
            } else
            {
                cubeTarget = cubeDepressed;
            }

            Vector3 cubePos = cube.transform.localPosition;
            float cubeDelta = cubeTarget - cubePos.y;
            float cubeTrans = Mathf.Min(Mathf.Abs(cubeDelta), depressSpeed) * Mathf.Sign(cubeDelta);
            cubePos.y += cubeTrans;
            cube.transform.localPosition = cubePos;
        }
    }

    private void OnTriggerEnter(Collider other)
    {
        if (!runningCoro)
        {
            StartCoroutine(ActivateCoro());
        }

        gameObjectsInTrigger.Add(other.gameObject.GetInstanceID());
    }

    private void OnTriggerExit(Collider other)
    {
        gameObjectsInTrigger.Remove(other.gameObject.GetInstanceID());
    }

    IEnumerator ActivateCoro()
    {
        runningCoro = true;

        yield return new WaitForSeconds(delaySeconds);

        if (gameObjectsInTrigger.Count >= 0)
        {
            onActivated.Invoke();
        }

        runningCoro = false;
    }
}
