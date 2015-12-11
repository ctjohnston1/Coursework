//cXboxController.cpp

#include "cXboxContoller.h"

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

}

