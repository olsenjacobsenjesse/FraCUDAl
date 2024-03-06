#include "DisplayScreen.h"

class WindowFrame
{
	private:
		DisplayScreen * window;
		Display * display;
		XEvent event;
		int width, height;
		bool buttonPressed;
		bool quit;

	public:
		WindowFrame(char*,int,int);
		~WindowFrame();
		void render();
		bool getEvent();
		void handleEvent();
		void updateDisplay();
		void setColor(ulong);
		void drawPixel(int,int);
		void drawMandelbrot();
};
