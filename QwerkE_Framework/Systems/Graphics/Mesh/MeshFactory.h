#ifndef _MeshFactory_H_
#define _MeshFactory_H_

#include "../../../../QwerkE_Common/Math_Includes.h"
#include "Model.h"

struct VertexData;
class Mesh;
class Model;

// TODO: Class unnecessary

class MeshFactory
{
public:
	MeshFactory() {};
	~MeshFactory() {};

	/* OBJ loading */
	Mesh* ImportOBJMesh(const char* fileDirectory, vec3 objScale, vec2 UVScale, bool invertFaces);
	Model* ImportOBJModel(const char* fileDirectory, vec3 objScale = vec3(1,1,1), vec2 UVScale = vec2(1,1), bool invertFaces = false) { return new Model(); }; // TODO: Write function

	/* Mesh creation */
	// defined in MeshShapes.cpp
	static Mesh* CreateTestModel();
	static Mesh* CreateBox(vec2 size);
	static Mesh* CreateCircle(float radius, unsigned int points, vec2 UVScale);
	static Mesh* CreateCube(vec3 size, vec2 UVScale = vec2(1.0f, 1.0f), bool invertFaces = false);
	static Mesh* CreatePlane(vec2 size, vec2 NumOfVerts, vec2 UVScale);

	static Mesh* TutorialCube(vec3 size, vec2 UVScale = vec2(1.0f, 1.0f), bool invertFaces = false);

	/* Mesh data assignment/re-assignment */
	void GenerateBox(Mesh* mesh, vec2 size, bool invertFaces = false);
	void GenerateCube(Mesh* mesh, vec3 size, bool invertFaces = false);
};

#endif //!_MeshFactory_H_
