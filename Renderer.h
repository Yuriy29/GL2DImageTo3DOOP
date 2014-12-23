#pragma once
#include "stdafx.h"
#include "FreeImage/FreeImage.h"
#include "glm/glm.hpp"
#include "glm/gtx/transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "GL/glew.h"
#include "GL/wglew.h"
#include "CreateGeometryScene.h"
#include "RotateImage.h"
class Renderer
{
public:
	void Render();
	void CleanupContext();
	CreateGeometryScene* getScene();
	Renderer(HWND aHwnd);
	~Renderer(void);
private:
	CreateGeometryScene* mScene;
	HWND mHwnd;
};

