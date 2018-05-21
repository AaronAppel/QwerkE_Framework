#ifndef _Model_H_
#define _Model_H_

#include <string>
#include <vector>

class Mesh;
class ShaderProgram;
struct MaterialData;

class Model
{
public:
	Model();
	~Model();

    void Init(std::vector<Mesh*> meshes) { m_Meshes = meshes; };
    void SetupMeshAttributes(ShaderProgram* shader); // TODO: Deprecate

	void Draw();

    /* Getters + Setters */
    // Getters
    std::string GetName() { return m_Name; }

    // Setters
    void SetName(std::string name) { m_Name = name; }

	std::vector<Mesh*> m_Meshes; // TODO: private
	std::vector<MaterialData*> m_Materials;
	std::vector<ShaderProgram*> m_Shaders;

private:
    std::string m_Name = "Uninitialized";
};

#endif //!_Model_H_
