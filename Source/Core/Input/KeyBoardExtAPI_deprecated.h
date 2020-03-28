#ifndef _KeyboardExtAPI_H_
#define _KeyboardExtAPI_H_

#include "QwerKE_eKeys.h"
#include "Keyboard.h"

// TODO: Consider moving InputDevices into the InputManager class or namespace
// to make them inaccessible to outside code if fully intended.

class Keyboard;

class KeyboardExtAPI
{
public:
	KeyboardExtAPI(Keyboard* keyboard) { m_Keyboard = keyboard; }
	~KeyboardExtAPI() {}

	bool GetIsKeyDown(eKeys key) const
	{
		return m_Keyboard->s_KeyStates[key];
	}

	bool FrameAction(eKeys key, eKeyState state) const
	{
		if (m_Keyboard->s_OneFrameKeyBuffer[0] != eKeys::eKeys_NULL_KEY) // was a key even pressed?
			for (int i = 0; i < QWERKE_ONE_FRAME_MAX_INPUT; i++)
			{
				if (m_Keyboard->s_OneFrameKeyBuffer[i] == key)
					return m_Keyboard->s_OneFrameValueBuffer[i] == state;
			}
		return 0;
	}

private:
	Keyboard* m_Keyboard = nullptr;
};

#endif // !_KeyboardExtAPI_H_
