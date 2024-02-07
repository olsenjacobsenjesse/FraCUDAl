#include "FractalRender.h"

#define Q_KEY 24
#define ESCAPE_KEY 9

FractalRender::FractalRender(int width, int height)
{
	this->width = width;
	this->height = height;
	this->window = new DisplayScreen(this->width, this->height);
	this->display = this->window->getDisplay();
	this->buttonPressed = false;
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
	} while (!this->quit);
}

bool FractalRender::getEvent()
{
	if(XPending(this->display))
	{
		XNextEvent(this->display, &this->event);
		//printf("EVENT: \nevent.type = %d\nevent.button = %d\n",this->event.type,this->event.xbutton.button);
		return true;
	}
	return false;
}

void FractalRender::handleEvent()
{
	if((this->event.type == ButtonPress && this->event.xbutton.button == Button1 && this->buttonPressed == false) || (this->event.type == ButtonRelease && this->event.xbutton.button == Button1 && this->buttonPressed == true))
	{
		this->buttonPressed = !this->buttonPressed;
		printf("Calling drawMandelbrot()\n");
		drawMandelbrot();
		printf("Calling updateDisplay()\n");
		updateDisplay();
	}
	if(this->event.type == KeyPress && (this->event.xkey.keycode == Q_KEY || this->event.xkey.keycode == ESCAPE_KEY))
	{
		this->quit = true;
	}
}

void FractalRender::updateDisplay()
{
	this->window->updateDisplay();
}

void FractalRender::setColor(ulong color)
{
	this->window->setColor(color);
}

void FractalRender::drawPixel(int xpos, int ypos)
{
	this->window->drawPixel(xpos, ypos);
}

void FractalRender::drawMandelbrot()
{
	for(int j = 0; j < this->height; j++)
	{
		for(int i = 0; i < this->width; i++)
		{
			setColor(0xFF0000);
			drawPixel(i,j);
		}
	}
}
