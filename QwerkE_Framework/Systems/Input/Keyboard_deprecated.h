#ifndef _Keyboard_H_
#define _Keyboard_H_

#include "InputDevice.h"

// TODO: Consider moving InputDevices into the InputManager class or namespace
// to make them inaccessible to outside code if fully intended.

struct Keyboard : public InputDevice
{
	Keyboard(eInputDeviceTypes type);
	~Keyboard();
};

#endif // !_Keyboard_H_
