#include "../../../QwerkE_Common/Utilities/FileIO/FileUtilities.h"
#include "../../../QwerkE_Common/Utilities/PrintFunctions.h"
#include "../../Graphics/Graphics_Header.h"
#include "../../../QwerkE_Common/Math_Includes.h"

#include <vector>

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
	std::vector<VertexData> verts; // VertexData data
	std::vector<unsigned int> indices; // IBO data

	unsigned int textureCounter = 0;
	unsigned int normalCounter = 0;

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

				verts.push_back(VertexData(vec3(vertexPosition.x, vertexPosition.y, vertexPosition.z), vec4(255, 255, 255, 255), vec2(0, 1), vec3(0, 0, 0)));
			}
			else if (loopString.at(1) == 't')
			{
				// uv coords
				vec2 vertexUV = vec2(0, 0);
				sscanf_s(loopString.data(), "%*s %f %f", &vertexUV.x, &vertexUV.y);
				//verts.at(textureCounter).uv = vertexUV;
				textureCounter++;
			}
			else if (loopString.at(1) == 'n')
			{
				// normal
				vec3 vertexNormal = vec3(0, 0, 0);
				sscanf_s(loopString.data(), "%*s %f %f %f", &vertexNormal.x, &vertexNormal.y, &vertexNormal.z);
				//verts.at(normalCounter).normal = vertexNormal;
				normalCounter++;
			}

		}
		else if (loopString.at(0) == 'f')
		{
			// read faces, create IBO
			int tempVariable[] = { 0,0,0 };
			sscanf_s(loopString.data(), "%*s %i %*s %i %*s %i", &tempVariable[0], &tempVariable[1], &tempVariable[2]);
			indices.push_back(tempVariable[0] - 1); // OBJ exporter thinks first index is 1
			indices.push_back(tempVariable[1] - 1);
			indices.push_back(tempVariable[2] - 1);
		}
	}

	// generate mesh
	Mesh* t_pNewMesh = new Mesh();

	// scale vertices
	if (objScale != vec3(1.0f, 1.0f, 1.0f))
	{
		ScaleVertices(verts.data(), verts.size(), objScale);
	}

	// generate UVCOORDS
	CalculateUVCoords(verts); // default scale 1,1

	// scale UVCOORDS
	if (UVScale != vec2(1.0f, 1.0f))
	{
		ScaleUVCOORDS(verts.data(), verts.size(), UVScale);
	}

	// invert faces
	if (invertFaces)
	{
		InvertFaces(indices.data(), indices.size());
	}

	// initialize mesh
	t_pNewMesh->BufferMeshData(verts.size(), verts.data(), indices.size(), indices.data()); // GL_STATIC_DRAW
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

	std::vector<vec3> verts; // VertexData data
	std::vector<vec2> uvs; // texture data
	std::vector<vec3> normals; // normal data
	int faces = 0;

	std::vector<unsigned int> VertexIndices;
	std::vector<unsigned int> UVIndices;
	std::vector<unsigned int> NormalIndices;

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
		}
	}

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
		t_VertexData.at(VertexIndices[i]).UV = uvs[UVIndices[i]];
		t_VertexData.at(VertexIndices[i]).normal = normals.at(NormalIndices[NormalIndices[i]]);
	}

	Mesh* pMesh = new Mesh();
	InvertFaces(VertexIndices.data(), VertexIndices.size()); // invert
	// pMesh->CalculateUVCoords(t_VertexData);
	pMesh->BufferMeshData(t_VertexData.size(), t_VertexData.data(), VertexIndices.size(), VertexIndices.data()); // GL_STATIC_DRAW
	pMesh->SetPrimitiveType(GL_TRIANGLES);

	return pMesh;
};

