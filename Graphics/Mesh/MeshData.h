#ifndef _Mesh_Data_H_
#define _Mesh_Data_H_

#include "../../QwerkE_Common/Math_Includes.h"

struct MeshBufferInfo
{
	int numPositions = 0;
	int numIndices = 0;
	int numColors = 0;
	int numUVs = 0;
	int numNormals = 0;
	int numTangents = 0;
	int numBitangents = 0;

	int SingleVertexByteSize() // Size in bytes of each value * 1 summed
	{
		return sizeof(numPositions) +
			sizeof(numColors) +
			sizeof(numUVs) +
			sizeof(numNormals) +
			sizeof(numTangents) +
			sizeof(numBitangents);
	}

	int BufferSize() { return BitangentsOff() + sizeof(vec3) * numBitangents; }

	int PositionOff() { return 0; } // Point to start of data (index 0)
	int ColorOff() { return sizeof(vec3) * numPositions; } // Number of bytes positions take
	int UVOff() { return ColorOff() + (sizeof(vec4) * numColors); } // Number of bytes positions take + Offset of colors and positions
	int NormalOff() { return UVOff() + (sizeof(vec2) * numUVs); }
	int TangentsOff() { return NormalOff() + (sizeof(vec3) * numNormals); }
	int BitangentsOff() { return TangentsOff() + (sizeof(vec3) * numTangents); }
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
		bufferInfo.numIndices = indices.size();
		bufferInfo.numPositions = positions.size();
		bufferInfo.numColors = colors.size();
		bufferInfo.numUVs = UVs.size();
		bufferInfo.numNormals = normals.size();
		bufferInfo.numTangents = tangents.size();
		bufferInfo.numBitangents = bitangents.size();

		return bufferInfo;
	}
};

#endif //!_Mesh_Data_H_
