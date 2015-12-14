/*
==================================================================================
cWNDManager.cpp
==================================================================================
*/
//the includes for the window manager
#include "cWNDManager.h"
#include <ctime>
#include <iostream>
#include <windows.h>
#include "GL/glut.h"
#include "wglext.h"
#include "windowOGL.h"
#include "GameConstants.h"

cWNDManager* cWNDManager::pInstance = NULL;

typedef HGLRC(APIENTRYP PFNWGLCREATECONTEXTATTRIBSARBPROC)(HDC, HGLRC, const int*);
PFNWGLCREATECONTEXTATTRIBSARBPROC wglCreateContextAttribsARB = NULL;

/*
=================================================================================
Constructor
=================================================================================
*/
cWNDManager::cWNDManager()
{
	//a list of private variables to be used throughout the different functions of the class
	m_isRunning = false;
	m_winOGL = NULL;
	m_hinstance = NULL;
	m_lastTime = 0;
	m_camera = false; //this is the private variable that controlls the camera switch 
	m_soundtrack = false; //this is the private variable that controlls the sound switch
	
}
/*
=================================================================================
Singleton Design Pattern
=================================================================================
*/
cWNDManager* cWNDManager::getInstance()
{
	//if pInstance is currently Null or not made
	if (pInstance == NULL)
	{
		//create a new instance of the cWNDManager constructor.
		pInstance = new cWNDManager();
	}
	//return pInstance
	return cWNDManager::pInstance;
}

//boolean createWND function with the parameters width, heign and bpp passing through it, all of them integers in value.
bool cWNDManager::createWND(int width, int height, int bpp)
{
	DWORD      dwExStyle;       // Window Extended Style
	DWORD      dwStyle;         // Window Style

	m_windowRect.left = (long)0; // Set Left Value To 0
	m_windowRect.right = (long)width; // Set Right Value To Requested Width
	m_windowRect.top = (long)0;  // Set Top Value To 0
	m_windowRect.bottom = (long)height;   // Set Bottom Value To Requested Height

	// fill out the window class structure
	m_windowClass.cbSize = sizeof(WNDCLASSEX);
	m_windowClass.style = CS_HREDRAW | CS_VREDRAW;
	m_windowClass.lpfnWndProc = (WNDPROC)cWNDManager::WndProc; //We set our static method as the event handler (WNDPROC)
	m_windowClass.cbClsExtra = 0;
	m_windowClass.cbWndExtra = 0;
	m_windowClass.hInstance = m_hinstance;
	m_windowClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);  // default icon
	m_windowClass.hCursor = LoadCursor(NULL, IDC_ARROW);      // default arrow
	m_windowClass.hbrBackground = NULL;                             // don't need background
	m_windowClass.lpszMenuName = NULL;                             // no menu
	m_windowClass.lpszClassName = "winOGL";
	m_windowClass.hIconSm = LoadIcon(NULL, IDI_WINLOGO);      // windows logo small icon

	// register the windows class
	if (!RegisterClassEx(&m_windowClass))
	{
		return false;
	}

	dwExStyle = WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;   // Window Extended Style
	dwStyle = WS_OVERLAPPEDWINDOW;                    // Windows Style

	AdjustWindowRectEx(&m_windowRect, dwStyle, false, dwExStyle);     // Adjust Window To True Requested Size

	// class registered, so now create our window
	m_hwnd = CreateWindowEx(NULL,                                 // extended style
		"winOGL",                          // class name
		WINDOW_TITLE,      // app name
		WS_OVERLAPPEDWINDOW,	// the window style
		CW_USEDEFAULT, // the starting x coordinate
		CW_USEDEFAULT, // the starting y coordinate
		m_windowRect.right - m_windowRect.left, // the pixel width of the window
		m_windowRect.bottom - m_windowRect.top, // the pixel height of the window
		NULL, // the parent window; NULL for desktop
		NULL, // the menu for the application; NULL for none
		m_hinstance, // the handle to the application instance
		this); // no values passed to the window

	// check if window creation failed (hwnd would equal NULL)
	if (!m_hwnd)
		return 0;

	m_hdc = GetDC(m_hwnd);

	ShowWindow(m_hwnd, SW_SHOW);          // display the window
	UpdateWindow(m_hwnd);                 // update the window

	m_lastTime = GetTickCount() / 1000.0f; //Initialize the time
	return true;
}


void cWNDManager::destroyWND()//function destroy window
{
	ShowCursor(true);                       // Show Mouse Pointer
}

void cWNDManager::attachOGLWnd(windowOGL* OGLWindow)//function attachOGLWnd 
{
	//sets private variable to the instance of windowOGL that was passed through the parameters
	m_winOGL = OGLWindow;
}

void cWNDManager::attachInputMgr(cInputMgr* inputMgr)//function attachInputMgr
{
	//sets private variable to the instance of cInputMgr that was passed through the parameter.
	m_InputMgr = inputMgr;
}

bool cWNDManager::isWNDRunning()//boolean function isWNDRunning
{
	//returns the current value of the private variable m_isRunning
	return m_isRunning;
}
bool cWNDManager::camera(){  //bool camera function
	//returns current value of the private variable m_camera
	return m_camera;
	
}
bool cWNDManager::soundtrack(){ //bool soundtrack function
	//returns the current value of the private variable m_sound
	return m_soundtrack;
}
HWND cWNDManager::getWNDHandle()   // Return window handle.
{
	return m_hwnd;
}

HDC cWNDManager::getWNDDC()//returns WDDC
{
	return m_hdc;
}

