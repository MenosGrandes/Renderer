#ifndef VERTEXPROCESSOR_H
#define VERTEXPROCESSOR_H
#include "Vertex3.h"
#include "Vector2.h"
#include "Matrix4.h"
#include "Fragment.h"
#include "DirectionalLight.h"
#include "PointLight.h"
#include "SpotLight.h"
#include <vector>
class VertexProcessor
{
public:
    VertexProcessor();
    virtual ~VertexProcessor();
    void setPerspective(d_type::Bfloat fovy, d_type::Bfloat aspect, const Vector2Bf& nearfar);
    void setLookat( Vector3Bf eye,  Vector3Bf center, Vector3Bf up);
    void multByTranslation(const Vector3Bf& vec);
    void multByScale(const Vector3Bf& vec);
    void multByRotation(d_type::Bfloat a,Vector3Bf vec);

    void setIdentity();
    void transform();
    Vertex3Bf tr(const Vertex3Bf &v) const;
void tr(const std::vector<Vertex3Bf> v2,const int triangleCount) const;

    void addLight(ILight * light);

    Matrix4Bfloat view2proj,world2view,obj2world,obj2proj,obj2view;
    std::vector<ILight*> m_lights;

    mutable std::vector<Vertex3Bf> tmp_vertices;
};

#endif // VERTEXPROCESSOR_H
