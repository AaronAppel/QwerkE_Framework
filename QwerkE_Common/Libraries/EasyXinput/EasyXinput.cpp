#include "EasyXinput.h"
#include <cmath>

#define Xin_Success 0

// XinVec2
// avoid declaring <cmath> in header
float XinVec2::Length() const { return sqrt(x*x + y * y); }

// setup
XinputHandler::XinputHandler(int numPlayers)
{
	m_NumPlayers = numPlayers;
	m_PlayerStates = new XINPUT_STATE*[numPlayers];

	for (int i = 0; i < numPlayers; i++) // load player list
	{
		m_PlayerStates[i] = new XINPUT_STATE;
	}
}
// tear down
XinputHandler::~XinputHandler()
{
}
// utility
void XinputHandler::ResetState(int player)
{
	memset(&m_PlayerStates[player], 0, sizeof(XINPUT_STATE)); // clear data
}

void XinputHandler::ResetStates()
{
	for (unsigned int i = 0; i < m_NumPlayers; i++)
	{
		memset(&m_PlayerStates[i], 0, sizeof(XINPUT_STATE)); // clear data
	}
}

bool XinputHandler::UpdatePlayerState(int player)
{
	// TODO: Figure out why XInputGetState gives LNK2019
	DWORD result = 0;// = XInputGetState((DWORD)player, m_PlayerStates[player]); // XInputGetState(PORT, &ControllerState );
	if (result == Xin_Success)
		return true;
	else
	{
		// if (m_Debugging) OutputMessage("\nXinputManager: Error reading gamepad state for Player %i", player];
		return false;
	}
}
// input
XinVec2 XinputHandler::LeftStick(int player)
{
	XinVec2 leftstick = XinVec2(m_PlayerStates[player]->Gamepad.sThumbRX, m_PlayerStates[player]->Gamepad.sThumbRY);

	float magnitude = leftstick.Length();

	if (magnitude < m_StickDeadZone.x)
	{
		leftstick.Set(0, 0);
	}
	else
	{
		// get the normalized direction vector of the thumbstick
		XinVec2 direction = leftstick / magnitude;

		magnitude = (magnitude - m_StickDeadZone.x) / (32767 - m_StickDeadZone.x);

		// clamp the magnitude to 1
		if (magnitude > 1)
			magnitude = 1;

		leftstick = direction * magnitude;
	}
	// if (m_Debugging) OutputMessage("\nController Sticks:%f, %f\r\n", leftstick.x, leftstick.y);
	return XinVec2(leftstick.x, leftstick.y);
}

XinVec2 XinputHandler::RightStick(int player)
{
	XinVec2 rightstick = XinVec2(m_PlayerStates[player]->Gamepad.sThumbRX, m_PlayerStates[player]->Gamepad.sThumbRY);

	float magnitude = rightstick.Length();

	if (magnitude < m_StickDeadZone.y)
	{
		rightstick.Set(0, 0);
	}
	else
	{
		// get the normalized direction vector of the thumbstick
		XinVec2 direction = rightstick / magnitude;

		magnitude = (magnitude - m_StickDeadZone.y) / (32767 - m_StickDeadZone.y);

		// clamp the magnitude to 1
		if (magnitude > 1)
			magnitude = 1;

		rightstick = direction * magnitude;
	}
	return XinVec2(rightstick.x, rightstick.y);
}

XinVec2 XinputHandler::Triggers(int player)
{
	// state.Gamepad.bLeftTrigger; // value between 0 and 255
	float leftTrigger = (float)m_PlayerStates[player]->Gamepad.bLeftTrigger / 255;
	float rightTrigger = (float)m_PlayerStates[player]->Gamepad.bRightTrigger / 255;
	return XinVec2(leftTrigger, rightTrigger);
}

bool XinputHandler::ButtonIsDown(int button, int player)
{
	return ((m_PlayerStates[player]->Gamepad.wButtons & button) != 0);
}

bool XinputHandler::ButtonIsDown(int button)
{
	return ((m_PlayerStates[m_CurrentPlayer]->Gamepad.wButtons & button) != 0);
}

// Face
// TODO:: Find a good naming convention for interface methods
bool XinputHandler::ADown(int player)
{
	return ((m_PlayerStates[player]->Gamepad.wButtons & XINPUT_GAMEPAD_A) != 0);
}

bool XinputHandler::BDown(int player)
{
	return ((m_PlayerStates[player]->Gamepad.wButtons & XINPUT_GAMEPAD_B) != 0);
}

bool XinputHandler::XDown(int player)
{
	return ((m_PlayerStates[player]->Gamepad.wButtons & XINPUT_GAMEPAD_X) != 0);
}

bool XinputHandler::YDown(int player)
{
	return ((m_PlayerStates[player]->Gamepad.wButtons & XINPUT_GAMEPAD_Y) != 0);
}
// DPad
bool XinputHandler::PadUpIsDown(int player)
{
	return ((m_PlayerStates[player]->Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_UP) != 0);
}

bool XinputHandler::PadDownIsDown(int player)
{
	return ((m_PlayerStates[player]->Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_DOWN) != 0);
}

bool XinputHandler::PadLeftIsDown(int player)
{
	return ((m_PlayerStates[player]->Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_LEFT) != 0);
}

bool XinputHandler::PadRightIsDown(int player)
{
	return ((m_PlayerStates[player]->Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_RIGHT) != 0);
}
// Bumper
bool XinputHandler::BumpLeftDown(int player)
{
	return ((m_PlayerStates[player]->Gamepad.wButtons & XINPUT_GAMEPAD_LEFT_SHOULDER) != 0);
}

bool XinputHandler::BumpRightDown(int player)
{
	return ((m_PlayerStates[player]->Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER) != 0);
}
// Start + Back
bool XinputHandler::StartDown(int player)
{
	return ((m_PlayerStates[player]->Gamepad.wButtons & XINPUT_GAMEPAD_START) != 0);
}
bool XinputHandler::BackDown(int player)
{
	return ((m_PlayerStates[player]->Gamepad.wButtons & XINPUT_GAMEPAD_BACK) != 0);
}