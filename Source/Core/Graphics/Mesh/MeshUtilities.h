#ifndef _MeshUtilities_H_
#define _MeshUtilities_H_

#include "MeshData.h"
#include <vector>

namespace QwerkE {

    /* Mesh modifications */
    // Scaling
    void ScaleUVCOORDS(std::vector<vec2>& verts, vec2 UVScale);
    void ScaleVertices(std::vector<vec3>& verts, vec3 scale);

    // Auto UV helpers
    void CalculateXZUVCoords(MeshData& data);
    void CalculateUVCoords(std::vector<vec2>& UVs);
    void CalculateUVCoords(std::vector<vec3>& vertArray, int numVertices);

    // Color
    void PaintObject(MeshData& colors, vec4 color); // vertex color

    // Edit IBO
    void InvertFaces(unsigned int oldIBO[], unsigned int arraySize); // reverse winding order

    // Tangents and bitangents
    void GenerateTangents();
    void GenerateBitangents();

}
#endif //!_MeshUtilities_H_
