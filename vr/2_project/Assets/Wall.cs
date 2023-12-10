using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Wall : MonoBehaviour
{
    public Object blockPrefab;

    public int width;
    public int height;

    public float blockWidth;
    public float blockHeight;
    public float blockDepth;

    public float blockSpace;

    public float blockMass;

    Vector3 blockSize;

    void Initialize()
    {
        blockSize = new Vector3(blockWidth, blockHeight, blockDepth);
    }

    private void Awake()
    {
        Initialize();
    }

    void OnValidate()
    {
        Initialize();
    }

    // Start is called before the first frame update
    void Start()
    {
        MakeBlocks(BlocksAction.Create);
    }

    // Update is called once per frame
    void Update()
    {
        
    }

    enum BlocksAction { Draw, Create };
    void MakeBlocks(BlocksAction action)
    {
        Vector3 currPos0 = Vector3.zero;
        for (int y = 0; y < height; y++)
        {
            Vector3 currPos1 = currPos0;
            if (y % 2 == 1)
            {
                currPos1.x += blockSize.x / 2;
            }

            int currEndX = width-1;
            int currStartX = 0;

            // make sure that a block won't instantly fall from the top-most row
            if (y == height-1)
            {
                if (height % 2 == 0)
                {
                    currEndX -= 1;
                } else
                {
                    currStartX += 1;
                }
            }

            for (int x = 0; x < width; x++)
            {
                if (x >= currStartX && x <= currEndX)
                {

                    switch (action)
                    {
                        case BlocksAction.Draw:
                            {
                                Gizmos.DrawCube(currPos1 + new Vector3(blockWidth, blockHeight) / 2, blockSize);
                                break;
                            }
                        case BlocksAction.Create:
                            {
                                GameObject blockObj = (GameObject)Instantiate(blockPrefab);
                                blockObj.transform.SetParent(transform, false);
                                blockObj.transform.localScale = blockSize;
                                blockObj.transform.position = transform.TransformPoint(currPos1 + new Vector3(blockWidth, blockHeight) / 2);

                                {
                                    Rigidbody rigidbody = blockObj.AddComponent<Rigidbody>();
                                    rigidbody.mass = blockMass;
                                }

                                break;
                            }
                    }
                }
                currPos1.x += blockSize.x;
                currPos1.x += blockSpace;
            }
            currPos0.y += blockSize.y;
            currPos0.y += blockSpace;
        }
    }

    public void OnDrawGizmos()
    {
        Color color = Color.red;
        color.a = 0.5f;
        Gizmos.color = color;
        Gizmos.matrix = this.transform.localToWorldMatrix;

        MakeBlocks(BlocksAction.Draw);
    }
}
