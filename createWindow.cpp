#include <windows.h>

//Store the name of the window class
const char className[] = "windowClass";

//The Window Procedure
	//This is where the messages are received from the message loop
LRESULT CALLBACK WndProc(HWND windowHandler, UINT msg, WPARAM wParam, LPARAM lParam)		
{
	switch(msg)
	{
		case WM_CLOSE:															//In the event that its the close button (or presses Alt+f4), destroy the window
			DestroyWindow(windowHandler);										//The destroy message is sent to the message loop and brought back to the switch statement
		break;
		case WM_DESTROY:
			PostQuitMessage(0);													//Sends WM_Quit (0) to message loop
		break;
		default:
			return DefWindowProc(windowHandler, msg, wParam, lParam);
	}
	return 0;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR lpCmdLine, int nCmdShow)
{
	WNDCLASSEX windowClass;
	HWND windowHandler;
	MSG Msg;

	//Registering the Window Class
	windowClass.cbSize        = sizeof(WNDCLASSEX);						//The size of the structure. 
	windowClass.style         = 0;										//Class Styles (CS_*), not to be confused with Window Styles (WS_*) This can usually be set to 0. 
	windowClass.lpfnWndProc   = WndProc;								//Pointer to the window procedure for this window class.
	windowClass.cbClsExtra    = 0;										//Amount of extra data allocated for this class in memory. Usually 0. 
	windowClass.cbWndExtra    = 0;										//Amount of extra data allocated in memory per window of this type. Usually 0. 
	windowClass.hInstance     = hInstance;								//Handle to application instance (that we got in the first parameter of WinMain()). 
	windowClass.hIcon         = LoadIcon(NULL, IDI_APPLICATION);		//Large (usually 32x32) icon shown when the user presses Alt+Tab. 
	windowClass.hCursor       = LoadCursor(NULL, IDC_ARROW);			//Cursor that will be displayed over our window. 
	windowClass.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);				//Background Brush to set the color of our window. 
	windowClass.lpszMenuName  = NULL;									//Name of a menu resource to use for the windows with this class. 
	windowClass.lpszClassName = className;								//Name to identify the class with. 
	windowClass.hIconSm       = LoadIcon(NULL, IDI_APPLICATION);		//Small (usually 16x16) icon to show in the taskbar and in the top left corner of the window. 

	//Check return values for error
	if(!RegisterClassEx(&windowClass))
	{
		MessageBox(NULL, "Window Registration Failed!", "Error!",
			MB_ICONEXCLAMATION | MB_OK);
		return 0;
    }

	//Creating the Window
	windowHandler = CreateWindowEx(
		WS_EX_CLIENTEDGE,									//Dictates the extended window style, this is going to have a sunken border. see: https://docs.microsoft.com/en-us/windows/desktop/winmsg/extended-window-styles
		className,											//The class name stored earlier
		"A simple window program",							//The title of the window
		WS_OVERLAPPEDWINDOW,								//Dictates the window style. See: https://docs.microsoft.com/en-us/windows/desktop/winmsg/window-styles
		CW_USEDEFAULT, CW_USEDEFAULT, 240, 120,				//The starting coordinates of the top left, and the width and height of the window
		NULL, NULL, hInstance, NULL);						//Parent Window, Menu Handle, application instance, and window creation data

	//Check return values for error 
	if(windowHandler == NULL)
	{
		MessageBox(NULL, "Window Creation Failed!", "Error!",
			MB_ICONEXCLAMATION | MB_OK);
		return 0;
	}

	//Show and update the window
	ShowWindow(windowHandler, nCmdShow);
	UpdateWindow(windowHandler);

	//The Message Loop
	while(GetMessage(&Msg, NULL, 0, 0) > 0)					//Any activity from the user is a message that the window received in the GetMessage queue
	{
		TranslateMessage(&Msg);								//Processes the message
		DispatchMessage(&Msg);								//Sends the message to the window that the activity was in
	}
	return Msg.wParam;									
}