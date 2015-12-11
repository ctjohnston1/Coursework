//cXboxController.cpp

#include "cXboxContoller.h"
#include <Windows.h>
#define _AMD_64_
#pragma comment(lib, "Xinput.lib")

cXboxController::cXboxController(int playerNumber){

//this is to set the controller number
	_controllerNum = playerNumber - 1;
}

XINPUT_STATE cXboxController::GetState(){
	//make the state Zero 
	ZeroMemory(&_controllerState, sizeof(XINPUT_STATE));
	//Get the state
	XInputGetState(_controllerNum, &_controllerState);

	return _controllerState;
}
bool cXboxController::isConnected(){

	//Zero state
	ZeroMemory(&_controllerState, sizeof(XINPUT_STATE));
	//Get state
	DWORD Result = XInputGetState(_controllerNum, &_controllerState);

	if (Result == ERROR_SUCCESS){
		return true;
	}
	else{
		return false;
	}

}

void cXboxController::Vibrate(int leftVal, int rightVal){
	//create a state for Vibration

	XINPUT_VIBRATION vibration;
	//and set the vibration values
	vibration.wLeftMotorSpeed = leftVal;
	vibration.wRightMotorSpeed = rightVal;

	//vibrate the controller
	XInputSetState(_controllerNum, &vibration);
}
