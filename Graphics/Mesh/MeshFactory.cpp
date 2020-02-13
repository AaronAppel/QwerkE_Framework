#include "MeshFactory.h"
#include "../../QwerkE_Common/Utilities/FileIO/FileUtilities.h"
#include "../../Graphics/Graphics_Header.h"
#include "../../Graphics/Mesh/MeshData.h"
#include "../../QwerkE_Common/Math_Includes.h"

#include <vector>

namespace QwerkE {

	/* OBJ loading */
	Mesh* MeshFactory::ImportOBJMesh(const char* fileDirectory, vec3 objScale, vec2 UVScale, bool invertFaces)
	{
		// find file
		long length = 0;
		char* buffer = LoadCompleteFile(fileDirectory, &length);
		if (buffer == 0 || length == 0)
		{
			delete buffer;
			return 0;
		}

		// read and store file text
		char* next_token = 0;
		char* line = strtok_s(buffer, "\n", &next_token);

		std::vector<std::string> stringList;

		while (line)
		{
			//OutputMessage("%s\n", line);
			stringList.push_back(line);
			line = strtok_s(0, "\n", &next_token);
		}
		// parse file for data
		// std::vector<VertexData> verts; // VertexData data
		// std::vector<unsigned int> indices; // IBO data

		/*unsigned int textureCounter = 0;
		unsigned int normalCounter = 0;*/

		MeshData data;

		for (unsigned int i = 0; i < stringList.size(); i++) // stringList.size() = number of lines in file
		{
			std::string loopString = stringList.at(i);

			if (loopString.at(0) == 'v') // check type of info
			{
				if (loopString.at(1) == ' ')
				{
					// read vertex data, create VBO
					vec3 vertexPosition = vec3(0, 0, 0);

					sscanf_s(loopString.data(), "%*s %f %f %f", &vertexPosition.x, &vertexPosition.y, &vertexPosition.z);// tempString.data(), tempString.length(), &tempInteger);

					data.positions.push_back(vec3(vertexPosition.x, vertexPosition.y, vertexPosition.z));
					data.colors.push_back(vec4(255, 255, 255, 255));

					// verts.push_back(VertexData(vec3(vertexPosition.x, vertexPosition.y, vertexPosition.z), vec4(255, 255, 255, 255), vec2(0, 1), vec3(0, 0, 0)));
				}
				else if (loopString.at(1) == 't')
				{
					// uv coords
					vec2 vertexUV = vec2(0, 0);
					sscanf_s(loopString.data(), "%*s %f %f", &vertexUV.x, &vertexUV.y);
					//verts.at(textureCounter).uv = vertexUV;
					data.UVs.push_back(vertexUV);
					// textureCounter++;
				}
				else if (loopString.at(1) == 'n')
				{
					// normal
					vec3 vertexNormal = vec3(0, 0, 0);
					sscanf_s(loopString.data(), "%*s %f %f %f", &vertexNormal.x, &vertexNormal.y, &vertexNormal.z);
					//verts.at(normalCounter).normal = vertexNormal;
					data.normals.push_back(vertexNormal);
					// normalCounter++;
				}

			}
			else if (loopString.at(0) == 'f')
			{
				// read faces, create IBO
				int tempVariable[] = { 0,0,0 };
				sscanf_s(loopString.data(), "%*s %i %*s %i %*s %i", &tempVariable[0], &tempVariable[1], &tempVariable[2]);

				data.indices.push_back(tempVariable[0] - 1);
				data.indices.push_back(tempVariable[1] - 1);
				data.indices.push_back(tempVariable[2] - 1);

				//indices.push_back(tempVariable[0] - 1); // OBJ exporter thinks first index is 1
				//indices.push_back(tempVariable[1] - 1);
				//indices.push_back(tempVariable[2] - 1);
			}
		}

		// generate mesh
		Mesh* t_pNewMesh = new Mesh();

		// scale vertices
		if (objScale != vec3(1.0f, 1.0f, 1.0f))
		{
			ScaleVertices(data.positions, objScale);
		}

		// generate UVCOORDS
		CalculateUVCoords(data.UVs); // default scale 1,1

		// scale UVCOORDS
		if (UVScale != vec2(1.0f, 1.0f))
		{
			ScaleUVCOORDS(data.UVs, UVScale);
		}

		// invert faces
		if (invertFaces)
		{
			InvertFaces(data.indices.data(), data.indices.size());
		}

		// initialize mesh
		// t_pNewMesh->BufferMeshData(verts.size(), verts.data(), indices.size(), indices.data()); // GL_STATIC_DRAW
		t_pNewMesh->BufferMeshData(&data); // GL_STATIC_DRAW
		t_pNewMesh->SetPrimitiveType(GL_TRIANGLES);

		// cleanup
		delete[] buffer;

		return t_pNewMesh;

		/*
		char* sentence = "Rudolph is 12 years old";
		char str[20];
		int i;

		sscanf_s(sentence, "%s %*s %d", str, 20, &i);
		OutputMessage("%s\n", str);
		*/
	}

