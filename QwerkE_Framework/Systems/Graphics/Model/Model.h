#ifndef __Model_H_
#define __Model_H_

#include <string>
#include <vector>

class Mesh;
class ShaderProgram;

class Model
{
public:
	Model();
	~Model();

    void Init(std::vector<Mesh*> meshes) { m_HotMeshes = meshes; };
    void SetupMeshes(ShaderProgram* shader);

	void Draw();

    /* Getters + Setters */
    // Getters
    std::string GetName() { return m_Name; }

    // Setters
    void SetName(std::string name) { m_Name = name; }

private:
    std::string m_Name = "Uninitialized";
	std::vector<Mesh*> m_HotMeshes;
};

#endif //!__Model_H_
