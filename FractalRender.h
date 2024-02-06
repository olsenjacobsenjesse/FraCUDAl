#include "DisplayScreen.h"

class FractalRender
{
	private:
		DisplayScreen * window;
		Display * display;
		XEvent event;
		bool quit;

	public:
		FractalRender(int,int);
		~FractalRender();
		void render();
		bool getEvent();
		void handleEvent();
};
