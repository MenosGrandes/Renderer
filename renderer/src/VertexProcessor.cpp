#include "VertexProcessor.h"

VertexProcessor::VertexProcessor()
{
    this->view2proj=Matrix4Bfloat::Identity;
    this->world2view=Matrix4Bfloat::Identity;
    this->obj2world=Matrix4Bfloat::Identity;
    this->obj2proj=Matrix4Bfloat::Identity;
    this->obj2view=Matrix4Bfloat::Identity;

}

VertexProcessor::~VertexProcessor()
{
    //dtor
}
void VertexProcessor::setPerspective(d_type::Bfloat fovy, d_type::Bfloat aspect, const Vector2Bf& nearfar)
{
    ///KOLUMNOWO MAM!!!!
    fovy *= M_PI/ 360;
    d_type::Bfloat f=cosf(fovy)/sinf(fovy);

    view2proj=Matrix4Bfloat(
                  Vector4Bf(f/aspect,0,0,0), //1,0,0,0
                  Vector4Bf(0,f,0,0), //0,2.4190,0,0
                  Vector4Bf(0,0,(nearfar.y+nearfar.x)/(nearfar.x-nearfar.y),(2*nearfar.y*nearfar.x)/(nearfar.x-nearfar.y)),// 0,0,-1.000002,-1
                  Vector4Bf(0,0,-1,0)//0,0,-0.2,0
              );

//std::cout<<"setPerspective\n "<<view2proj;
}

void VertexProcessor::setLookat( Vector3Bf eye,  Vector3Bf center, Vector3Bf up)
{
    //DOBRZE LICZY
    Vector3Bf f= center - eye; // dobrze
    Vector3Bf::normalize(f);// dobrze
    Vector3Bf::normalize(up);// dobrze
    Vector3Bf s= Vector3Bf::cross(f,up);// dobrze
    Vector3Bf u= Vector3Bf::cross(s,f);// dobrze
    // std::cout<<f<<"\n"<<up<<"\n";
    world2view = Matrix4Bfloat(
                     Vector4Bf(s.x,s.y,s.z,-eye.x), //1,0,0,0
                     Vector4Bf(u.x,u.y,u.z,-eye.y), //0,1,0,0
                     Vector4Bf(-f.x,-f.y,-f.z,-eye.z), // 0,0,1,0
                     Vector4Bf(0,0,0,1)//0,0,-10,1
                 );
    //std::cout<<"w2v "<<world2view<<"\n";

}
void VertexProcessor::multByTranslation(const Vector3Bf& vec)
{
    Matrix4Bfloat m(
        Vector4Bf(1,0,0,vec.x),
        Vector4Bf(0,1,0,vec.y),
        Vector4Bf(0,0,1,vec.z),
        Vector4Bf(0,0,0,1)
    );

    obj2world*=m;
}

void VertexProcessor::multByScale(const Vector3Bf& vec)
{
    Matrix4Bfloat m(
        Vector4Bf(vec.x,0,0,0),
        Vector4Bf(0,vec.y,0,0),
        Vector4Bf(0,0,vec.z,0),
        Vector4Bf(0,0,0,1)
    );

    obj2world*=m;
}
void VertexProcessor::multByRotation(d_type::Bfloat a, Vector3Bf v)
{
    d_type::Bfloat s=sinf(a*M_PI/180),c=cosf(a*M_PI/180);
    Vector3Bf::normalize(v);

    Matrix4Bfloat m(
        Vector4Bf(
            v.x*v.x*(1-c)+c,
            v.x*v.y*(1-c)-v.z*s,
            v.x*v.z*(1-c)+v.y*s,
            0

        ),
        Vector4Bf(
            v.y*v.x*(1-c)+v.z*s,
            v.y*v.y*(1-c)+c,
            v.y*v.z*(1-c)-v.x*s,
            0

        ),
        Vector4Bf(
            v.x*v.z*(1-c)-v.y*s,
            v.y*v.z*(1-c)+v.x*s,
            v.z*v.z*(1-c)+c,
            0
        ),
        Vector4Bf(0,0,0,1)
    );

//    std::cout<<m<<"\n";
    obj2world*=m;//*obj2world;

}



