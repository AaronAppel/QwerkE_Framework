#ifndef _KeyboardExtAPI_H_
#define _KeyboardExtAPI_H_

#include "Keyboard.h"
#include "QwerKE_eKeys.h"

// TODO: Consider moving InputDevices into the InputManager class or namespace
// to make them inaccessible to outside code if fully intended.

class Keyboard;

class KeyboardExtAPI
{
public:
	KeyboardExtAPI(Keyboard* keyboard) { m_Keyboard = keyboard; }
	~KeyboardExtAPI() {}

	bool GetIsKeyDown(eKeys key) const;
	bool FrameAction(eKeys key, eKeyState state) const;

private:
	Keyboard* m_Keyboard = nullptr;
};

#endif // !_KeyboardExtAPI_H_
