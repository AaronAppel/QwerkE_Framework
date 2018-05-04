#include "Controller.h"
#include "../../Engine_Enums.h"
#include "../../../Shared_Generic/Math_Includes.h"

Controller::Controller()
{
	ClearButtonCodes(); // set all buttons to unpressed, revert codes
}

Controller::Controller(int idnum)
{
	ClearButtonCodes(); // set all buttons to unpressed, revert codes
	id = idnum;
}

Controller::~Controller()
{
}

void Controller::NewFrame()
{
	// Clear delta values from last frame
	m_CursorPositionDelta = 0.0f;
	m_ScrollDelta = 0;
}

void Controller::ClearButtonCodes()
{
	for (int i = 0; i < Button_Max; i++)
	{
		m_KeyCodes[i] = 0;
		m_KeyStates[i] = 0;
	}
}

void Controller::SetButtonPressed(eGameButtons button)
{
	m_KeyStates[button] = 1;
}

void Controller::SetButtonReleased(eGameButtons button)
{
	m_KeyStates[button] = 0;
}

bool Controller::IsButtonPressed(eGameButtons button)
{
	return m_KeyStates[button];
}

unsigned short int Controller::GetKeyCode(eGameButtons button)
{
	return m_KeyCodes[button];
}

void Controller::SetKeyCode(eGameButtons index, unsigned short button)
{
	m_KeyCodes[index] = button;
}

void Controller::SetCursorPosition(vec2 position)
{
	m_CursorPositionDelta = position - m_CursorPosition;
	m_CursorPosition = position;
	// OutputMessage("\nDelta: %f, %f\n", m_CursorPositionDelta.x, m_CursorPositionDelta.y);
};

void Controller::MouseScroll(short scrollOffset)
{
	m_ScrollDelta += scrollOffset;
}