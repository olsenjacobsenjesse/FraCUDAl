#include <iostream>
#include <unistd.h>
#include <cstdlib>
#include "WindowFrame.h"

/*
	Jesse Olsen-Jacobsen
	Mandelbrot Renderer

	Program utilizes Xlib to create windows to render the Mandelbrot set (and 
	perhaps others in the future) and will eventually utilize Nvidia's CUDA to 
	render the mandelbrot set and allow for easy exploration of the fractal(s) 
 */

//This will all be moved into more appropriate files later on

int main(int argc, char ** argv)
{
	// Set resolution of the window
	int resx = 500;
	int resy = 500;
	// Assign the WM_CLASS name for window managers to utilize
	char window_name[19] = "MandelbrotRenderer";

	//if resolution was passed in via arguments, use resolution values as (x,y)
	if(argc > 2){
		resx = atoi(argv[1]);
		resy = atoi(argv[2]);
	} 
	
	WindowFrame *fractal = new WindowFrame(window_name,resx,resy);
	fractal->render();

	printf("Exiting window\n");
	delete fractal;
	
	return 0;
}
