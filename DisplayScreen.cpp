#include "DisplayScreen.h"

DisplayScreen::DisplayScreen(char * name, int width, int height)
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
	
	//Assigning WM_CLASS for compatability with window managers
	wm_class = XAllocClassHint();
	int class_length = strnlen(name,63);
	wm_class->res_class = (char*)malloc(class_length + 1);
	strncpy(wm_class->res_class, name, class_length);
	wm_class->res_class[class_length] = '\0';
	wm_class->res_name = (char*)malloc(class_length + 1);
	strncpy(wm_class->res_name, name, class_length);
	wm_class->res_name[class_length] = '\0';
	XSetClassHint(this->display, this->window, wm_class);

	//Capture incoming keyboard events
	XSelectInput(this->display, this->window, KeyPressMask | ExposureMask | ButtonPressMask | ButtonReleaseMask);
	//Map window to display
	XMapWindow(this->display, this->window);
}

DisplayScreen::~DisplayScreen()
{
	XFree(wm_class);
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

//Changes the WM_NAME variable, updating the title bar.
void DisplayScreen::SetWMName(char * new_window_name)
{
	//Get size of the new name, up to 128 characters
	int nameSize = strnlen(new_window_name,128);
	
	//Create XTextProperty struct and fill it in
	XTextProperty textProperty;
	textProperty.value = (unsigned char*)malloc(nameSize + 1);
	memcpy(textProperty.value, new_window_name, nameSize); //using memcpy to convert from char to unsigned char
	textProperty.value[nameSize] = '\0'; //ensure last byte is null-terminated
	textProperty.format = 8; //8-bit encoding
	textProperty.encoding = XA_WM_NAME; //WM_NAME atom
	textProperty.nitems = (ulong)nameSize; //size of the array
	XSetWMName(this->display,this->window, &textProperty); //Set WM Name
}
