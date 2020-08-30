// http://github.com/Amos-Tibaldi -> svid  "simple video acquisition program for windows X using DirectShow" 20200830, GPLv3.

#include <Windows.h>
#include <iostream>
#include <d3d9.h>
#include "CapDShow.h"
#include "DXWindow.h"
using namespace std;
using namespace svid;
bool g_app_done = false;

int main()
{
	CVIn cap(0);
	DXWindow* pw = new DXWindow((char*)"TEST", cap.getX(0), cap.getY(0), true);
	LDADXWINDOWHANDLE h = (LDADXWINDOWHANDLE)pw;
	unsigned char* pointer = (unsigned char*)malloc(4 * cap.getX(0) * cap.getY(0));

	while (!g_app_done)
	{
		cap.grabFrame();
		cap.retrieveFrame(0, pointer);

		LDADXWindowDisplayBuffer(h, pointer);
		
		LDACallWhenIdle();
		SwitchToThread();
		Sleep(1);
	}
	free(pointer);
	return 0;
}

