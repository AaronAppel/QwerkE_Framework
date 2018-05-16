#include "OBJLoader.h"
#include "../../../QwerkE_Framework/Systems/Graphics/Graphics_Header.h"
#include "FileUtilities.h"
#include "../PrintFunctions.h"
#include "../../../QwerkE_Framework/Systems/Graphics/Mesh/Model.h"
#include "../../../QwerkE_Framework/Systems/Graphics/Mesh/Mesh.h"
#include "../../../QwerkE_Framework/Systems/Graphics/Mesh/MeshUtilities.h"

#include <cstring>

// TODO: Consider abstracting functionality. Maybe
// abstract the mesh class and just pass vector2/3[]s back

// TwinMatrix reference: https://pastebin.com/b5EuEyxj
Model* ImportOBJModel(const char* fileDirectory, vec3 objScale, vec2 UVScale, bool invertFaces)
{
	// TODO: Search method for returning one object/mesh from a file instead of all or multiple

	//////////////////////////////////Read File/////////////////////////////////////////
	// find file
	long length = 0;
	char* buffer = LoadCompleteFile(fileDirectory, &length);
	if (buffer == 0 || length == 0)
	{
		delete[] buffer;
		OutputPrint("\nMesh: ImportOBJMesh() error reading %s\n", fileDirectory);
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

	//////////////////////////////////Parse for data/////////////////////////////////////////
	std::vector<vec3> verts; // VertexData data
	std::vector<vec2> uvs; // texture data
	std::vector<vec3> normals; // normal data

	std::vector<unsigned int> VertexIndices;
	std::vector<unsigned int> UVIndices;
	std::vector<unsigned int> NormalIndices;

	std::vector<Mesh*> m_Meshes;
	std::string objectName = "Long Name For Buffer Purpose";
	Mesh* pMesh = nullptr;
	std::vector<unsigned int> rangeList;

	for (unsigned int i = 0; i < stringList.size(); i++)
	{
		std::string loopString = stringList.at(i);
		if (loopString.find("# object") != loopString.npos) // check type of info
		{
			sscanf_s((char*)loopString.c_str(), "%*s %*s %s", (char*)objectName.c_str(), objectName.length());
			pMesh = new Mesh();
			m_Meshes.push_back(pMesh);
			pMesh->SetName(objectName);
			unsigned int temp = 0;
			rangeList.push_back(temp);
		}
		if (loopString.at(0) == 'v') // check type of info
		{
			if (loopString.at(1) == ' ')
			{
				vec3 vertexPosition = vec3(0, 0, 0);
				sscanf_s(loopString.data(), "%*s %f %f %f", &vertexPosition.x, &vertexPosition.y, &vertexPosition.z);
				verts.push_back(vec3(vertexPosition.x, vertexPosition.y, vertexPosition.z));
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
				OutputPrint("\nMeshHelpers: ImportOBJMesh() -> Error reading %s.\n", fileDirectory);
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
			rangeList.at(m_Meshes.size() - 1) += 3;
		}
	}

	////////////////////////////////////Setup VertexData///////////////////////////////////////////
	/* Create VertexData list */
	std::vector<VertexData> t_VertexData;
	for (unsigned int i = 0; i < verts.size(); i++)
	{
		// First vertex
		VertexData t_Vertex;
		t_Vertex.position = verts[i];
		t_Vertex.color = vec4(1.0f, 1.0f, 1.0f, 1.0f);
		t_Vertex.UV = vec2(-1.0f, -1.0f); // invalidate
		t_Vertex.normal = vec3(-1.0f, -1.0f, -1.0f); // invalidate
													 // push_back
		t_VertexData.push_back(t_Vertex);
	}
	/* Setup UVs and Normals */
	for (unsigned int i = 0; i < VertexIndices.size(); i++)
	{
		// Go through each face array list (1/1/1 2/2/2 3/3/3)
		// and set the values for each vertex.uv, .normal
		t_VertexData.at(VertexIndices[i]).UV = uvs[UVIndices[i]];
		t_VertexData.at(VertexIndices[i]).normal = normals.at(NormalIndices[i]);
		// TODO: Increase efficiency. Repeats vertices to ensure values get assigned.
	}

	if (invertFaces)
	{
		InvertFaces(VertexIndices.data(), VertexIndices.size()); // invert
	}
	if (objScale != vec3(1.0f, 1.0f, 1.0f))
	{
		ScaleVertices(t_VertexData.data(), t_VertexData.size(), objScale);
	}

	////////////////////////////////////Setup mesh specific data///////////////////////////////////////////
	// Setup list of object specific vertices
	if (m_Meshes.size() == 0) // no mesh/object found
	{
		return nullptr;
	}
	Model* m_Model = new Model();
	m_Model->SetName(m_Meshes.at(0)->GetName()); // TODO: Get name from fileDirectory

	std::vector<std::vector<VertexData>> t_ObjectVertsList; // 2D list

	if (m_Meshes.size() == 1)
	{
		// use pre-existing vert list
		m_Meshes.at(0)->BufferMeshData(t_VertexData.size(), t_VertexData.data(), VertexIndices.size(), VertexIndices.data());
		m_Model->Init(m_Meshes);
		return m_Model;
	}
	else // TODO: Finish loading multiple mesh models
	{
		int loopcounter = 0;
		for (unsigned int objectIndex = 0; objectIndex < m_Meshes.size(); objectIndex++)
		{
			// per mesh
			std::vector<VertexData> t_TempVertList;
			t_ObjectVertsList.push_back(t_TempVertList);
			for (unsigned int j = loopcounter; j < rangeList.at(objectIndex) + loopcounter; j++) // vertList
			{
				// Use face data
				// pushback all vertices for each object
				VertexData t_Temp;
				t_Temp = t_VertexData.at(VertexIndices.at(j)); // Use stored range for object data
															   // TODO: Check for unique results
				t_ObjectVertsList.at(objectIndex).push_back(t_Temp);
			}
			loopcounter += rangeList.at(objectIndex);
		}
	}
	// Setup list of indices for each object
	std::vector<std::vector<unsigned int>> t_IndexList;
	for (unsigned int i = 0; i < m_Meshes.size(); i++) // indexList
	{
		int size = 0;
		for (int j = 0; j < size; j++)
		{

		}
	}

	////////////////////////////////////Buffer meshes///////////////////////////////////////////
	// buffer each mesh
	for (unsigned int i = 0; i < m_Meshes.size(); i++)
	{
		m_Meshes.at(i)->BufferMeshData(t_VertexData.size(), t_VertexData.data(), VertexIndices.size(), VertexIndices.data());
	}
	m_Model->Init(m_Meshes);

	return m_Model;
}