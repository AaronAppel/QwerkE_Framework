#ifndef _ModelComponent_H_
#define _ModelComponent_H_

#include "Component.h"
#include "../../Systems/Graphics/Gfx_Classes/Renderable.h"

#include <vector>

class ModelComponent : public Component
{
public:
	ModelComponent() { m_ComponentTag = eComponentTags::Component_Model; }
	~ModelComponent() {}

	// TODO:
	void SetData() {}

	const std::vector<Renderable>* LookAtRenderableList() { return &m_RenderableList; }

private:
	std::vector<Renderable> m_RenderableList;
};

#endif // !_ModelComponent_H_
