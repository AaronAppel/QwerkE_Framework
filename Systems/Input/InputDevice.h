#ifndef _Input_Device_H_
#define _Input_Device_H_

#include "QwerKE_eKeys.h"

namespace QwerkE {

    // TODO: Should be class?
    struct InputDevice
    {
        InputDevice() {}
        virtual ~InputDevice() {}

        eInputDeviceTypes GetType() const { return m_DeviceType; }

        void SetType(eInputDeviceTypes type) { m_DeviceType = type; }

        unsigned short* s_KeyCodex; // [eKeys_MAX] = { 0 }; // initialize to 0
        bool s_KeyStates[eKeys_MAX] = { false }; // initialize to false

        // Frame by frame input tracking
        bool s_OneFrameBuffersAreDirty = true;
        unsigned short s_OneFrameKeyBuffer[12]; // TODO: Use QWERKE_ONE_FRAME_MAX_INPUT
        bool s_OneFrameValueBuffer[12] = { false };

        virtual void RaiseInputEvent(eKeys key, eKeyState state);

        virtual void NewFrame();

        InputDevice(eInputDeviceTypes type) { m_DeviceType = type; }

        eInputDeviceTypes m_DeviceType = eInputDeviceTypes::Max_Device;
    };

}
#endif // !_Input_Device_H_
