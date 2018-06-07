#ifndef _Mouse_H_
#define _Mouse_H_

#include "InputDevice.h"

struct Mouse : public InputDevice
{
	vec2 s_MousePos = vec2(0, 0); // position change from last frame
	vec2 s_MouseDelta = vec2(0, 0);
	vec2 s_MouseDragStart = vec2(0, 0);
	bool s_DragReset = false;

	void NewFrame()
	{
		if (s_DragReset)
		{
			s_MouseDragStart = 0.0f;
			s_DragReset = false;
		}

		// reset 1 frame buffers
		if (s_OneFrameBuffersAreDirty)
		{
			// m_MouseDragStart = 0.0f;
			memset(s_OneFrameKeyBuffer, eKeys_NULL_KEY, QWERKE_ONE_FRAME_MAX_INPUT * sizeof(short));
			memset(s_OneFrameValueBuffer, 0, QWERKE_ONE_FRAME_MAX_INPUT); // TODO: Do I want a 3rd key state?
			s_OneFrameBuffersAreDirty = false;
		}
	}

	Mouse(eInputDeviceTypes type);
	~Mouse();
};

#endif // !_Mouse_H_