	/* Mesh creation */
	Mesh* MeshFactory::CreateTestModel()
	{
		// DEBUG: Remove from final build
		/* This is for testing purposes only! */
		const char* fileDirectory = "Resources/Models/1M_CubeModel.obj";
		// find file
		long length = 0;
		char* buffer = LoadCompleteFile(fileDirectory, &length);
		if (buffer == 0 || length == 0)
		{
            delete[] buffer;
            LOG_ERROR("Mesh: ImportOBJMesh() error reading %s", fileDirectory);
			return 0;
		}

		// read and store file text
		char* next_token = 0;
		char* line = strtok_s(buffer, "\n", &next_token);

		std::vector<std::string> stringList;

		while (line)
		{
			//OutputMessage("%s\n", line);
			stringList.push_back(line);
			line = strtok_s(0, "\n", &next_token);
		}
		delete[] buffer;

		std::vector<vec3> verts; // VertexData data
		std::vector<vec2> uvs; // texture data
		std::vector<vec3> normals; // normal data
		int faces = 0;

		std::vector<unsigned int> VertexIndices;
		std::vector<unsigned int> UVIndices;
		std::vector<unsigned int> NormalIndices;

		MeshData data;

		/* Read data */
		for (unsigned int i = 0; i < stringList.size(); i++)
		{
			std::string loopString = stringList.at(i);

			if (loopString.at(0) == 'v') // check type of info
			{
				if (loopString.at(1) == ' ')
				{
					vec3 vertexPosition = vec3(0, 0, 0);
					sscanf_s(loopString.data(), "%*s %f %f %f", &vertexPosition.x, &vertexPosition.y, &vertexPosition.z);
					data.positions.push_back(vec3(vertexPosition.x, vertexPosition.y, vertexPosition.z));
				}
				else if (loopString.at(1) == 't') // uv coords
				{
					vec2 vertexUV = vec2(0, 0);
					sscanf_s(loopString.data(), "%*s %f %f", &vertexUV.x, &vertexUV.y);
					uvs.push_back(vertexUV);
				}
				else if (loopString.at(1) == 'n') // normals
				{
					vec3 vertexNormal = vec3(0, 0, 0);
					sscanf_s(loopString.data(), "%*s %f %f %f", &vertexNormal.x, &vertexNormal.y, &vertexNormal.z);
					normals.push_back(vertexNormal);
				}
			}
			else if (loopString.at(0) == 'f')
			{
				faces++;
				// read faces
				// Example: f 1/4/7 2/5/8 3/6/9    vert/uv/normal   vert/uv/normal   vert/uv/normal
				int tempVertexIndices[] = { -1,-1,-1 };
				int tempUVIndices[] = { -1,-1,-1 };
				int tempNormalIndices[] = { -1,-1,-1 };

				int matches = sscanf_s(loopString.data(), "%*s %d/%d/%d %d/%d/%d %d/%d/%d",
					&tempVertexIndices[0], &tempUVIndices[0], &tempNormalIndices[0], // First vertex
					&tempVertexIndices[1], &tempUVIndices[1], &tempNormalIndices[1],
					&tempVertexIndices[2], &tempUVIndices[2], &tempNormalIndices[2]);

				if (matches != 9)
                {
                    LOG_ERROR("MeshHelpers: ImportOBJMesh() -> Error reading %s", fileDirectory);
				}

				/* Save values */
				VertexIndices.push_back(tempVertexIndices[0] - 1); // OBJ exporter thinks first index is 1 instead of 0
				VertexIndices.push_back(tempVertexIndices[1] - 1);
				VertexIndices.push_back(tempVertexIndices[2] - 1);

				UVIndices.push_back(tempUVIndices[0] - 1);
				UVIndices.push_back(tempUVIndices[1] - 1);
				UVIndices.push_back(tempUVIndices[2] - 1);

				NormalIndices.push_back(tempNormalIndices[0] - 1);
				NormalIndices.push_back(tempNormalIndices[1] - 1);
				NormalIndices.push_back(tempNormalIndices[2] - 1);
			}
		}

		/* Create VertexData list */
		std::vector<MeshData> t_VertexData;
		for (unsigned int i = 0; i < verts.size(); i++)
		{
			// First vertex
			MeshData t_Vertex;
			t_Vertex.positions.push_back(verts[i]);
			t_Vertex.colors.push_back(vec4(1.0f, 1.0f, 1.0f, 1.0f));
			t_Vertex.UVs.push_back(vec2(-1.0f, -1.0f)); // invalidate
			t_Vertex.normals.push_back(vec3(-1.0f, -1.0f, -1.0f)); // invalidate

			// push_back
			t_VertexData.push_back(t_Vertex);
		}

		/* Setup UVs and Normals */
		for (unsigned int i = 0; i < VertexIndices.size(); i++)
		{
			t_VertexData.at(VertexIndices[i]).UVs.push_back(uvs[UVIndices[i]]);
			t_VertexData.at(VertexIndices[i]).normals.push_back(normals.at(NormalIndices[NormalIndices[i]]));
		}

		Mesh* pMesh = new Mesh();
		InvertFaces(VertexIndices.data(), VertexIndices.size()); // invert
		// pMesh->CalculateUVCoords(t_VertexData);
		// pMesh->BufferMeshData(t_VertexData.size(), t_VertexData.data(), VertexIndices.size(), VertexIndices.data()); // GL_STATIC_DRAW
		pMesh->BufferMeshData(&data); // GL_STATIC_DRAW
		pMesh->SetPrimitiveType(GL_TRIANGLES);

		return pMesh;
	};

