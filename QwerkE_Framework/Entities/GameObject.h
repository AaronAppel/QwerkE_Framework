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
	MyMatrix m_Mat;

	vec3 m_Position = 0; // calculate from matrix?
	vec3 m_Rotation = 0;
	vec3 m_Scale = 1.0f;

	vec3 m_Forward() {} // calculate from matrix?
	vec3 m_Right() {}
	vec3 m_Up() {}

	void Rotate(vec3 rotation) {}
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

	/* Getters + Setters */
	// getters
	std::string GetName() { return m_Name; };
	vec3 GetPosition() { return m_Position; };
	vec3 GetRotation() { return m_Rotation; };
	vec3 GetScale() { return m_Scale; };
	Component* GetComponent(eComponentTags tag);
	Routine* GetFirstDrawRoutineOfType(eRoutineTypes type);
	Routine* GetFirstUpdateRoutineOfType(eRoutineTypes type);
	int GetRenderOrder() { return m_RenderOrder; };
	Scene* GetScene() { return m_pScene; };
	eGameObjectTags GetTag() { return m_Tag; }

	// setters
	// TODO: overload functions to take object like float[x]s
	void UpdatePosition(vec3 position) { m_Position = position; }; // box 2d
	void UpdateRotation(vec3 rotation) { m_Rotation = rotation; }; // box 2d
	void SetName(std::string name) { m_Name = name; };
	void SetPosition(vec3 position);
	void SetRotation(vec3 rotation);
	void SetScale(vec3 scale) { m_Scale = scale; };
	void SetRenderOrder(int order) { m_RenderOrder = order; };
	void SetTag(eGameObjectTags tag) { m_Tag = tag; }

private:
	Scene * m_pScene = nullptr;
	std::string m_Name = "Uninitialized";
	eGameObjectTags m_Tag = GO_Tag_Null;

	vec3 m_Position = 0;
	vec3 m_Rotation = 0;
	vec3 m_Scale = 1.0f;

	int m_BaseUpdateListSize = 0; // TODO: make use of these of delete
	std::vector<Routine*> m_UpdateList;
	int m_BaseDrawListSize = 0;
	std::vector<Routine*> m_DrawList;
	int m_RenderOrder = 100;

	std::map<eComponentTags, Component*> m_Components;

	// Direction vectors
	float m_FacingAngle = 0; // Y axis
	vec3 m_Forward = vec3(0, 0, 1);
	vec3 m_Up = vec3(0, 1, 0);
	vec3 m_Right = vec3(1, 0, 0);
};

#endif //!_GameObject_H_
