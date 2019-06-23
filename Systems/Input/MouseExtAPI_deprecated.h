#ifndef _MouseExtAPI_H_
#define _MouseExtAPI_H_

#include "QwerKE_eKeys.h"

class Mouse;

class MouseExtAPI
{
public:
	MouseExtAPI(Mouse* mouse) { m_Mouse = mouse; }
	~MouseExtAPI() {}

	bool GetIsKeyDown(eKeys key) const
	{
		return m_Mouse->s_KeyStates[key];
	}

	bool FrameAction(eKeys key, eKeyState state) const
	{
		if (m_Mouse->s_OneFrameKeyBuffer[0] != eKeys::eKeys_NULL_KEY) // was a key even pressed?
			for (int i = 0; i < QWERKE_ONE_FRAME_MAX_INPUT; i++)
			{
				if (m_Mouse->s_OneFrameKeyBuffer[i] == key)
					return m_Mouse->s_OneFrameValueBuffer[i] == state;
			}
		return 0;
	}

private:
	Mouse* m_Mouse = nullptr;
};

#endif // !_MouseExtAPI_H_
