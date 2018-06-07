#include "KeyBoardExtAPI.h"

bool KeyboardExtAPI::GetIsKeyDown(eKeys key) const
{
	return m_Keyboard->s_KeyStates[key];
}

bool KeyboardExtAPI::FrameAction(eKeys key, eKeyState state) const
{
	if (m_Keyboard->s_OneFrameKeyBuffer[0] != eKeys::eKeys_NULL_KEY) // was a key even pressed?
		for (int i = 0; i < QWERKE_ONE_FRAME_MAX_INPUT; i++)
		{
			if (m_Keyboard->s_OneFrameKeyBuffer[i] == key)
				return m_Keyboard->s_OneFrameValueBuffer[i] == state;
		}
	return 0;
}