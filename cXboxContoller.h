#ifndef _CXBOXCONTROLLER_H
#define _CXBOXCONTROLLER_H

#include <Xinput.h>
#include <windows.h>

class cXboxController{

private:
	XINPUT_STATE _controllerState;
	int _controllerNum;

public:
	cXboxController(int playerNum);
	XINPUT_STATE GetState();
	bool isConnected();
	void Vibrate(int leftVal = 0, int rightVal = 0);

};

#endif