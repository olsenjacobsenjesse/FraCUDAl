#include <iostream>
#include <unistd.h>
#include "FractalRender.h"

int main()
{
	FractalRender *fractal = new FractalRender(100,100);
	fractal->render();

	printf("Exiting window\n");
	delete fractal;
	
	return 0;
}
