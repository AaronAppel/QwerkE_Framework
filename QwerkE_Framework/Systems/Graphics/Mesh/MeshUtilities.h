#ifndef _MeshUtilities_H_
#define _MeshUtilities_H_

#include "../../../../QwerkE_Common/Math_Includes.h"
#include "VertexData.h"
#include <vector>

/* Mesh modifications */
// scale
void ScaleUVCOORDS(VertexData verts[], int numVerts, vec2 UVScale);
void ScaleVertices(VertexData verts[], int numVerts, vec3 scale);

// Auto UVs
void CalculateXZUVCoords(VertexData vertArray[], int numVertices);
void CalculateUVCoords(std::vector<VertexData> &verts);
void CalculateUVCoords(VertexData verts[], int numVertices);

// Color
void PaintObject(std::vector<VertexData> &verts, vec4 color); // vertex color

// Edit IBO
void InvertFaces(unsigned int oldIBO[], unsigned int arraySize); // reverse winding order

#endif //!_MeshUtilities_H_
