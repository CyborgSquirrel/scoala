using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Player : MonoBehaviour
{
    public float sensitivityHor;
    public float sensitivityVer;
    public float speed;

    GameObject m_player;
    GameObject m_playerHead;
    GameObject m_note;
    Collider m_collider;
    Person m_person;

    // Start is called before the first frame update
    void Start()
    {
        // setting this here is kinda sussy
        Cursor.lockState = CursorLockMode.Locked;
        Camera.main.cullingMask |= 1 << LayerMask.NameToLayer("Player");

        m_player = transform.Find("Person").gameObject;
        m_playerHead = transform.Find("Person/Head").gameObject;
        m_note = transform.Find("Person/Note").gameObject;
        m_collider = m_player.GetComponent<CapsuleCollider>();
        m_person = m_player.GetComponent<Person>();
    }

    // Update is called once per frame
    void Update()
    {

    }

    private void FixedUpdate()
    {
        //bool isGrounded = Physics.Raycast(
        //    m_player.transform.position,
        //    Vector3.down,
        //    m_collider.bounds.extents.y + 0.1f);

        Camera camera = Camera.main;

        //camera.transform.rotation.eulerAngles.y;

        // movement
        {
            float moveHor = Input.GetAxis("Horizontal");
            float moveVer = Input.GetAxis("Vertical");

            float rot = -camera.transform.rotation.eulerAngles.y;
            Vector2 basisHor = new Vector2(Mathf.Cos(rot / 360 * Mathf.PI * 2), Mathf.Sin(rot / 360 * Mathf.PI * 2));
            Vector2 basisVer = new Vector2(-basisHor.y, basisHor.x);

            m_person.move = (basisHor * moveHor + basisVer * moveVer) * speed * Time.deltaTime;
        }

        // camera position
        //camera.transform.position = m_playerHead.transform.position;

        // camera rotation
        float rotateHor = Input.GetAxis("Mouse X") * sensitivityHor;
        float rotateVer = -Input.GetAxis("Mouse Y") * sensitivityVer;
        camera.transform.eulerAngles += new Vector3(rotateVer, rotateHor, 0);

        m_note.transform.eulerAngles = new Vector3(0, camera.transform.eulerAngles.y, 0);
    }
}