	Mesh* MeshFactory::CreateTestPlane()
	{
		MeshData data = MeshData();

		// positions
		vec3 pos1(-1.0f, 1.0f, 0.0f);
		vec3 pos2(-1.0f, -1.0f, 0.0f);
		vec3 pos3(1.0f, -1.0f, 0.0f);
		vec3 pos4(1.0f, 1.0f, 0.0f);

		// texture coordinates
		vec2 uv1(0.0f, 1.0f);
		vec2 uv2(0.0f, 0.0f);
		vec2 uv3(1.0f, 0.0f);
		vec2 uv4(1.0f, 1.0f);

		// normal vector
		vec3 nm(0.0f, 0.0f, 1.0f);

		// calculate tangent/bitangent vectors of both triangles
		vec3 tangent1, bitangent1;
		vec3 tangent2, bitangent2;

		// triangle 1
		// ----------
		vec3 edge1 = pos2 - pos1;
		vec3 edge2 = pos3 - pos1;
		vec2 deltaUV1 = uv2 - uv1;
		vec2 deltaUV2 = uv3 - uv1;

		GLfloat f = 1.0f / (deltaUV1.x * deltaUV2.y - deltaUV2.x * deltaUV1.y);

		tangent1.x = f * (deltaUV2.y * edge1.x - deltaUV1.y * edge2.x);
		tangent1.y = f * (deltaUV2.y * edge1.y - deltaUV1.y * edge2.y);
		tangent1.z = f * (deltaUV2.y * edge1.z - deltaUV1.y * edge2.z);
		glm::vec3 tan1 = glm::normalize(glm::vec3(tangent1.x, tangent1.y, tangent1.z));
		tangent1 = vec3(tan1.x, tan1.y, tan1.z);

		bitangent1.x = f * (-deltaUV2.x * edge1.x + deltaUV1.x * edge2.x);
		bitangent1.y = f * (-deltaUV2.x * edge1.y + deltaUV1.x * edge2.y);
		bitangent1.z = f * (-deltaUV2.x * edge1.z + deltaUV1.x * edge2.z);
		glm::vec3 bitan1 = glm::normalize(glm::vec3(bitangent1.x, bitangent1.y, bitangent1.z));
		bitangent1 = vec3(bitan1.x, bitan1.y, bitan1.z);

		// triangle 2
		// ----------
		edge1 = pos3 - pos1;
		edge2 = pos4 - pos1;
		deltaUV1 = uv3 - uv1;
		deltaUV2 = uv4 - uv1;

		f = 1.0f / (deltaUV1.x * deltaUV2.y - deltaUV2.x * deltaUV1.y);

		tangent2.x = f * (deltaUV2.y * edge1.x - deltaUV1.y * edge2.x);
		tangent2.y = f * (deltaUV2.y * edge1.y - deltaUV1.y * edge2.y);
		tangent2.z = f * (deltaUV2.y * edge1.z - deltaUV1.y * edge2.z);
		glm::vec3 tan2 = glm::normalize(glm::vec3(tangent2.x, tangent2.y, tangent2.z));
		tangent2 = vec3(tan2.x, tan2.y, tan2.z);

		bitangent2.x = f * (-deltaUV2.x * edge1.x + deltaUV1.x * edge2.x);
		bitangent2.y = f * (-deltaUV2.x * edge1.y + deltaUV1.x * edge2.y);
		bitangent2.z = f * (-deltaUV2.x * edge1.z + deltaUV1.x * edge2.z);
		glm::vec3 bitan2 = glm::normalize(glm::vec3(bitangent2.x, bitangent2.y, bitangent2.z));
		bitangent2 = vec3(bitan2.x, bitan2.y, bitan2.z);

		// Positions
		data.positions.push_back(pos1);
		data.positions.push_back(pos2);
		data.positions.push_back(pos3);
		data.positions.push_back(pos4);

		// UVs
		data.UVs.push_back(uv1);
		data.UVs.push_back(uv2);
		data.UVs.push_back(uv3);
		data.UVs.push_back(uv4);

		// Normals
		data.positions.push_back(nm);
		data.positions.push_back(nm);
		data.positions.push_back(nm);
		data.positions.push_back(nm);

		// Tangents
		data.positions.push_back(tangent1);
		data.positions.push_back(tangent1);
		data.positions.push_back(tangent1);
		data.positions.push_back(tangent2);

		// Bitangents
		data.positions.push_back(bitangent1);
		data.positions.push_back(bitangent1);
		data.positions.push_back(bitangent1);
		data.positions.push_back(bitangent2);

		// Indices
		data.indices = std::vector<unsigned int>{ 0,1,2, 0,2,3 };

		Mesh* mesh = new Mesh();
		mesh->BufferMeshData(&data);

		return mesh;
	}

