#pragma once
#include "stdafx.h"
class RotateImage
{
public:
	static FLOAT mOrbitX;
	static FLOAT mOrbitY;

public:
	void mouseMove(int x, int y);
	RotateImage(void);
	~RotateImage(void);
};

