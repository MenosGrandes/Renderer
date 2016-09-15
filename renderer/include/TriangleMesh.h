#ifndef TRIANGLEMESH_H
#define TRIANGLEMESH_H
#include <vector>
#include <string>
#include <stdio.h>
#include <string.h>
#include <algorithm>
#include "Vertex3.h"
#include "VertexProcessor.h"
#include "RenderTarget.h"
using namespace d_type;
namespace render
{
class TriangleMesh
{
public:
    TriangleMesh() {}
    virtual ~TriangleMesh() {}
    void draw(const VertexProcessor &vp,const RenderTarget &rt) const;
    void calcNormals();
    void loadOBJ(std::string filename);


    int m_vertSize,m_triangleCount;
    Vertex3BfVector  m_vertices;

    Vector3BiVector m_indices;
//     Colour m_colour;
};
}
#endif // TRIANGLEMESH_H