	Mesh* MeshFactory::CreateQuad(vec2 size)
	{
		std::vector<vec3> pos = std::vector<vec3>{ vec3(-size.x / 2, -size.y / 2, 0.0f), vec3(-size.x / 2, size.y / 2, 0.0f), vec3(size.x / 2, size.y / 2, 0.0f), vec3(size.x / 2, -size.y / 2, 0.0f) };
		std::vector<vec4> col = std::vector<vec4>();
		std::vector<vec2> uv = std::vector<vec2>{ vec2(0,0), vec2(0, 1), vec2(1, 1), vec2(1, 0) };
		std::vector<vec3> nor = std::vector<vec3>{ vec3(1, 0, 0), vec3(1, 1, 0), vec3(0, 1, 0), vec3(0, 0, 0) };
		std::vector<vec3> tang = std::vector<vec3>();
		std::vector<vec3> bit = std::vector<vec3>();

		MeshData data = MeshData(pos, col, uv, nor, tang, bit);
		data.indices = std::vector<unsigned int>{ 0,1,2, 2,3,0 };

		Mesh* pMesh = new Mesh();
		pMesh->BufferMeshData(&data);
		return pMesh;
	};

	Mesh* MeshFactory::CreateCircle(float radius, unsigned int points, vec2 UVScale)
	{
		// TODO: Ability to draw XZ OR XY axis
		MeshData data;
		data.positions.push_back(vec3(0, 0, 0)); // center

		float t_AngleBetweenPoints = 360.0f / points; // degrees

		vec3 Position = vec3(0, 0, 0);
		float t_IncrementAngle = 360.0f;

		for (unsigned int j = 0; j < points + 1; j++) // plot circle
		{
			Position.x = cosf(t_IncrementAngle * DEG_TO_RAD) * radius;
			Position.y = sinf(t_IncrementAngle * DEG_TO_RAD) * radius;// 0;
			Position.z = 0;// sinf(t_IncrementAngle * DEG_TO_RAD) * radius;

			// verts.push_back(VertexData(vec3(Position.x, Position.y, Position.z), vec4(255, 255, 255, 255), vec2(0, 1), vec3(0, 0, 0)));
			data.positions.push_back(vec3(Position.x, Position.y, Position.z));

			t_IncrementAngle -= t_AngleBetweenPoints; // clockwise
		}
		// generate indices
		std::vector<unsigned int> indices;
		for (unsigned int i = 0; i < points; i++)
		{
			indices.push_back(0); // center first
			indices.push_back(i + 1);
			indices.push_back(i + 2);
		}


		// generate UVCOORDS
		// TODO: Fix CalculateXZUVCoords(verts.data(), verts.size()); // default scale 1,1
		// scale UVCOORDS
		if (UVScale != vec2(1.0f, 1.0f))
		{
			// TODO: Fix ScaleUVCOORDS(verts.data(), verts.size(), UVScale);
		}

		if (Wind_CCW) { InvertFaces(indices.data(), indices.size()); } // Reverse winding order

		// Create mesh
		Mesh* t_pNewMesh = new Mesh();
		t_pNewMesh->BufferMeshData(&data);

		return t_pNewMesh;
	}

