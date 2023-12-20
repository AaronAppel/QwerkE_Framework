#ifndef _Mesh_Data_H_
#define _Mesh_Data_H_

#include <vector>

#include "../../Math/Vector.h"

namespace QwerkE {

    struct MeshBufferInfo
    {
        unsigned int numPositions = 0;
        unsigned int numIndices = 0;
        unsigned int numColors = 0;
        unsigned int numUVs = 0;
        unsigned int numNormals = 0;
        unsigned int numTangents = 0;
        unsigned int numBitangents = 0;

        unsigned int SingleVertexByteSize() // Size in bytes of each value * 1 summed
        {
            return sizeof(numPositions) +
                sizeof(numColors) +
                sizeof(numUVs) +
                sizeof(numNormals) +
                sizeof(numTangents) +
                sizeof(numBitangents);
        }

        unsigned int BufferSize() { return BitangentsOffset() + sizeof(vec3) * numBitangents; }

        unsigned int PositionOffset() { return 0; } // Point to start of data (index 0)
        unsigned int ColorOffset() { return sizeof(vec3) * numPositions; } // Number of bytes positions take
        unsigned int UVOffset() { return ColorOffset() + (sizeof(vec4) * numColors); } // Number of bytes positions take + Offset of colors and positions
        unsigned int NormalOffset() { return UVOffset() + (sizeof(vec2) * numUVs); }
        unsigned int TangentsOffset() { return NormalOffset() + (sizeof(vec3) * numNormals); }
        unsigned int BitangentsOffset() { return TangentsOffset() + (sizeof(vec3) * numTangents); }
    };

    struct MeshData
    {
        std::vector<unsigned int> indices;

        std::vector<vec3> positions;
        std::vector<vec4> colors;
        std::vector<vec2> UVs;
        std::vector<vec3> normals;
        std::vector<vec3> tangents;
        std::vector<vec3> bitangents;

        MeshData() {};
        // pos, uv
        MeshData(std::vector<vec3> a_Positions, std::vector<vec2> a_UVs)
        {
            positions = a_Positions;
            UVs = a_UVs;
        }
        // pos, uv, norm
        MeshData(std::vector<vec3> a_Positions, std::vector<vec2> a_UVs, std::vector<vec3> a_Normals)
        {
            positions = a_Positions;
            UVs = a_UVs;
            normals = a_Normals;
        }
        // pos, uv, norm, tan, bitan
        MeshData(std::vector<vec3> a_Positions, std::vector<vec2> a_UVs, std::vector<vec3> a_Normals, std::vector<vec3> a_Tangents, std::vector<vec3> a_Bitangents)
        {
            positions = a_Positions;
            UVs = a_UVs;
            normals = a_Normals;
            tangents = a_Tangents;
            bitangents = a_Bitangents;
        }
        // All
        MeshData(std::vector<vec3> a_Positions, std::vector<vec4> a_Colors, std::vector<vec2> a_UVs, std::vector<vec3> a_Normals, std::vector<vec3> a_Tangents, std::vector<vec3> a_Bitangents)
        {
            positions = a_Positions;
            colors = a_Colors;
            UVs = a_UVs;
            normals = a_Normals;
            tangents = a_Tangents;
            bitangents = a_Bitangents;
        }

        MeshBufferInfo BufferInfo()
        {
            MeshBufferInfo bufferInfo;
            bufferInfo.numIndices = (unsigned int)indices.size();
            bufferInfo.numPositions = (unsigned int)positions.size();
            bufferInfo.numColors = (unsigned int)colors.size();
            bufferInfo.numUVs = (unsigned int)UVs.size();
            bufferInfo.numNormals = (unsigned int)normals.size();
            bufferInfo.numTangents = (unsigned int)tangents.size();
            bufferInfo.numBitangents = (unsigned int)bitangents.size();

            return bufferInfo;
        }
    };

}
#endif //!_Mesh_Data_H_
