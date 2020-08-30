

namespace svid
{



#define DXWINDOW_BUFFER_SIZE 4

	LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);

	typedef struct {
		DWORD* Pixels[DXWINDOW_BUFFER_SIZE];
		CRITICAL_SECTION mutex;
		CONDITION_VARIABLE cond_not_full, cond_not_empty;
		int head, tail, size;
	} pixelbuffer_t;

	class DXWindow {

	public:
		DXWindow(char* theWindowTitle, int ww, int hh, bool WaitVSync);
		~DXWindow();
		LRESULT CALLBACK MyMsgProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
		void SetRGBAtXY(int r, int g, int b, int x, int y);
		void DisplayBuffer(unsigned char* bfr);

	private:
		static DWORD run(LPVOID arg);
		void CalculateExactRect(int cx, int cy, RECT& rect);
		void ResizeWindow(int width, int height);
		void PutFrontBufferOntoScreen();
		void CopyFrameToFrontBuffer();
		void ReduceWindowSize();
		void IncreaseWindowSize();

		int nCmdShow;
		HINSTANCE instance;
		WNDCLASS window_class;
		bool mycond;
		char class_name[200];
		bool is_app_fullscreen;
		int window_width;
		int window_height;
		int buffer_width;
		int buffer_height;
		float buffer_ratio;
		DWORD style;
		HWND p_window;
		RECT window_rect;

		pixelbuffer_t PixelBuffer;

		D3DLOCKED_RECT lr;
		IDirect3D9* g_D3D;
		D3DFORMAT format;
		D3DPRESENT_PARAMETERS pp;
		IDirect3DDevice9* p_device;
		HRESULT hr;
		LPDIRECT3DSURFACE9 FrontBuffer;
		LPDIRECT3DSURFACE9 BackBuffer;
		HRESULT Result;
	};

}

typedef void* LDADXWINDOWHANDLE;

#define LDASetARGBXYOfBuffer(buffer, bufxsize, x, y, r, g, b) \
{ \
	int offset = 4 * ((x) + (y) * (bufxsize)); \
	buffer[offset] = b; \
	buffer[offset+1] = g; \
	buffer[offset+2] = r; \
	buffer[offset+3] = 0; \
}

#define LDAGetRGBXYOfBuffer(buffer, bufxsize, x, y, r, g, b) \
{ \
	int offset = 3 * ((x) + (y) * (bufxsize)); \
	r = buffer[offset]; \
	g = buffer[offset+1]; \
	b = buffer[offset+2]; \
}

void LDADXWindowDisplayBuffer(LDADXWINDOWHANDLE win, unsigned char* bfr);


void LDACallWhenIdle();