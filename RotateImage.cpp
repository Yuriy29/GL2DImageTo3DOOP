#include "RotateImage.h"

 void RotateImage:: mouseMove(int x, int y) { 	
	 mOrbitX+=x;
	 mOrbitY+=y;

}

RotateImage::RotateImage(void){

}


RotateImage::~RotateImage(void)
{
}

FLOAT RotateImage::mOrbitX =0;
FLOAT RotateImage::mOrbitY=0;
