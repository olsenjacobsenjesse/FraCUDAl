#include <iostream>
#include <unistd.h>
#include <cstdlib>
#include "FractalRender.h"

int main(int argc, char ** argv)
{
	int resx = 500;
	int resy = 500;

	//if resolution was passed in via arguments, use resolution values as (x,y)
	if(argc > 2){
		resx = atoi(argv[1]);
		resy = atoi(argv[2]);
	}
	FractalRender *fractal = new FractalRender(resx,resy);
	fractal->render();


	printf("Exiting window\n");
	delete fractal;
	
	return 0;
}
