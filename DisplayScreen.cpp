#include "DisplayScreen.h"

DisplayScreen::DisplayScreen(int width, int height)
{
	//Start new display for the window
	this->display = XOpenDisplay(NULL);
	//check if it succeeded
	if (!this->display){
		//throw exception if failed
		throw std::runtime_error("Failed to open the display\n");
	}
	
	//set up window to work with
	this->screen = DefaultScreen(this->display);
	this->window = XCreateSimpleWindow(this->display, RootWindow(this->display, this->screen), 0, 0, width, height, 1, BlackPixel(this->display, this->screen), WhitePixel(this->display, this->screen));

	//Capture incoming keyboard events
	XSelectInput(this->display, this->window, KeyPressMask);
	//Map window to display
	XMapWindow(this->display, this->window);
}

DisplayScreen::~DisplayScreen()
{
	XCloseDisplay(this->display);
}

Display * DisplayScreen::getDisplay()
{
	return this->display;
}
