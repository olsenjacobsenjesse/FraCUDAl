#include "FractalRender.h"

#define Q_KEY 24
#define ESCAPE_KEY 9

FractalRender::FractalRender(int width, int height)
{
	this->window = new DisplayScreen(width, height);
	this->display = this->window->getDisplay();
	this->quit = false;
}

FractalRender::~FractalRender()
{
	delete window;
}

void FractalRender::render()
{
	do
	{
		if(this->getEvent())
		{
			this->handleEvent();
		}
	} while (!quit);
}

bool FractalRender::getEvent()
{
	if(XPending(this->display))
	{
		XNextEvent(this->display, &event);
		return true;
	}
	return false;
}

void FractalRender::handleEvent()
{

	printf("Key pressed: %d\n",event.xkey.keycode);
	if(event.type == KeyPress && (event.xkey.keycode == Q_KEY || event.xkey.keycode == ESCAPE_KEY))
	{
		printf("Key pressed: %d\n",event.xkey.keycode);
		quit = true;
	}
}