	Mesh* MeshFactory::CreateCube(vec3 size, vec2 UVScale, bool invertFaces)
	{
		// TODO: Fix UV values
		// TODO: Change winding order of faces and improve invert faces logic
		// TODO: Only use 8 vertices for cube

		// image
		int imageWidth = 500; // pixels
		int imageHeight = 500; // 0.1666666666666667
		int numOfXFrames = 1;
		int numOfYFrames = 1;

		float frameWidth = (float)(imageWidth / numOfXFrames);
		float frameHeight = (float)(imageHeight / numOfYFrames);

		float UVOffsetX = frameWidth / imageWidth;
		float UVOffsetY = imageHeight / frameHeight;

		// mesh
		MeshData data;
		data.positions.resize(24); // TODO: Update to only 8
		data.UVs.resize(24); // TODO: Update to only 8
		data.normals.resize(24); // TODO: Update to only 8

		// cube with 6 sides, 2 triangles per side
		// face 1 - front
		data.positions[0] = vec3(-size.x / 2, size.y / 2, -size.z / 2); // top-left
		data.UVs[0] = vec2(0, 1);
		data.normals[0] = vec3(0, 0, -1);

		data.positions[1] = vec3(-size.x / 2, -size.y / 2, -size.z / 2); // bottom-left
		data.UVs[1] = vec2(0, 0);
		data.normals[1] = vec3(0, 0, -1);

		data.positions[2] = vec3(size.x / 2, -size.y / 2, -size.z / 2); // bottom-right
		data.UVs[2] = vec2(UVOffsetX, 0.0f);
		data.normals[2] = vec3(0, 0, -1);

		data.positions[3] = vec3(size.x / 2, size.y / 2, -size.z / 2); // top-right
		data.UVs[3] = vec2(UVOffsetX, 1.0f);
		data.normals[3] = vec3(0, 0, -1);

		// face 2 - left
		data.positions[4] = vec3(-size.x / 2, size.y / 2, -size.z / 2);
		data.UVs[4] = vec2(UVOffsetX, 1.0f);
		data.normals[4] = vec3(-1, 0, 0);

		data.positions[5] = vec3(-size.x / 2, -size.y / 2, -size.z / 2);
		data.UVs[5] = vec2(UVOffsetX, 0.0f);
		data.normals[5] = vec3(-1, 0, 0);

		data.positions[6] = vec3(-size.x / 2, -size.y / 2, size.z / 2);
		data.UVs[6] = vec2(UVOffsetX * 2, 0.0f);
		data.normals[6] = vec3(-1, 0, 0);

		data.positions[7] = vec3(-size.x / 2, size.y / 2, size.z / 2);
		data.UVs[7] = vec2(UVOffsetX * 2, 1.0f);
		data.normals[7] = vec3(-1, 0, 0);

		// face 3 - back
		data.positions[8] = vec3(size.x / 2, size.y / 2, size.z / 2);
		data.UVs[8] = vec2(UVOffsetX * 2, 1.0f);
		data.normals[8] = vec3(0, 0, 1);

		data.positions[9] = vec3(size.x / 2, -size.y / 2, size.z / 2);
		data.UVs[9] = vec2(UVOffsetX * 2, 0.0f);
		data.normals[9] = vec3(0, 0, 1);

		data.positions[10] = vec3(-size.x / 2, -size.y / 2, size.z / 2);
		data.UVs[10] = vec2(UVOffsetX * 3, 0.0f);
		data.normals[10] = vec3(0, 0, 1);

		data.positions[11] = vec3(-size.x / 2, size.y / 2, size.z / 2);
		data.UVs[11] = vec2(UVOffsetX * 3, 1.0f);
		data.normals[11] = vec3(0, 0, 1);

		// face 4 - right
		data.positions[12] = vec3(size.x / 2, size.y / 2, -size.z / 2);
		data.UVs[12] = vec2(UVOffsetX * 3, 1.0f);
		data.normals[12] = vec3(0, 0, 1);

		data.positions[13] = vec3(size.x / 2, -size.y / 2, -size.z / 2);
		data.UVs[13] = vec2(UVOffsetX * 3, 0.0f);
		data.normals[13] = vec3(0, 0, 1);

		data.positions[14] = vec3(size.x / 2, -size.y / 2, size.z / 2);
		data.UVs[14] = vec2(UVOffsetX * 4, 0.0f);
		data.normals[14] = vec3(0, 0, 1);

		data.positions[15] = vec3(size.x / 2, size.y / 2, size.z / 2);
		data.UVs[15] = vec2(UVOffsetX * 4, 1.0f);
		data.normals[15] = vec3(0, 0, 1);

		// face 5 - top - z axis becomes vertical + reference
		data.positions[16] = vec3(-size.x / 2, size.y / 2, size.z / 2);
		data.UVs[16] = vec2(UVOffsetX * 4, 1.0f);
		data.normals[16] = vec3(0, 0, 1);

		data.positions[17] = vec3(-size.x / 2, size.y / 2, -size.z / 2);
		data.UVs[17] = vec2(UVOffsetX * 4, 0.0f);
		data.normals[17] = vec3(0, 0, 1);

		data.positions[18] = vec3(size.x / 2, size.y / 2, -size.z / 2);
		data.UVs[18] = vec2(UVOffsetX * 5, 0.0f);
		data.normals[18] = vec3(0, 0, 1);

		data.positions[19] = vec3(size.x / 2, size.y / 2, size.z / 2);
		data.UVs[19] = vec2(UVOffsetX * 5, 1.0f);
		data.normals[19] = vec3(0, 0, 1);

		// face 6 - bottom
		data.positions[20] = vec3(-size.x / 2, -size.y / 2, size.z / 2);
		data.UVs[20] = vec2(UVOffsetX * 5, 0.0f);
		data.normals[20] = vec3(0, 0, 1);

		data.positions[21] = vec3(-size.x / 2, -size.y / 2, -size.z / 2);
		data.UVs[21] = vec2(UVOffsetX * 2, 0.0f);
		data.normals[21] = vec3(0, 0, 1);

		data.positions[22] = vec3(size.x / 2, -size.y / 2, -size.z / 2);
		data.UVs[22] = vec2(UVOffsetX * 6, 0.0f);
		data.normals[22] = vec3(0, 0, 1);

		data.positions[23] = vec3(size.x / 2, -size.y / 2, size.z / 2);
		data.UVs[23] = vec2(UVOffsetX * 6, 1.0f);
		data.normals[23] = vec3(0, 0, 1);

		data.indices = std::vector<unsigned int>{
			0,3,2, 2,1,0, // front - brown
			6,7,4, 4,5,6, // left - pink
			10,9,8, 8,11,10, // back - blue
			12,15,14, 14,13,12, // right - yellow
			16,19,18, 18,17,16, // top - red
			22,23,20, 20,21,22 // bottom - green
		};

		Mesh* t_pNewMesh = new Mesh();

		// scale UVCOORDS
		if (UVScale != vec2(1.0f, 1.0f))
		{
			ScaleUVCOORDS(data.UVs, UVScale);
		}

		if (invertFaces) // invert faces
		{
			InvertFaces(data.indices.data(), data.indices.size());
		}

		if (Wind_CCW) { InvertFaces(data.indices.data(), data.indices.size()); }

		t_pNewMesh->BufferMeshData(&data);

		return t_pNewMesh;
	}