void VertexProcessor::setIdentity()
{
    obj2world= Matrix4Bfloat::Identity;
}

void VertexProcessor::transform()
{
    obj2view= (world2view*obj2world);
    obj2proj = view2proj*obj2view;


}
void VertexProcessor::tr(const     Vertex3BfVector  v2,const int triangleCount) const
{

    // tmp_vertices.clear();
    // Vertex3Bf v;
    Vector4Bf _p,_lp,_norm;
    Vector3Bf _3norm,_3norm2;
    for(int j=0; j<triangleCount; j++)
    {
        const Vertex3Bf v=v2[j];

        //PointLight * light= new PointLight(Vector3Bf(0.0f, 0.0f, .0f));
        _p.emplace(v.m_position.x,v.m_position.y,v.m_position.z,1);
        const Vector4Bf p = obj2proj*_p;
//UJEMNA POZYCJA
        _lp.emplace(-v.m_position.x,-v.m_position.y,-v.m_position.z,1);
        const Vector4Bf lp = obj2view * _lp;
        _3norm.emplace(lp.x / lp.w, lp.y / lp.w, lp.z / lp.w);
        tmp_frag.m_negativePosToView = _3norm;


//NORMALNA
        _norm.emplace(v.m_normal.x,v.m_normal.y,v.m_normal.z,1);
        Vector4Bf normal = obj2view * _norm;
        _3norm2.emplace(normal.x / normal.w, normal.y / normal.w, normal.z / normal.w);
        tmp_frag.m_normal = _3norm2;
        //Vector3Bf::normalize(frag.m_normal);
        tmp_frag.m_normal.normalize();

        tmp_frag.m_position = v.m_position;

        Colour lightColour = Colour::Black;
        for(int i=0; i<m_lights.size(); i++)
        {
            if(m_lights[i]->m_on)
            {
                lightColour+=m_lights[i]->calculate(tmp_frag);//lightColour);
            }

        }
        lightColour=v.m_color*lightColour;

        tmp_vertices[j]=( Vertex3Bf(Vector3Bf(p.x / p.w, p.y / p.w, p.z / p.w),
                                    v.m_normal,
                                    lightColour.maxToOneReturn()));

    }

}

Vertex3Bf VertexProcessor::tr(const Vertex3Bf &v) const
{

//    Fragment frag;
    //PointLight * light= new PointLight(Vector3Bf(0.0f, 0.0f, .0f));

    const Vector4Bf p = obj2proj*Vector4Bf(v.m_position.x,v.m_position.y,v.m_position.z,1);
//UJEMNA POZYCJA
    const Vector4Bf lp = obj2view * Vector4Bf(-v.m_position.x,-v.m_position.y,-v.m_position.z,1);
    tmp_frag.m_negativePosToView = Vector3Bf(lp.x / lp.w, lp.y / lp.w, lp.z / lp.w);


//NORMALNA
    const Vector4Bf normal= obj2view * Vector4Bf(v.m_normal.x,v.m_normal.y,v.m_normal.z,1);
    tmp_frag.m_normal = Vector3Bf(normal.x / normal.w, normal.y / normal.w, normal.z / normal.w);
    Vector3Bf::normalize(tmp_frag.m_normal);


    tmp_frag.m_position = v.m_position;

    Colour lightColour = Colour::Black;
    for(int i=0; i<m_lights.size(); i++)
    {
        if(m_lights[i]->m_on)
        {
            lightColour+=m_lights[i]->calculate(tmp_frag);//lightColour);
        }

    }
    lightColour=v.m_color*lightColour;

//       Colour::maxToOne(lightColour);
    return Vertex3Bf(Vector3Bf(p.x / p.w, p.y / p.w, p.z / p.w),
                     v.m_normal,
                     lightColour.maxToOneReturn());
}
void VertexProcessor::addLight(ILight* light)
{
    m_lights.push_back(light);
}
