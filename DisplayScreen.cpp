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
	XSelectInput(this->display, this->window, KeyPressMask | ExposureMask | ButtonPressMask | ButtonReleaseMask);
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

void DisplayScreen::updateDisplay()
{
	//XClearWindow(this->display, this->window);
	//create variables for storing return values from XGetGeometry
	Window root_wind;
	int x_return, y_return;
	uint width_return, height_return, border_width_return, depth_return;
	XGetGeometry(this->display, this->window, &root_wind, &x_return, &y_return,
			     &width_return, &height_return, &border_width_return, &depth_return);

	//create event to send so the display can update
	XEvent exposure_event;
	exposure_event.xexpose.type= Expose;
	exposure_event.xexpose.display = this->display;
	exposure_event.xexpose.window = this->window;
	exposure_event.xexpose.x = x_return;
	exposure_event.xexpose.y = y_return;
	exposure_event.xexpose.width = width_return;
	exposure_event.xexpose.height = height_return;
	exposure_event.xexpose.count = 0;

	XSendEvent(this->display, this->window, false, ExposureMask, &exposure_event);
}

void DisplayScreen::setColor(ulong color)
{
	XSetForeground(this->display, DefaultGC(this->display, this->screen), color);
}

void DisplayScreen::drawPixel(int xpos, int ypos)
{
	XDrawPoint(this->display, this->window, DefaultGC(this->display, this->screen), xpos, ypos);
}
