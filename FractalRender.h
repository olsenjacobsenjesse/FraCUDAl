#include "DisplayScreen.h"

class FractalRender
{
	private:
		DisplayScreen * window;
		Display * display;
		XEvent event;
		int width, height;
		bool buttonPressed;
		bool quit;

	public:
		FractalRender(int,int);
		~FractalRender();
		void render();
		bool getEvent();
		void handleEvent();
		void updateDisplay();
		void setColor(ulong);
		void drawPixel(int,int);
		void drawMandelbrot();
};