void cWNDManager::processWNDEvents()//function processWDEvents
{
	MSG msg; //new MSG called msg, creates a message

	//While there are messages in the queue, store them in msg
	while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
	{
		//Process the messages one-by-one
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
}

void cWNDManager::setupPixelFormat(void)//function set up pixel format
{
	int pixelFormat;

	PIXELFORMATDESCRIPTOR pfd =
	{
		sizeof(PIXELFORMATDESCRIPTOR),  // size
		1,                          // version
		PFD_SUPPORT_OPENGL |        // OpenGL window
		PFD_DRAW_TO_WINDOW |        // render to window
		PFD_DOUBLEBUFFER,           // support double-buffering
		PFD_TYPE_RGBA,              // color type
		32,                         // prefered color depth
		0, 0, 0, 0, 0, 0,           // color bits (ignored)
		0,                          // no alpha buffer
		0,                          // alpha bits (ignored)
		0,                          // no accumulation buffer
		0, 0, 0, 0,                 // accum bits (ignored)
		16,                         // depth buffer
		0,                          // no stencil buffer
		0,                          // no auxiliary buffers
		PFD_MAIN_PLANE,             // main layer
		0,                          // reserved
		0, 0, 0,                    // no layer, visible, damage masks
	};

	pixelFormat = ChoosePixelFormat(m_hdc, &pfd);
	SetPixelFormat(m_hdc, pixelFormat, &pfd);
}

LRESULT CALLBACK cWNDManager::WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	cWNDManager* theWindow = NULL;
	switch (uMsg)
	{
	case WM_CREATE:         // window creation
	{
		pInstance->m_hdc = GetDC(hWnd);
		pInstance->setupPixelFormat();

		//Set the version that we want, in this case 3.0
		int attribs[] = {
			WGL_CONTEXT_MAJOR_VERSION_ARB, 3,
			WGL_CONTEXT_MINOR_VERSION_ARB, 0,
			0 }; //zero indicates the end of the array

		//Create temporary context so we can get a pointer to the function
		HGLRC tmpContext = wglCreateContext(pInstance->m_hdc);
		//Make it current
		wglMakeCurrent(pInstance->m_hdc, tmpContext);

		//Get the function pointer
		wglCreateContextAttribsARB = (PFNWGLCREATECONTEXTATTRIBSARBPROC)wglGetProcAddress("wglCreateContextAttribsARB");

		//If this is NULL then OpenGL 3.0 is not supported
		if (!wglCreateContextAttribsARB)
		{
			std::cerr << "OpenGL 3.0 is not supported, falling back to GL 2.1" << std::endl;
			pInstance->m_hglrc = tmpContext;
		}
		else
		{
			// Create an OpenGL 3.0 context using the new function
			pInstance->m_hglrc = wglCreateContextAttribsARB(pInstance->m_hdc, 0, attribs);
			//Delete the temporary context
			wglDeleteContext(tmpContext);
		}

		//Make the GL3 context current
		wglMakeCurrent(pInstance->m_hdc, pInstance->m_hglrc);

		pInstance->m_isRunning = true; //Mark our window as running
	}
		break;
	case WM_DESTROY: // window destroy
	case WM_CLOSE: // windows is closing
		wglMakeCurrent(pInstance->m_hdc, NULL);
		wglDeleteContext(pInstance->m_hglrc);
		pInstance->m_isRunning = false; //Stop the main loop
		PostQuitMessage(0); //Send a WM_QUIT message
		return 0;
		break;
	case WM_SIZE:
	{
		int height = HIWORD(lParam);        // retrieve width and height
		int width = LOWORD(lParam);
		pInstance->getAttachedWND()->onResize(width, height); //Call the example's resize method
	}
		break;
	case WM_KEYDOWN:
	{
		if (wParam == VK_F1) //If the F1 key was pressed
		{
			OutputDebugString("ffffffffffffffffffffffffffffffffffff"); //place message in debug log
			pInstance->m_camera = true; //set private variable to true
		}
		if (wParam == VK_F2) //If the F2 key was pressed
		{
			OutputDebugString("aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa");//place message in debug log
			pInstance->m_camera = false; //set private variable to false
		}
		if (wParam == VK_F3) //If the F3 key was pressed
		{
			OutputDebugString("Duel of the Fates"); //place message in debug log
			if (pInstance->m_soundtrack == false){ //if private variable's current value is false
                        pInstance->m_soundtrack = true; //set it to tru
			}
			
			
		}
		if (wParam == VK_F4) //If the F4 key was pressed
		{
			OutputDebugString("sound switch "); //place message in the debug log
			pInstance->m_soundtrack = false; //set the pinstance of soundtrack private variabel to false
			if (pInstance->m_soundtrack == true){ 
						pInstance->m_soundtrack = false;
			}

		}
		if (wParam == VK_ESCAPE) //If the escape key was pressed
		{
			OutputDebugString("eeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeee");//place messgae in the debug log
			DestroyWindow(pInstance->m_hwnd); //Send a WM_DESTROY message
		}
		

		pInstance->m_InputMgr->keyDown(wParam); //passes the current key down through the inputmanager private variable iof the pInstance
		return 0;
	}

		break;
	default:
		break;
	}

	return DefWindowProc(hWnd, uMsg, wParam, lParam);//returns the window processes
}

windowOGL*  cWNDManager::getAttachedWND()//function get attached window
{
	return m_winOGL; //returns private variabel m_winOGL
}


float cWNDManager::getElapsedSeconds()//function getElapsed Seconds
{
	float currentTime = float(GetTickCount()) / 1000.0f; //current time variabel equals the numbe of ticks passed divided by 1000
	float seconds = float(currentTime - m_lastTime); //seconds equals the current time minus the private variabel last time
	m_lastTime = currentTime;//sets a new last time value to the still in use currentTime value.
	return seconds; //returns the value of seconds
}
