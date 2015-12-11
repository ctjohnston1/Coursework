#ifndef GAMEPAD_H
#define GAMEPAD_H

#include <Windows.h>
#include <Xinput.h>


class Gamepad{

public:
	//constructors
	Gamepad();
	Gamepad(int a_iIndex);
	void  Update(); //updates the gamepad
	//the analogue sticks
	bool LStick_InDeadzone();
	bool RStick_InDeadzone();
	float LeftStick_X();  // Returns X axis of left stick
	float LeftStick_Y();  // Returns Y axis of left stick
	float RightStick_X(); // Returns X axis of right stick
	float RightStick_Y(); // Returns Y axis of right stick

	// the triggers
	float LeftTrigger();  // Returns value of left trigger
	float RightTrigger(); // Returns value of right trigger
	//functions

	XINPUT_STATE GetState();
	int GetIndex();
	bool Connected();

	//vibrate 
	void Rumble(float a_fLeftMotor = 0.0f, float a_fRightMotor = 0.0f);
private:
	XINPUT_STATE m_State; //current state of gamepad
	int m_iGamepadIndex; //Gamepad index (1,2,3,4)


};




#endif