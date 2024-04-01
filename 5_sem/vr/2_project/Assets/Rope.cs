using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Rope : MonoBehaviour
{
    public Object ropePrefab;

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
        MakeSegments(SegmentsAction.Create);
    }

    enum SegmentsAction { Draw, Create };
    void MakeSegments(SegmentsAction action)
    {
        Vector3 currPosition = Vector3.zero;
        GameObject prevSegment = null;

        for (int i = 0; i < segmentsNo + 1; i++)
        {
            GameObject attacher = null;
            bool isAttachTo = false;
            if (action == SegmentsAction.Create)
            {
                if (i > 0)
                {
                    attacher = prevSegment;
                }
                else
                {
                    attacher = attachTo;
                    isAttachTo = true;
                }
            }

            GameObject attachee = null;
            if (i < segmentsNo)
            {
                GameObject segment = null;
                if (action == SegmentsAction.Create)
                {
                    //segment = GameObject.CreatePrimitive(PrimitiveType.Cube);
                    segment = (GameObject)Instantiate(ropePrefab);
                    segment.AddComponent<Rigidbody>();
                    {
                        Rigidbody rigidbody = segment.GetComponent<Rigidbody>();

                        // ignore collisions with rope, to combat kraken-ification
                        rigidbody.excludeLayers |= 1 << LayerMask.NameToLayer("Rope");
                        segment.layer = LayerMask.NameToLayer("Rope");

                        rigidbody.mass = 0.0001f;
                    }
                    segment.transform.SetParent(transform, false);
                    segment.transform.localScale = new Vector3(segmentSize, segmentSize, segmentLength);
                    segment.transform.position = transform.TransformPoint(currPosition);

                    attachee = segment;

                    prevSegment = segment;

                    Segments.Add(segment);
                }
                else if (action == SegmentsAction.Draw)
                {
                    Gizmos.DrawCube(currPosition, new Vector3(segmentSize, segmentSize, segmentLength));
                }
                currPosition.z += segmentLength + segmentSpace;
            }
            else
            {
                attachee = attachEndTo;
            }

            if (action == SegmentsAction.Create)
            {
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

        Gizmos.matrix = transform.localToWorldMatrix;
        MakeSegments(SegmentsAction.Draw);;
    }
}