	// worldSize, number of vertices, UVPos,
	//Mesh* MeshFactory::CreatePlane(vec2 size, vec2 NumOfVerts, vec2 UVScale) // pivot, size, UVStart, UVOffset
	//{
	//	// TODO: Ability to create XY plane
	//	//// variables
	//	int numVertsX = (int)NumOfVerts.x;
	//	int numVertsY = (int)NumOfVerts.y;
	//	int numVerts = numVertsX * numVertsY;
	//
	//	// create array
	//	// VertexData *verts = new VertexData[numVerts]; //  (vertexCount.x-1)*(vertexCount-1)*2 triangles per square*3 indices per triangle;
	//	MeshData data;
	//
	//	float width = size.x;
	//	float height = size.y;
	//
	//	// spacing
	//	float xSpacing = width / (numVertsX - 1);
	//	float ySpacing = height / (numVertsY - 1);
	//
	//	// for-loop variables
	//	// increment
	//	float xIncrement = -width * 0.5f;
	//	float zIncrement = -height * 0.5f;
	//
	//	int indexCounter = 0;
	//
	//	for (int i = 0; i < numVertsX; i++)
	//	{
	//		for (int j = 0; j < numVertsY; j++)
	//		{
	//			data.positions.push_back(vec3(xIncrement, 0.0f, zIncrement));
	//			// verts[indexCounter] = VertexData(vec3(xIncrement, 0.0f, zIncrement), vec4(255, 255, 255, 255), vec2(0, 0), vec3(0, 0, 0));
	//			indexCounter++;
	//			xIncrement += xSpacing;
	//		}
	//		xIncrement = -width * 0.5f;
	//		zIncrement += ySpacing;
	//	}
	//
	//	const int numOfIndices = 6 * (numVertsX - 1) * (numVertsY - 1); // 6 points per rectangle * number of rectangles
	//	unsigned int* indices = new unsigned int[numOfIndices]; // 6 * numOfRectangles
	//	data.indices.reserve(numOfIndices);
	//	indexCounter = 0;
	//	int vertex = 0;
	//
	//	// start at bottom left corner, create left most box by taking y point from above, then current y points (clockwise)
	//	// then move right, at end of x row, increment y and continue
	//	for (int i = 0; i < numVertsY - 1; i++) // numVertsY - 1 = number of spaces between points on that axis, which tell how many rectangles
	//	{
	//		// y
	//		for (int j = 0; j < numVertsX - 1; j++)
	//		{
	//			//x
	//			// top right triangle
	//			data.indices[indexCounter] = vertex + numVertsX;
	//			data.indices[indexCounter + 1] = vertex + numVertsX + 1;
	//			data.indices[indexCounter + 2] = vertex + 1;
	//
	//			// bottom left triangle
	//			data.indices[indexCounter + 3] = vertex + 1;
	//			data.indices[indexCounter + 4] = vertex;
	//			data.indices[indexCounter + 5] = vertex + numVertsX;
	//			indexCounter += 6; // next triangle
	//			vertex++; // next point
	//		}
	//		vertex++;
	//	}
	//
	//	Mesh* pMesh = new Mesh();
	//
	//	// generate UVCOORDS
	//	// CalculateXZUVCoords(verts, numVerts);
	//
	//	// scale UVCOORDS
	//	// ScaleUVCOORDS(verts, numVerts, UVScale);
	//
	//	// pMesh->BufferMeshData(numVerts, verts, numOfIndices, indices); // GL_STATIC_DRAW
	//	pMesh->BufferMeshData(&data);
	//	pMesh->SetPrimitiveType(GL_TRIANGLES);
	//
	//	// delete[] verts;
	//	delete[] indices;
	//
	//	return pMesh;
	//}

	/* Mesh data assignment*/
	void MeshFactory::GenerateBox(Mesh* mesh, vec2 size, bool invertFaces)
	{
		MeshData data;
		data.positions.push_back(vec3(0.5f * size.x, 0.5f * size.y, 0.0f));
		data.UVs.push_back(vec2(1, 1));

		data.positions.push_back(vec3(0.5f * size.x, -0.5f * size.y, 0.0f));
		data.UVs.push_back(vec2(1, 0));

		data.positions.push_back(vec3(-0.5f * size.x, -0.5f * size.y, 0.0f));
		data.UVs.push_back(vec2(0, 0));

		data.positions.push_back(vec3(-0.5f * size.x, 0.5f * size.y, 0.0f));
		data.UVs.push_back(vec2(0, 1));

		data.indices = std::vector<unsigned int>{
			0, 1, 3, // First Triangle
			1, 2, 3  // Second Triangle
		};
		if (Wind_CCW) { InvertFaces(data.indices.data(), data.indices.size()); } // Reverse winding order
		mesh->BufferMeshData(&data);
	}

