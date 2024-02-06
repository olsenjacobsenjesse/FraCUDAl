#include <X11/Xlib.h>
#include <cstdio>
#include <stdexcept>

class DisplayScreen
{
	private:
		Display * display;
		int screen;
		Window window;
	public:
		DisplayScreen(int width, int height);
		~DisplayScreen();
		Display * getDisplay(void);
};
