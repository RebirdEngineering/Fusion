#include <gr/dx11/DX11_createContext.h>
#include <gr/dx11/DX11_Context.h>

namespace gr
{
	Context* createContext(int w, int h, Context::OrientationType orientation, HWND hwnd)
	{
		return new DX11_Context(hwnd, orientation);
	}

}