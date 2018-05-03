#ifndef _EasyXinput_H_
#define _EasyXinput_H_

// https://msdn.microsoft.com/en-us/library/windows/desktop/microsoft.directx_sdk.reference.xinput_gamepad(v=vs.85).aspx <-- button codes
// https://katyscode.wordpress.com/2013/08/30/xinput-tutorial-part-1-adding-gamepad-support-to-your-windows-game/ <-- reading Xinput
// https://msdn.microsoft.com/en-ca/library/windows/desktop/ee417001(v=vs.85).aspx <- microsoft tutorial
// "The constant XINPUT_GAMEPAD_TRIGGER_THRESHOLD may be used as the value which bLeftTrigger and bRightTrigger must be greater than to register as pressed." - MSDN XINPUT_GAMEPAD structure
// XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE, XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE

#include <Xinput.h>
// #include Xinput.lib, Xinput9_1_0.lib or other version

/*  HOW TO USE
XinputHandler newHandler = new XinputHanlder(4);
...
newHanlder->ResetStates();
newHanlder->SetPlayer(0);
newHanlder->UpdatePlayerState();
if(newHanlder->AButtonIsDown())
    m_Player->Jump();
...
*/

// TODO:: increase efficiency
// Compare previous frame state to see if face buttons changed.
// If they did, queue an event, otherwise don't waste ram and processor's time
// Add option to disable auto stick+trigger event generation

// TODO: consider removing dependencies like vec2 and std::vector to make incorporation simpler
// TODO: Remove m_CurrentPlayer?

// TODO:: Finalize interface.
// Find better variable and function names. Possibly add prefixes like xin_.

struct XinVec2
{
	float x = 0.0f;
	float y = 0.0f;
	XinVec2() {};
	XinVec2(float aX, float aY)	{ x = aX; y = aY; }
	XinVec2(float a) { x = a; y = a; }
	float Length() const; // avoid including <cmath> in .h
	void Set(float aX, float aY) { x = aX; y = aY; };
	XinVec2 operator /(const float a) { return XinVec2(this->x / a, this->y / a); };
	XinVec2 operator *(const float a) { return XinVec2(this->x * a, this->y * a); };
};

class XinputHandler
{
public:
	// setup
	XinputHandler(int numPlayers);
	// tear down
	~XinputHandler();

	// utility
	void ResetState() { ResetState(m_CurrentPlayer); };
	void ResetState(int player);
	void ResetStates();

	void SetPlayer(int player) { m_CurrentPlayer = player; };
	void SetStickDeadZone(int deadzone) { m_StickDeadZone = (float)deadzone; };
	void SetTriggerDeadZone(int deadzone) { m_TriggerDeadZone = deadzone; };

	bool UpdatePlayerState() { return UpdatePlayerState(m_CurrentPlayer); };
	bool UpdatePlayerState(int player);

	//// input
	// Sticks + Triggers
	XinVec2 LeftStick() { return LeftStick(m_CurrentPlayer); };
	XinVec2 LeftStick(int player);

	XinVec2 RightStick() { return RightStick(m_CurrentPlayer); };
	XinVec2 RightStick(int player);

	XinVec2 Triggers() { return Triggers(m_CurrentPlayer); };
	XinVec2 Triggers(int player);

	bool ButtonIsDown(int button, int player = 0);
	bool ButtonIsDown(int button);

	// Face
	bool ADown() { return ADown(m_CurrentPlayer); };
	bool ADown(int player);

	bool BDown() { return BDown(m_CurrentPlayer); };
	bool BDown(int player);

	bool XDown() { return XDown(m_CurrentPlayer); };
	bool XDown(int player);

	bool YDown() { return YDown(m_CurrentPlayer); };
	bool YDown(int player);
	// DPad
	bool PadUpIsDown() { return PadUpIsDown(m_CurrentPlayer); };
	bool PadUpIsDown(int player);

	bool PadDownIsDown() { return PadDownIsDown(m_CurrentPlayer); };
	bool PadDownIsDown(int player);

	bool PadLeftIsDown() { return PadLeftIsDown(m_CurrentPlayer); };
	bool PadLeftIsDown(int player);

	bool PadRightIsDown() { return PadRightIsDown(m_CurrentPlayer); };
	bool PadRightIsDown(int player);
	// Bumper
	bool BumpLeftDown() { return BumpLeftDown(m_CurrentPlayer); };
	bool BumpLeftDown(int player);

	bool BumpRightDown() { return BumpRightDown(m_CurrentPlayer); };
	bool BumpRightDown(int player);
	// Start + Back
	bool StartDown() { return StartDown(m_CurrentPlayer); };
	bool StartDown(int player);

	bool BackDown() { return BackDown(m_CurrentPlayer); };
	bool BackDown(int player);

private:
	XinVec2 m_StickDeadZone;
	int m_TriggerDeadZone;

	unsigned int m_NumPlayers; // change numPlayers during runtime?
	unsigned int m_CurrentPlayer;

	// TODO: reduce polling by generating events.
	// Or let input manager handle that
	XINPUT_STATE** m_PlayerStates;
};

#endif // !_EasyXinput_H_