	void MeshFactory::GenerateCube(Mesh* mesh, vec3 size, bool invertFaces)
	{
		// std::vector<VertexData> tempList;
		MeshData data;
		// front
		data.positions.push_back(vec3(-0.5f * size.x, -0.5f * size.y, 0.5f * size.z)); // 0
		data.UVs.push_back(vec2(0, 0));

		data.positions.push_back(vec3(-0.5f * size.x, 0.5f * size.y, 0.5f * size.z));
		data.UVs.push_back(vec2(0, 1));

		data.positions.push_back(vec3(0.5f * size.x, 0.5f * size.y, 0.5f * size.z));
		data.UVs.push_back(vec2(1, 1));

		data.positions.push_back(vec3(0.5f * size.x, -0.5f * size.y, 0.5f * size.z));
		data.UVs.push_back(vec2(1, 0));

		// back
		data.positions.push_back(vec3(-0.5f * size.x, -0.5f * size.y, -0.5f * size.z)); // 0
		data.UVs.push_back(vec2(0, 0));

		data.positions.push_back(vec3(-0.5f * size.x, 0.5f * size.y, -0.5f * size.z));
		data.UVs.push_back(vec2(0, 1));

		data.positions.push_back(vec3(0.5f * size.x, 0.5f * size.y, -0.5f * size.z));
		data.UVs.push_back(vec2(1, 1));

		data.positions.push_back(vec3(0.5f * size.x, -0.5f * size.y, -0.5f * size.z));
		data.UVs.push_back(vec2(1, 0));

		data.indices = std::vector<unsigned int>{
			// front
			0,1,2,
			2,3,0,
			// back
			6,5,4,
			4,7,6,
			// right
			3,2,6,
			6,7,3,
			// left
			4,5,1,
			1,0,4,
			// bottom
			2,1,5,
			5,6,2,
			// top
			4,0,3,
			3,7,4
		};
		if (Wind_CCW) { InvertFaces(data.indices.data(), data.indices.size()); } // Reverse winding order
		mesh->BufferMeshData(&data);
	}