Mesh* MeshFactory::CreateBox(vec2 size)
{
	VertexData verts[4];

	verts[0] = VertexData(vec3(-size.x / 2, -size.y / 2, 0), vec4(255, 255, 255, 255), vec2(0, 0), vec3(1, 0, 0));
	verts[1] = VertexData(vec3(-size.x / 2, size.y / 2, 0), vec4(255, 255, 255, 255), vec2(0, 1), vec3(1, 1, 0));
	verts[2] = VertexData(vec3(size.x / 2, size.y / 2, 0), vec4(255, 255, 255, 255), vec2(1, 1), vec3(0, 1, 0));
	verts[3] = VertexData(vec3(size.x / 2, -size.y / 2, 0), vec4(255, 255, 255, 255), vec2(1, 0), vec3(0, 0, 0));

	unsigned int indices[6] = { 0,1,2, 2,3,0 };

	Mesh* pMesh = new Mesh();
	pMesh->BufferMeshData(4, verts, 6, indices); // GL_STATIC_DRAW
	return pMesh;
};
Mesh* MeshFactory::CreateCircle(float radius, unsigned int points, vec2 UVScale)
{
	// TODO: Ability to draw XZ OR XY axis
	std::vector<VertexData> verts;
	verts.push_back(VertexData(vec3(0, 0, 0), vec4(255, 255, 255, 255), vec2(0, 1), vec3(0, 0, 0))); // center

	float t_AngleBetweenPoints = 360.0f / points; // degrees

	vec3 Position = vec3(0, 0, 0);
	float t_IncrementAngle = 360.0f;

	for (unsigned int j = 0; j < points + 1; j++) // plot circle
	{
		Position.x = cosf(t_IncrementAngle * DEG_TO_RAD) * radius;
		Position.y = sinf(t_IncrementAngle * DEG_TO_RAD) * radius;// 0;
		Position.z = 0;// sinf(t_IncrementAngle * DEG_TO_RAD) * radius;

		verts.push_back(VertexData(vec3(Position.x, Position.y, Position.z), vec4(255, 255, 255, 255), vec2(0, 1), vec3(0, 0, 0)));

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

	Mesh* t_pNewMesh = new Mesh();

	// generate UVCOORDS
	CalculateXZUVCoords(verts.data(), verts.size()); // default scale 1,1
																 // scale UVCOORDS
	if (UVScale != vec2(1.0f, 1.0f))
	{
		ScaleUVCOORDS(verts.data(), verts.size(), UVScale);
	}

	if (Wind_CCW) { InvertFaces(indices.data(), indices.size()); } // Reverse winding order

	// initialize mesh
	t_pNewMesh->BufferMeshData(verts.size(), verts.data(), indices.size(), indices.data()); // GL_STATIC_DRAW
	t_pNewMesh->SetPrimitiveType(GL_TRIANGLES);
	return t_pNewMesh;
}
Mesh* MeshFactory::CreateCube(vec3 size, vec2 UVScale, bool invertFaces)
{
	// TODO:: Fix UV values
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
	VertexData verts[24];

	// cube with 6 sides, 2 triangles per side
	// face 1 - front
	verts[0] = VertexData(vec3(-size.x / 2, size.y / 2, -size.z / 2), vec4(255, 255, 255, 255), vec2(0, 1), vec3(0, 0, -1)); //top-left
	verts[1] = VertexData(vec3(-size.x / 2, -size.y / 2, -size.z / 2), vec4(255, 255, 255, 255), vec2(0, 0), vec3(0, 0, -1)); // bottom-left
	verts[2] = VertexData(vec3(size.x / 2, -size.y / 2, -size.z / 2), vec4(255, 255, 255, 255), vec2(UVOffsetX, 0.0f), vec3(0, 0, -1)); // bottom-right
	verts[3] = VertexData(vec3(size.x / 2, size.y / 2, -size.z / 2), vec4(255, 255, 255, 255), vec2(UVOffsetX, 1.0f), vec3(0, 0, -1)); // top-right

	// face 2 - left
	verts[4] = VertexData(vec3(-size.x / 2, size.y / 2, -size.z / 2), vec4(255, 255, 255, 255), vec2(UVOffsetX, 1.0f), vec3(-1, 0, 0));
	verts[5] = VertexData(vec3(-size.x / 2, -size.y / 2, -size.z / 2), vec4(255, 255, 255, 255), vec2(UVOffsetX, 0.0f), vec3(-1, 0, 0));
	verts[6] = VertexData(vec3(-size.x / 2, -size.y / 2, size.z / 2), vec4(255, 255, 255, 255), vec2(UVOffsetX * 2, 0.0f), vec3(-1, 0, 0));
	verts[7] = VertexData(vec3(-size.x / 2, size.y / 2, size.z / 2), vec4(255, 255, 255, 255), vec2(UVOffsetX * 2, 1.0f), vec3(-1, 0, 0));

	// face 3 - back
	verts[8] = VertexData(vec3(size.x / 2, size.y / 2, size.z / 2), vec4(255, 255, 255, 255), vec2(UVOffsetX * 2, 1.0f), vec3(0, 0, 1));
	verts[9] = VertexData(vec3(size.x / 2, -size.y / 2, size.z / 2), vec4(255, 255, 255, 255), vec2(UVOffsetX * 2, 0.0f), vec3(0, 0, 1));
	verts[10] = VertexData(vec3(-size.x / 2, -size.y / 2, size.z / 2), vec4(255, 255, 255, 255), vec2(UVOffsetX * 3, 0.0f), vec3(0, 0, 1));
	verts[11] = VertexData(vec3(-size.x / 2, size.y / 2, size.z / 2), vec4(255, 255, 255, 255), vec2(UVOffsetX * 3, 1.0f), vec3(0, 0, 1));

	// face 4 - right
	verts[12] = VertexData(vec3(size.x / 2, size.y / 2, -size.z / 2), vec4(255, 255, 255, 255), vec2(UVOffsetX * 3, 1.0f), vec3(1, 0, 0));
	verts[13] = VertexData(vec3(size.x / 2, -size.y / 2, -size.z / 2), vec4(255, 255, 255, 255), vec2(UVOffsetX * 3, 0.0f), vec3(1, 0, 0));
	verts[14] = VertexData(vec3(size.x / 2, -size.y / 2, size.z / 2), vec4(255, 255, 255, 255), vec2(UVOffsetX * 4, 0.0f), vec3(1, 0, 0));
	verts[15] = VertexData(vec3(size.x / 2, size.y / 2, size.z / 2), vec4(255, 255, 255, 255), vec2(UVOffsetX * 4, 1.0f), vec3(1, 0, 0));

	// face 5 - top - z axis becomes vertical + reference
	verts[16] = VertexData(vec3(-size.x / 2, size.y / 2, size.z / 2), vec4(255, 255, 255, 255), vec2(UVOffsetX * 4, 1.0f), vec3(0, 1, 0));
	verts[17] = VertexData(vec3(-size.x / 2, size.y / 2, -size.z / 2), vec4(255, 255, 255, 255), vec2(UVOffsetX * 4, 0.0f), vec3(0, 1, 0));
	verts[18] = VertexData(vec3(size.x / 2, size.y / 2, -size.z / 2), vec4(255, 255, 255, 255), vec2(UVOffsetX * 5, 0.0f), vec3(0, 1, 0));
	verts[19] = VertexData(vec3(size.x / 2, size.y / 2, size.z / 2), vec4(255, 255, 255, 255), vec2(UVOffsetX * 5, 1.0f), vec3(0, 1, 0));

	// face 6 - bottom
	verts[20] = VertexData(vec3(-size.x / 2, -size.y / 2, size.z / 2), vec4(255, 255, 255, 255), vec2(UVOffsetX * 5, 1.0f), vec3(0, -1, 0));
	verts[21] = VertexData(vec3(-size.x / 2, -size.y / 2, -size.z / 2), vec4(255, 255, 255, 255), vec2(UVOffsetX * 5, 0.0f), vec3(0, -1, 0));
	verts[22] = VertexData(vec3(size.x / 2, -size.y / 2, -size.z / 2), vec4(255, 255, 255, 255), vec2(UVOffsetX * 6, 0.0f), vec3(0, -1, 0));
	verts[23] = VertexData(vec3(size.x / 2, -size.y / 2, size.z / 2), vec4(255, 255, 255, 255), vec2(UVOffsetX * 6, 1.0f), vec3(0, -1, 0));

	unsigned int indices[36] = {
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
		ScaleUVCOORDS(verts, 24, UVScale);
	}

	if (invertFaces) // invert faces
	{
		InvertFaces(indices, 36);
	}

	if (Wind_CCW) { InvertFaces(indices, 36); } // Reverse winding order

	t_pNewMesh->BufferMeshData(24, verts, 36, indices); // GL_STATIC_DRAW
	t_pNewMesh->SetPrimitiveType(GL_TRIANGLES);

	return t_pNewMesh;
}
// worldSize, number of vertices, UVPos,
Mesh* MeshFactory::CreatePlane(vec2 size, vec2 NumOfVerts, vec2 UVScale) // pivot, size, UVStart, UVOffset
{
	// TODO: Ability to create XY plane
	//// variables
	int numVertsX = (int)NumOfVerts.x;
	int numVertsY = (int)NumOfVerts.y;
	int numVerts = numVertsX * numVertsY;

	// create array
	VertexData *verts = new VertexData[numVerts]; //  (vertexCount.x-1)*(vertexCount-1)*2 triangles per square*3 indices per triangle;

	float width = size.x;
	float height = size.y;

	// spacing
	float xSpacing = width / (numVertsX - 1);
	float ySpacing = height / (numVertsY - 1);

	// for-loop variables
	// increment
	float xIncrement = -width * 0.5f;
	float zIncrement = -height * 0.5f;

	int indexCounter = 0;

	for (int i = 0; i < numVertsX; i++)
	{
		for (int j = 0; j < numVertsY; j++)
		{
			verts[indexCounter] = VertexData(vec3(xIncrement, 0, zIncrement), vec4(255, 255, 255, 255), vec2(0, 0), vec3(0, 0, 0));
			indexCounter++;
			xIncrement += xSpacing;
		}
		xIncrement = -width * 0.5f;
		zIncrement += ySpacing;
	}

	const int numOfIndices = 6 * (numVertsX - 1) * (numVertsY - 1); // 6 points per rectangle * number of rectangles
	unsigned int* indices = new unsigned int[numOfIndices]; // 6 * numOfRectangles
	indexCounter = 0;
	int vertex = 0;

	// start at bottom left corner, create left most box by taking y point from above, then current y points (clockwise)
	// then move right, at end of x row, increment y and continue
	for (int i = 0; i < numVertsY - 1; i++) // numVertsY - 1 = number of spaces between points on that axis, which tell how many rectangles
	{
		// y
		for (int j = 0; j < numVertsX - 1; j++)
		{
			//x
			// top right triangle
			indices[indexCounter] = vertex + numVertsX;
			indices[indexCounter + 1] = vertex + numVertsX + 1;
			indices[indexCounter + 2] = vertex + 1;

			// bottom left triangle
			indices[indexCounter + 3] = vertex + 1;
			indices[indexCounter + 4] = vertex;
			indices[indexCounter + 5] = vertex + numVertsX;
			indexCounter += 6; // next triangle
			vertex++; // next point
		}
		vertex++;
	}

	Mesh* pMesh = new Mesh();

	// generate UVCOORDS
	CalculateXZUVCoords(verts, numVerts);

	// scale UVCOORDS
	ScaleUVCOORDS(verts, numVerts, UVScale);

	pMesh->BufferMeshData(numVerts, verts, numOfIndices, indices); // GL_STATIC_DRAW
	pMesh->SetPrimitiveType(GL_TRIANGLES);

	delete[] verts;
	delete[] indices;

	return pMesh;
}
/* Mesh data assignment*/
void MeshFactory::GenerateBox(Mesh* mesh, vec2 size, bool invertFaces)
{
	std::vector<VertexData> tempList;
	tempList.push_back(VertexData(vec3(0.5f * size.x, 0.5f * size.y, 0.0f), vec4(1, 1, 1, 1), vec2(1, 1), vec3(0, 0, 0)));
	tempList.push_back(VertexData(vec3(0.5f * size.x, -0.5f * size.y, 0.0f), vec4(1, 1, 1, 1), vec2(1, 0), vec3(0, 0, 0)));
	tempList.push_back(VertexData(vec3(-0.5f * size.x, -0.5f * size.y, 0.0f), vec4(1, 1, 1, 1), vec2(0, 0), vec3(0, 0, 0)));
	tempList.push_back(VertexData(vec3(-0.5f * size.x, 0.5f * size.y, 0.0f), vec4(1, 1, 1, 1), vec2(0, 1), vec3(0, 0, 0)));

	unsigned int indices[] = {
		0, 1, 3, // First Triangle
		1, 2, 3  // Second Triangle
	};
	if (Wind_CCW) { InvertFaces(indices, 6); } // Reverse winding order
	mesh->BufferMeshData(4, tempList.data(), 6, indices);
}

void MeshFactory::GenerateCube(Mesh* mesh, vec3 size, bool invertFaces)
{
	std::vector<VertexData> tempList;
	// front
	tempList.push_back(VertexData(vec3(-0.5f * size.x, -0.5f * size.y, 0.5f * size.z), vec4(1, 1, 1, 1), vec2(0, 0), vec3(0, 0, 0))); // 0
	tempList.push_back(VertexData(vec3(-0.5f * size.x, 0.5f * size.y, 0.5f * size.z), vec4(1, 1, 1, 1), vec2(0, 1), vec3(0, 0, 0)));
	tempList.push_back(VertexData(vec3(0.5f * size.x, 0.5f * size.y, 0.5f * size.z), vec4(1, 1, 1, 1), vec2(1, 1), vec3(0, 0, 0)));
	tempList.push_back(VertexData(vec3(0.5f * size.x, -0.5f * size.y, 0.5f * size.z), vec4(1, 1, 1, 1), vec2(1, 0), vec3(0, 0, 0)));
	// back
	tempList.push_back(VertexData(vec3(-0.5f * size.x, -0.5f * size.y, -0.5f * size.z), vec4(1, 1, 1, 1), vec2(0, 0), vec3(0, 0, 0))); // 4
	tempList.push_back(VertexData(vec3(-0.5f * size.x, 0.5f * size.y, -0.5f * size.z), vec4(1, 1, 1, 1), vec2(0, 1), vec3(0, 0, 0)));
	tempList.push_back(VertexData(vec3(0.5f * size.x, 0.5f * size.y, -0.5f * size.z), vec4(1, 1, 1, 1), vec2(1, 1), vec3(0, 0, 0)));
	tempList.push_back(VertexData(vec3(0.5f * size.x, -0.5f * size.y, -0.5f * size.z), vec4(1, 1, 1, 1), vec2(1, 0), vec3(0, 0, 0)));

	unsigned int indices[] = {
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
	if (Wind_CCW) { InvertFaces(indices, 36); } // Reverse winding order
	mesh->BufferMeshData(8, tempList.data(), 36, indices);
}

Mesh* MeshFactory::TutorialCube(vec3 size, vec2 UVScale, bool invertFaces)
{
	Mesh* mesh = new Mesh();

	std::vector<VertexData> t_Verts;

	// Create vertices
	t_Verts.push_back(VertexData(vec3(0.5f, 0.5f, -0.5f), vec4(1, 1, 1, 1), vec2(1.0f, 1.0f), vec3(0.0f, 0.0f, -1.0f))); // front
	t_Verts.push_back(VertexData(vec3(0.5f, -0.5f, -0.5f), vec4(1, 1, 1, 1), vec2(1.0f, 0.0f), vec3(0.0f, 0.0f, -1.0f)));
	t_Verts.push_back(VertexData(vec3(-0.5f, -0.5f, -0.5f), vec4(1, 1, 1, 1), vec2(0.0f, 0.0f), vec3(0.0f, 0.0f, -1.0f)));
	t_Verts.push_back(VertexData(vec3(-0.5f, -0.5f, -0.5f), vec4(1, 1, 1, 1), vec2(0.0f, 0.0f), vec3(0.0f, 0.0f, -1.0f)));
	t_Verts.push_back(VertexData(vec3(-0.5f, 0.5f, -0.5f), vec4(1, 1, 1, 1), vec2(0.0f, 1.0f), vec3(0.0f, 0.0f, -1.0f)));
	t_Verts.push_back(VertexData(vec3(0.5f, 0.5f, -0.5f), vec4(1, 1, 1, 1), vec2(1.0f, 1.0f), vec3(0.0f, 0.0f, -1.0f)));

	t_Verts.push_back(VertexData(vec3(-0.5f, -0.5f, 0.5f), vec4(1, 1, 1, 1), vec2(0.0f, 0.0f), vec3(0.0f, 0.0f, 1.0f))); // back
	t_Verts.push_back(VertexData(vec3(0.5f, -0.5f, 0.5f), vec4(1, 1, 1, 1), vec2(1.0f, 0.0f), vec3(0.0f, 0.0f, 1.0f)));
	t_Verts.push_back(VertexData(vec3(0.5f, 0.5f, 0.5f), vec4(1, 1, 1, 1), vec2(1.0f, 1.0f), vec3(0.0f, 0.0f, 1.0f)));
	t_Verts.push_back(VertexData(vec3(0.5f, 0.5f, 0.5f), vec4(1, 1, 1, 1), vec2(1.0f, 1.0f), vec3(0.0f, 0.0f, 1.0f)));
	t_Verts.push_back(VertexData(vec3(-0.5f, 0.5f, 0.5f), vec4(1, 1, 1, 1), vec2(0.0f, 1.0f), vec3(0.0f, 0.0f, 1.0f)));
	t_Verts.push_back(VertexData(vec3(-0.5f, -0.5f, 0.5f), vec4(1, 1, 1, 1), vec2(0.0f, 0.0f), vec3(0.0f, 0.0f, 1.0f)));

	t_Verts.push_back(VertexData(vec3(-0.5f, 0.5f, 0.5f), vec4(1, 1, 1, 1), vec2(1.0f, 0.0f), vec3(-1.0f, 0.0f, 0.0f))); // left
	t_Verts.push_back(VertexData(vec3(-0.5f, 0.5f, -0.5f), vec4(1, 1, 1, 1), vec2(1.0f, 1.0f), vec3(-1.0f, 0.0f, 0.0f)));
	t_Verts.push_back(VertexData(vec3(-0.5f, -0.5f, -0.5f), vec4(1, 1, 1, 1), vec2(0.0f, 1.0f), vec3(-1.0f, 0.0f, 0.0f)));
	t_Verts.push_back(VertexData(vec3(-0.5f, -0.5f, -0.5f), vec4(1, 1, 1, 1), vec2(0.0f, 1.0f), vec3(-1.0f, 0.0f, 0.0f)));
	t_Verts.push_back(VertexData(vec3(-0.5f, -0.5f, 0.5f), vec4(1, 1, 1, 1), vec2(0.0f, 0.0f), vec3(-1.0f, 0.0f, 0.0f)));
	t_Verts.push_back(VertexData(vec3(-0.5f, 0.5f, 0.5f), vec4(1, 1, 1, 1), vec2(1.0f, 0.0f), vec3(-1.0f, 0.0f, 0.0f)));

	t_Verts.push_back(VertexData(vec3(0.5f, -0.5f, -0.5f), vec4(1, 1, 1, 1), vec2(0.0f, 1.0f), vec3(1.0f, 0.0f, 0.0f))); // right
	t_Verts.push_back(VertexData(vec3(0.5f, 0.5f, -0.5f), vec4(1, 1, 1, 1), vec2(1.0f, 1.0f), vec3(1.0f, 0.0f, 0.0f)));
	t_Verts.push_back(VertexData(vec3(0.5f, 0.5f, 0.5f), vec4(1, 1, 1, 1), vec2(1.0f, 0.0f), vec3(1.0f, 0.0f, 0.0f)));
	t_Verts.push_back(VertexData(vec3(0.5f, 0.5f, 0.5f), vec4(1, 1, 1, 1), vec2(1.0f, 0.0f), vec3(1.0f, 0.0f, 0.0f)));
	t_Verts.push_back(VertexData(vec3(0.5f, -0.5f, 0.5f), vec4(1, 1, 1, 1), vec2(0.0f, 0.0f), vec3(1.0f, 0.0f, 0.0f)));
	t_Verts.push_back(VertexData(vec3(0.5f, -0.5f, -0.5f), vec4(1, 1, 1, 1), vec2(0.0f, 1.0f), vec3(1.0f, 0.0f, 0.0f)));

	t_Verts.push_back(VertexData(vec3(-0.5f, -0.5f, -0.5f), vec4(1, 1, 1, 1), vec2(0.0f, 1.0f), vec3(0.0f, -1.0f, 0.0f))); // bottom
	t_Verts.push_back(VertexData(vec3(0.5f, -0.5f, -0.5f), vec4(1, 1, 1, 1), vec2(1.0f, 1.0f), vec3(0.0f, -1.0f, 0.0f)));
	t_Verts.push_back(VertexData(vec3(0.5f, -0.5f, 0.5f), vec4(1, 1, 1, 1), vec2(1.0f, 0.0f), vec3(0.0f, -1.0f, 0.0f)));
	t_Verts.push_back(VertexData(vec3(0.5f, -0.5f, 0.5f), vec4(1, 1, 1, 1), vec2(1.0f, 0.0f), vec3(0.0f, -1.0f, 0.0f)));
	t_Verts.push_back(VertexData(vec3(-0.5f, -0.5f, 0.5f), vec4(1, 1, 1, 1), vec2(0.0f, 0.0f), vec3(0.0f, -1.0f, 0.0f)));
	t_Verts.push_back(VertexData(vec3(-0.5f, -0.5f, -0.5f), vec4(1, 1, 1, 1), vec2(0.0f, 1.0f), vec3(0.0f, -1.0f, 0.0f)));

	t_Verts.push_back(VertexData(vec3(0.5f, 0.5f, 0.5f), vec4(1, 1, 1, 1), vec2(1.0f, 0.0f), vec3(0.0f, 1.0f, 0.0f))); // top
	t_Verts.push_back(VertexData(vec3(0.5f, 0.5f, -0.5f), vec4(1, 1, 1, 1), vec2(1.0f, 1.0f), vec3(0.0f, 1.0f, 0.0f)));
	t_Verts.push_back(VertexData(vec3(-0.5f, 0.5f, -0.5f), vec4(1, 1, 1, 1), vec2(0.0f, 1.0f), vec3(0.0f, 1.0f, 0.0f)));
	t_Verts.push_back(VertexData(vec3(-0.5f, 0.5f, -0.5f), vec4(1, 1, 1, 1), vec2(0.0f, 1.0f), vec3(0.0f, 1.0f, 0.0f)));
	t_Verts.push_back(VertexData(vec3(-0.5f, 0.5f, 0.5f), vec4(1, 1, 1, 1), vec2(0.0f, 0.0f), vec3(0.0f, 1.0f, 0.0f)));
	t_Verts.push_back(VertexData(vec3(0.5f, 0.5f, 0.5f), vec4(1, 1, 1, 1), vec2(1.0f, 0.0f), vec3(0.0f, 1.0f, 0.0f)));

	// if (Wind_CCW) { InvertFaces(indices, 36); } // Reverse winding order

	mesh->BufferMeshData(36, t_Verts.data(), 0, 0);

	return mesh;
}