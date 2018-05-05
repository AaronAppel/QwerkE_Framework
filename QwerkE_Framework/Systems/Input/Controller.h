#ifndef __Controller_H_
#define __Controller_H_

// TODO: Create child/sub classes for different types of controllers (mouse/keyboard, gamepad, joysticks etc).
// TODO: Add multiple device functionality (XBOX controller, Joystick etc..)
// TODO: Create Event() and Command() systems for input.
#include "../../../QwerkE_Common/Math_Includes.h"
#include "../../QwerkE_Enums.h"

class Controller
{
public:
	Controller();
	Controller(int idnum);
    virtual ~Controller();

	void NewFrame(); // Clear delta values
	void ClearButtonCodes();

    void SetButtonPressed(eGameButtons button);
    void SetButtonReleased(eGameButtons button);

    bool IsButtonPressed(eGameButtons button);

	unsigned short int GetKeyCode(eGameButtons button);
	void SetKeyCode(eGameButtons index, unsigned short button);

	void SetCursorPosition(vec2 position);

	void MouseScroll(short scrollOffset);

	vec2 GetCursorPosition() { return m_CursorPosition; }

	vec2 GetMousePosDelta() { return m_CursorPositionDelta; }
	short GetMouseScrollDelta() { return m_ScrollDelta; }

protected:
	int id = -1; // player number
	// Mouse
	vec2 m_CursorPosition = 0.0f;
	vec2 m_LastCursorPosition = 0.0f; // Used for deltaPos calculation
	vec2 m_CursorPositionDelta = 0.0f;

	short m_ScrollDelta = 0; // negative means towards user. 1 per "tick".
	vec2 m_MouseDrag = 0.0f; // TODO: When mouse is down add mouse delta to check distance from initial mouse down position

	// Keyboard
	unsigned short int m_KeyCodes[Button_Max];
	bool m_KeyStates[Button_Max];
};

#endif //__Controller_H_