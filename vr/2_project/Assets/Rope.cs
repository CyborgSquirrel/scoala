using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Rope : MonoBehaviour
{
    public GameObject attachTo;
    public Vector3 attachToAnchor;
    public Vector3 attachToAxis;

    public GameObject attachEndTo;
    public Vector3 attachEndToAnchor;
    public Vector3 attachEndToAxis;

    public float segmentSize;
    public float segmentLength;
    public float segmentSpace;
    public int segmentsNo;

    public bool breakable = false;
    public float breakForce;

    public List<GameObject> Segments { get; set; }

    // Start is called before the first frame update
    void Start()
    {
        Segments = new List<GameObject>();

        Vector3 currPosition = transform.position;
        GameObject prevSegment = null;

        for (int i = 0; i < segmentsNo+1; i++)
        {
            GameObject attacher;
            bool isAttachTo = false;
            if (i > 0)
            {
                attacher = prevSegment;
            }
            else
            {
                attacher = attachTo;
                isAttachTo = true;
            }

            GameObject attachee;
            if (i < segmentsNo)
            {
                GameObject segment;
                segment = GameObject.CreatePrimitive(PrimitiveType.Cube);
                segment.AddComponent<Rigidbody>();
                {
                    Rigidbody rigidbody = segment.GetComponent<Rigidbody>();

                    // ignore collisions with rope, to combat kraken-ification
                    rigidbody.excludeLayers |= 1 << LayerMask.NameToLayer("Rope");
                    segment.layer = LayerMask.NameToLayer("Rope");

                    rigidbody.mass = 0.0001f;
                }
                segment.transform.parent = this.transform;
                segment.transform.localScale = new Vector3(segmentSize, segmentSize, segmentLength);
                segment.transform.position = currPosition;
                currPosition.z += segmentLength + segmentSpace;

                attachee = segment;

                prevSegment = segment;

                Segments.Add(segment);
            }
            else
            {
                attachee = attachEndTo;
            }

            if (attacher != null && attachee != null)
            {
                attacher.AddComponent<HingeJoint>();
                HingeJoint hingeJoint = attacher.GetComponent<HingeJoint>();
                if (breakable)
                {
                    hingeJoint.breakForce = breakForce;
                }
                hingeJoint.connectedBody = attachee.GetComponent<Rigidbody>();
                if (isAttachTo)
                {
                    hingeJoint.axis = attachToAxis;
                    hingeJoint.anchor = attachToAnchor;
                }
                else
                {
                    hingeJoint.axis = new Vector3(0, 0, 1);
                    hingeJoint.anchor = new Vector3(0, 0, segmentLength + segmentSpace);
                }
            }
        }
    }

    // Update is called once per frame
    void Update()
    {
        
    }

    private void OnDrawGizmos()
    {
        Color color = Color.yellow;
        color.a = 0.5f;
        Gizmos.color = color;

        Vector3 size = new Vector3(segmentSize, segmentSize, (segmentLength + segmentSpace) * segmentsNo);
        Gizmos.DrawCube(transform.position + new Vector3(0, 0, size.z / 2), size);
    }
}
