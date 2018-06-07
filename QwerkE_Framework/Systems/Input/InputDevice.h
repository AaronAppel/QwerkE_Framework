#ifndef _InputDevice_H_
#define _InputDevice_H_

#include "../../QwerkE_Enums.h"
#include "QwerKE_eKeys.h"
#include "InputManager.h" // QWERKE_ONE_FRAME_MAX_INPUT

#include <string>

// InputDevice() is meant to abstract input to come from any device.

struct InputDevice // abstract
{
	eInputDeviceTypes GetType() const { return m_DeviceType; }

	void SetType(eInputDeviceTypes type) { m_DeviceType = type; }

	unsigned short* s_KeyCodex; // [eKeys_MAX] = { 0 }; // initialize to 0
	bool s_KeyStates[eKeys_MAX] = { false }; // initialize to false

	// frame by frame input tracking
	bool s_OneFrameBuffersAreDirty = true; // wipe at init
	unsigned short s_OneFrameKeyBuffer[12]; // TODO: Use QWERKE_ONE_FRAME_MAX_INPUT
	bool s_OneFrameValueBuffer[12] = { false };

	virtual void RaiseInputEvent(eKeys key, eKeyState state)
	{
		s_OneFrameBuffersAreDirty = true;

		for (int i = 0; i < 12; i++)
		{
			if (s_OneFrameKeyBuffer[i] == eKeys_NULL_KEY)
			{
				s_OneFrameKeyBuffer[i] = key;
				s_OneFrameValueBuffer[i] = state;
				return;
			}
		}
	}

	virtual void NewFrame()
	{
		// reset 1 frame buffers
		if (s_OneFrameBuffersAreDirty)
		{
			// m_MouseDragStart = 0.0f;
			memset(s_OneFrameKeyBuffer, eKeys_NULL_KEY, 12 * sizeof(short));
			memset(s_OneFrameValueBuffer, 0, 12); // TODO: Do I want a 3rd key state?
			s_OneFrameBuffersAreDirty = false;
		}
	}

protected:
	InputDevice(eInputDeviceTypes type);
	virtual ~InputDevice();

	eInputDeviceTypes m_DeviceType = eInputDeviceTypes::Max_Device;
};

#endif // !_InputDevice_H_
