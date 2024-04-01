using System.Collections;
using System.Collections.Generic;
using Unity.VisualScripting;
using UnityEngine;

public class Trebuchet : MonoBehaviour
{
    public float launchForce;
    public float detachDelaySeconds;

    GameObject pivotObj;
    GameObject ropeObj;

    // Start is called before the first frame update
    void Start()
    {
        pivotObj = transform.Find("Base/Pivot/Cube").gameObject;
        Rigidbody rigidbody = pivotObj.GetComponent<Rigidbody>();
        rigidbody.maxAngularVelocity = 100;

        ropeObj = transform.Find("Rope").gameObject;

        //Launch();
    }

    // Update is called once per frame
    void Update()
    {

    }

    public void Launch()
    {
        StartCoroutine(LaunchCoro());
    }

    IEnumerator LaunchCoro()
    {
        {
            Rigidbody rigidbody = pivotObj.GetComponent<Rigidbody>();
            rigidbody.AddRelativeTorque(new Vector3(1, 0, 0) * launchForce, ForceMode.Impulse);
        }

        yield return new WaitForSeconds(detachDelaySeconds);

        {
            Rope rope = ropeObj.GetComponent<Rope>();
            GameObject segment = rope.Segments[^1];
            HingeJoint hingeJoint = segment.GetComponent<HingeJoint>();
            Destroy(hingeJoint);
        }
    }
}
