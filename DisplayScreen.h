#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xatom.h>
#include <cstdio>
#include <stdexcept>
#include <string.h>

class DisplayScreen
{
	private:
		Display * display;
		int screen;
		Window window;
		XClassHint * wm_class;
	public:
		DisplayScreen(char * name, int width, int height);
		~DisplayScreen();
		Display * getDisplay(void);
		void updateDisplay(void);
		void setColor(ulong);
		void drawPixel(int,int);
		void SetWMName(char*);
};
