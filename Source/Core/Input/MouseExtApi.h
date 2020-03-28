#ifndef _Mouse_Ext_Api_H_
#define _Mouse_Ext_Api_H_

#include "QwerKE_eKeys.h"

namespace QwerkE {

    struct Mouse;

    class MouseExtAPI
    {
    public:
        MouseExtAPI(Mouse* mouse) { m_Mouse = mouse; }
        ~MouseExtAPI() {}

        bool GetIsKeyDown(eKeys key) const;

        bool FrameAction(eKeys key, eKeyState state) const;

    private:
        Mouse* m_Mouse = nullptr;
    };

}
#endif // !_Mouse_Ext_Api_H_
