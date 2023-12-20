#include "TransformRoutine.h"

#include "../GameObject.h"

namespace QwerkE {

    void TransformRoutine::Initialize()
    {
        m_pParent->AddUpdateRoutine(this);
        m_Type = eRoutineTypes::Routine_Transform;
    }

    void TransformRoutine::Update(double a_Deltatime)
    {
        if (!m_pParent) return;

        m_pParent->SetPosition(m_pParent->GetPosition() + (m_PositionOffset * m_Speed));
        m_pParent->SetRotation(m_pParent->GetRotation() + (m_RotationOffset * m_Speed));
        m_pParent->SetScale(m_pParent->GetScale() + (m_ScaleOffset * m_Speed));
    }

}
