#include "Gamepad.h"
#include <Windows.h>
//linking in the Xinput library
#pragma comment(lib, "Xinput.lib")
//THIS CODE DOES NOT COVER THE ENTIRE GAMEPAD OF AN XBOX 360 CONTROLLER
//the default constructor
Gamepad::Gamepad(){}
//Overloaded Constructor
Gamepad::Gamepad(int a_index){
	m_iGamepadIndex = a_index - 1;
}

XINPUT_STATE Gamepad::GetState(){//gets the state of the controller
	//temporary XINPUT STATE to return
	XINPUT_STATE GamepadState;
	//zeros memory
	ZeroMemory(&GamepadState, sizeof(XINPUT_STATE));
	//get the state of the gamepad
	XInputGetState(m_iGamepadIndex, &GamepadState);
	//return Gamepad state
	return GamepadState;
}
int Gamepad::GetIndex(){//gets the private variabel iGamepadIndex
	return m_iGamepadIndex;
}
bool Gamepad::Connected(){
	ZeroMemory(&m_State, sizeof(XINPUT_STATE));
	//get the state of the gamepad
	DWORD Result = XInputGetState(m_iGamepadIndex, &m_State);
	if (Result == ERROR_SUCCESS)
		return true; //the gamepad is connected
	else
		return false; //the gamepad is not connected

}
void Gamepad::Update(){//updates the state

	m_State = GetState(); //Obtain current gamepad state
}
bool Gamepad::LStick_InDeadzone(){

	
	// Obtain the X & Y axes of the stick
	short sX = m_State.Gamepad.sThumbLX;
	short sY = m_State.Gamepad.sThumbLY;

	// X axis is outside of deadzone
	if (sX > XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE ||
		sX < -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE)
		return false;

	// Y axis is outside of deadzone
	if (sY > XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE ||
		sY < -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE)
		return false;

	// One (or both axes) axis is inside of deadzone
	return true;
}

// Deadzone check for Right Thumbstick
bool Gamepad::RStick_InDeadzone(){

	// Obtain the X & Y axes of the stick
	short sX = m_State.Gamepad.sThumbRX;
	short sY = m_State.Gamepad.sThumbRY;

	// X axis is outside of deadzone
	if (sX > XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE ||
		sX < -XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE)
		return false;

	// Y axis is outside of deadzone
	if (sY > XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE ||
		sY < -XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE)
		return false;

	// One (or both axes) axis is inside of deadzone
	return true;
}
// Return X axis of left stick
float Gamepad::LeftStick_X(){//to be used for the left analogue stick

	// Obtain X axis of left stick
	short sX = m_State.Gamepad.sThumbLX;

	// Return axis value, converted to a float
	return (static_cast<float>(sX) / 32768.0f);
}

// Return Y axis of left stick//left analogue stick
float Gamepad::LeftStick_Y(){

	// Obtain Y axis of left stick
	short sY = m_State.Gamepad.sThumbLY;

	// Return axis value, converted to a float
	return (static_cast<float>(sY) / 32768.0f);
}

// Return X axis of right stick
float Gamepad::RightStick_X(){//right analogue stick

	// Obtain X axis of right stick
	short sX = m_State.Gamepad.sThumbRX;

	// Return axis value, converted to a float
	return (static_cast<float>(sX) / 32768.0f);
}

// Return Y axis of right stick
float Gamepad::RightStick_Y(){//right analogue stick
	// Obtain the Y axis of the left stick
	short sY = m_State.Gamepad.sThumbRY;

	// Return axis value, converted to a float
	return (static_cast<float>(sY) / 32768.0f);
}
// Return value of left trigger
float Gamepad::LeftTrigger(){

	// Obtain value of left trigger
	BYTE Trigger = m_State.Gamepad.bLeftTrigger;

	if (Trigger > XINPUT_GAMEPAD_TRIGGER_THRESHOLD)
		return Trigger / 255.0f;

	return 0.0f; // Trigger was not pressed
}

// Return value of right trigger
float Gamepad::RightTrigger(){

	// Obtain value of right trigger
	BYTE Trigger = m_State.Gamepad.bRightTrigger;

	if (Trigger > XINPUT_GAMEPAD_TRIGGER_THRESHOLD)
		return Trigger / 255.0f;
	else
		return 0.0f; // Trigger was not pressed
	
}
void Gamepad::Rumble(float a_fLeftMotor, float a_fRightMotor){//vibration function

	// Vibration state
	XINPUT_VIBRATION VibrationState;

	// Zero memory
	ZeroMemory(&VibrationState, sizeof(XINPUT_VIBRATION));

	// Calculate vibration values
	int iLeftMotor = int(a_fLeftMotor * 65535.0f);
	int iRightMotor = int(a_fRightMotor * 65535.0f);

	// Set vibration values
	VibrationState.wLeftMotorSpeed = iLeftMotor;
	VibrationState.wRightMotorSpeed = iRightMotor;

	// Set the vibration state
	XInputSetState(m_iGamepadIndex, &VibrationState);
}