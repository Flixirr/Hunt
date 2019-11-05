using UnityEngine;

public class CameraManager : MonoBehaviour
{
    public Vector3 offset ;
    public Transform player;
    public float Screenwidth= Screen.width;
    public float Screenheight = Screen.height;
    public Rigidbody camerabody;
    public bool BlockCamera=true;
    public float XlimitL;
    public float XlimitR;
    public float ZlimitU;
    public float ZlimitD;
    public float CMForce;
   
    void Start()
    {
        transform.position = player.position + offset;
    }

    // Update is called once per frame
    void FixedUpdate()
    {
        if(Input.GetKeyDown("x"))
        {
            if (BlockCamera == true) BlockCamera = false;
            else BlockCamera = true;
        }
        //transform.LookAt(player);
        float MouseX = Input.mousePosition.x;
        float MouseZ = Input.mousePosition.y;
        float CameraZ = camerabody.position.z;
        Debug.Log(camerabody.position.x);
        if(BlockCamera==true)
        {
            camerabody.transform.LookAt(player);
            camerabody.gameObject.transform.position = player.transform.position + offset;
        }
        if (BlockCamera == false)
        {
            if ( camerabody.position.x <= XlimitR && camerabody.position.x >=XlimitL)
            {
                camerabody.constraints = RigidbodyConstraints.None;
                if (MouseX >= Screenwidth)
                {
                    camerabody.AddForce(CMForce* Time.deltaTime, 0, 0,ForceMode.VelocityChange);
                }
                if (MouseX <= 0)
                {
                    camerabody.AddForce(-CMForce* Time.deltaTime, 0, 0,ForceMode.VelocityChange);
                }
            }
            if(CameraZ<=ZlimitU && CameraZ>=ZlimitD)
            {
                camerabody.constraints = RigidbodyConstraints.None;
                if(MouseZ>=Screenheight)
                {
                    camerabody.AddForce(0, 0, CMForce * Time.deltaTime, ForceMode.VelocityChange);
                }
                if(MouseZ<=0)
                {
                    camerabody.AddForce(0, 0, -CMForce * Time.deltaTime, ForceMode.VelocityChange);
                }
            }
            if(camerabody.position.x>XlimitR)
            {
                camerabody.constraints = RigidbodyConstraints.FreezePositionX;
                camerabody.transform.Translate(-0.5f,0,0,player.transform);
            }
            if(camerabody.position.x<XlimitL)
            {
                camerabody.constraints = RigidbodyConstraints.FreezePositionX;
                camerabody.transform.Translate(0.5f, 0, 0,player.transform);
            }

            if (camerabody.position.z > ZlimitU)
            {
                camerabody.constraints = RigidbodyConstraints.FreezePositionZ;
                camerabody.transform.Translate(0, 0, -0.5f, player.transform);
            }
            if (camerabody.position.z < ZlimitD)
            {
                camerabody.constraints = RigidbodyConstraints.FreezePositionZ;
                camerabody.transform.Translate(0, 0, 0.5f,player.transform);
            }
        }

    }
}