	Mesh* MeshFactory::TutorialCube(vec3 size, vec2 UVScale, bool invertFaces)
	{
		// std::vector<VertexData> t_Verts;
		MeshData data;

		//// Create vertices
		// Front
		data.positions.push_back(vec3(0.5f, 0.5f, -0.5f));
		data.UVs.push_back(vec2(1.0f, 1.0f));
		data.normals.push_back(vec3(0.0f, 0.0f, -1.0f));

		data.positions.push_back(vec3(0.5f, -0.5f, -0.5f));
		data.UVs.push_back(vec2(1.0f, 0.0f));
		data.normals.push_back(vec3(0.0f, 0.0f, -1.0f));

		data.positions.push_back(vec3(-0.5f, -0.5f, -0.5f));
		data.UVs.push_back(vec2(0.0f, 0.0f));
		data.normals.push_back(vec3(0.0f, 0.0f, -1.0f));

		data.positions.push_back(vec3(-0.5f, -0.5f, -0.5f));
		data.UVs.push_back(vec2(0.0f, 0.0f));
		data.normals.push_back(vec3(0.0f, 0.0f, -1.0f));

		data.positions.push_back(vec3(-0.5f, 0.5f, -0.5f));
		data.UVs.push_back(vec2(0.0f, 1.0f));
		data.normals.push_back(vec3(0.0f, 0.0f, -1.0f));

		data.positions.push_back(vec3(0.5f, 0.5f, -0.5f));
		data.UVs.push_back(vec2(1.0f, 1.0f));
		data.normals.push_back(vec3(0.0f, 0.0f, -1.0f));

		// Back
		data.positions.push_back(vec3(-0.5f, -0.5f, 0.5f));
		data.UVs.push_back(vec2(0.0f, 0.0f));
		data.normals.push_back(vec3(0.0f, 0.0f, 1.0f));

		data.positions.push_back(vec3(0.5f, -0.5f, 0.5f));
		data.UVs.push_back(vec2(1.0f, 0.0f));
		data.normals.push_back(vec3(0.0f, 0.0f, 1.0f));

		data.positions.push_back(vec3(0.5f, 0.5f, 0.5f));
		data.UVs.push_back(vec2(1.0f, 1.0f));
		data.normals.push_back(vec3(0.0f, 0.0f, 1.0f));

		data.positions.push_back(vec3(0.5f, 0.5f, 0.5f));
		data.UVs.push_back(vec2(1.0f, 1.0f));
		data.normals.push_back(vec3(0.0f, 0.0f, 1.0f));

		data.positions.push_back(vec3(-0.5f, 0.5f, 0.5f));
		data.UVs.push_back(vec2(0.0f, 1.0f));
		data.normals.push_back(vec3(0.0f, 0.0f, 1.0f));

		data.positions.push_back(vec3(-0.5f, -0.5f, 0.5f));
		data.UVs.push_back(vec2(0.0f, 0.0f));
		data.normals.push_back(vec3(0.0f, 0.0f, 1.0f));

		// Left
		data.positions.push_back(vec3(-0.5f, 0.5f, 0.5f));
		data.UVs.push_back(vec2(1.0f, 0.0f));
		data.normals.push_back(vec3(-1.0f, 0.0f, 0.0f));

		data.positions.push_back(vec3(-0.5f, 0.5f, -0.5f));
		data.UVs.push_back(vec2(1.0f, 1.0f));
		data.normals.push_back(vec3(-1.0f, 0.0f, 0.0f));

		data.positions.push_back(vec3(-0.5f, -0.5f, -0.5f));
		data.UVs.push_back(vec2(0.0f, 1.0f));
		data.normals.push_back(vec3(-1.0f, 0.0f, 0.0f));

		data.positions.push_back(vec3(-0.5f, -0.5f, -0.5f));
		data.UVs.push_back(vec2(0.0f, 1.0f));
		data.normals.push_back(vec3(-1.0f, 0.0f, 0.0f));

		data.positions.push_back(vec3(-0.5f, -0.5f, 0.5f));
		data.UVs.push_back(vec2(0.0f, 0.0f));
		data.normals.push_back(vec3(-1.0f, 0.0f, 0.0f));

		data.positions.push_back(vec3(-0.5f, 0.5f, 0.5f));
		data.UVs.push_back(vec2(1.0f, 0.0f));
		data.normals.push_back(vec3(-1.0f, 0.0f, 0.0f));

		// Right
		data.positions.push_back(vec3(0.5f, -0.5f, -0.5f));
		data.UVs.push_back(vec2(0.0f, 1.0f));
		data.normals.push_back(vec3(1.0f, 0.0f, 0.0f));

		data.positions.push_back(vec3(0.5f, 0.5f, -0.5f));
		data.UVs.push_back(vec2(1.0f, 1.0f));
		data.normals.push_back(vec3(1.0f, 0.0f, 0.0f));

		data.positions.push_back(vec3(0.5f, 0.5f, 0.5f));
		data.UVs.push_back(vec2(1.0f, 0.0f));
		data.normals.push_back(vec3(1.0f, 0.0f, 0.0f));

		data.positions.push_back(vec3(0.5f, 0.5f, 0.5f));
		data.UVs.push_back(vec2(1.0f, 0.0f));
		data.normals.push_back(vec3(1.0f, 0.0f, 0.0f));

		data.positions.push_back(vec3(0.5f, -0.5f, 0.5f));
		data.UVs.push_back(vec2(0.0f, 0.0f));
		data.normals.push_back(vec3(1.0f, 0.0f, 0.0f));

		data.positions.push_back(vec3(0.5f, -0.5f, -0.5f));
		data.UVs.push_back(vec2(0.0f, 1.0f));
		data.normals.push_back(vec3(1.0f, 0.0f, 0.0f));

		// Bottom
		data.positions.push_back(vec3(-0.5f, -0.5f, -0.5f));
		data.UVs.push_back(vec2(0.0f, 1.0f));
		data.normals.push_back(vec3(0.0f, -1.0f, 0.0f));

		data.positions.push_back(vec3(0.5f, -0.5f, -0.5f));
		data.UVs.push_back(vec2(1.0f, 1.0f));
		data.normals.push_back(vec3(0.0f, -1.0f, 0.0f));

		data.positions.push_back(vec3(0.5f, -0.5f, 0.5f));
		data.UVs.push_back(vec2(1.0f, 0.0f));
		data.normals.push_back(vec3(0.0f, -1.0f, 0.0f));

		data.positions.push_back(vec3(0.5f, -0.5f, 0.5f));
		data.UVs.push_back(vec2(1.0f, 0.0f));
		data.normals.push_back(vec3(0.0f, -1.0f, 0.0f));

		data.positions.push_back(vec3(-0.5f, -0.5f, 0.5f));
		data.UVs.push_back(vec2(0.0f, 0.0f));
		data.normals.push_back(vec3(0.0f, -1.0f, 0.0f));

		data.positions.push_back(vec3(-0.5f, -0.5f, -0.5f));
		data.UVs.push_back(vec2(0.0f, 1.0f));
		data.normals.push_back(vec3(0.0f, -1.0f, 0.0f));

		// Top
		data.positions.push_back(vec3(0.5f, 0.5f, 0.5f));
		data.UVs.push_back(vec2(1.0f, 0.0f));
		data.normals.push_back(vec3(0.0f, 1.0f, 0.0f));

		data.positions.push_back(vec3(0.5f, 0.5f, -0.5f));
		data.UVs.push_back(vec2(1.0f, 1.0f));
		data.normals.push_back(vec3(0.0f, 1.0f, 0.0f));

		data.positions.push_back(vec3(-0.5f, 0.5f, -0.5f));
		data.UVs.push_back(vec2(0.0f, 1.0f));
		data.normals.push_back(vec3(0.0f, 1.0f, 0.0f));

		data.positions.push_back(vec3(-0.5f, 0.5f, -0.5f));
		data.UVs.push_back(vec2(0.0f, 1.0f));
		data.normals.push_back(vec3(0.0f, 1.0f, 0.0f));

		data.positions.push_back(vec3(-0.5f, 0.5f, 0.5f));
		data.UVs.push_back(vec2(0.0f, 0.0f));
		data.normals.push_back(vec3(0.0f, 1.0f, 0.0f));

		data.positions.push_back(vec3(0.5f, 0.5f, 0.5f));
		data.UVs.push_back(vec2(1.0f, 0.0f));
		data.normals.push_back(vec3(0.0f, 1.0f, 0.0f));

		// if (Wind_CCW) { InvertFaces(indices, 36); } // Reverse winding order

		Mesh* mesh = new Mesh();
		// mesh->BufferMeshData(36, t_Verts.data(), 0, 0);
		mesh->BufferMeshData(&data);

		return mesh;
	}

}
