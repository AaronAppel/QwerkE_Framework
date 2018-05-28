#ifndef _GameObject_H_
#define _GameObject_H_

#include "../../../QwerkE_Common/Math_Includes.h"
#include "../QwerkE_Enums.h"

#include <map>
#include <vector>

class Scene;
class Component;
class Routine;
class GameObject;

// TODO: setup a Unity esq transform for a GameObject
struct Transform
{
	// MyMatrix s_Mat; Use?

	vec3 s_Position = 0; // calculate from matrix?
	vec3 s_Rotation = 0;
	vec3 s_Scale = 1.0f;

	vec3 s_Forward = vec3(0, 0, 1); // TODO: Calculate instead of saving?
	vec3 s_Up = vec3(0, 1, 0);
	vec3 s_Right = vec3(1, 0, 0);

	// TODO:
	void Scale(vec3 scale) {}
	void Rotate(vec3 rotation) {}
	void Translate(vec3 translation) {}

	// TODO: Use quaternions to avoid gimble lock
};

class GameObject
{
public:
	GameObject(Scene* scene);
	GameObject(Scene* scene, vec3 position);
	~GameObject();

	void Update(double deltatime);
	void Draw(GameObject* camera);

	void AddComponent(Component* component);
	void RemoveComponent(eComponentTags tag) { m_Components.erase(tag); };

	void AddRoutine(Routine* routine);
	void RemoveRoutine(Routine* routine);

	void AddUpdateRoutine(Routine* routine);
	void AddDrawRoutine(Routine* routine);

	void Reset();
	void Activate();
	void Deactivate();

	const std::map<eComponentTags, Component*>* SeeComponents() const { return &m_Components; }
	const std::vector<Routine*>* SeeUpdateRoutines() { return &m_UpdateList; }
	const std::vector<Routine*>* SeeDrawRoutines() { return &m_DrawList; }

	/* Getters + Setters */
	// getters
	std::string GetName() { return m_Name; };
	// Transform* GetTransform() const { return &m_Transform; }
	vec3 GetPosition() const { return m_Transform.s_Position; };
	vec3 GetRotation() const { return m_Transform.s_Rotation; };
	vec3 GetScale() const { return m_Transform.s_Scale; };
	Component* GetComponent(eComponentTags tag);
	Routine* GetFirstDrawRoutineOfType(eRoutineTypes type);
	Routine* GetFirstUpdateRoutineOfType(eRoutineTypes type);
	int GetRenderOrder() { return m_RenderOrder; };
	Scene* GetScene() { return m_pScene; };
	eGameObjectTags GetTag() { return m_Tag; }

	// setters
	// TODO: overload functions to take object like float[x]s
	void UpdatePosition(vec3 position) { m_Transform.s_Position = position; }; // box 2d
	void UpdateRotation(vec3 rotation) { m_Transform.s_Rotation = rotation; }; // box 2d
	void SetName(std::string name) { m_Name = name; };
	void SetPosition(vec3 position);
	void SetRotation(vec3 rotation);
	void SetScale(vec3 scale) { m_Transform.s_Scale = scale; };
	void SetRenderOrder(int order) { m_RenderOrder = order; };
	void SetTag(eGameObjectTags tag) { m_Tag = tag; }

private:
	Scene* m_pScene = nullptr;
	std::string m_Name = "Uninitialized";
	eGameObjectTags m_Tag = GO_Tag_Null;

	Transform m_Transform;

	int m_BaseUpdateListSize = 0; // TODO: make use of these of delete
	std::vector<Routine*> m_UpdateList;
	int m_BaseDrawListSize = 0;
	std::vector<Routine*> m_DrawList;
	int m_RenderOrder = 100;

	std::map<eComponentTags, Component*> m_Components;
};

#endif //!_GameObject_H_
