#pragma once
#include "ImageData.h"
#include "VertexStruct.h"
#include "texture.h"
#include "shaders.h"
#include "GL/glew.h"
#include "GL/wglew.h"
#include "RotateImage.h"
#include "FreeImage/FreeImage.h"
class CreateGeometryScene
{
public:
	void CreateMap();
	void GenerateSurface();
	void InitGeometryScene();
	void setHwnd(HWND hwnd);
	CShader getShVertex();
	CShader getShFragment();
	CShaderProgram getSpMain();
	CTexture getTex();
	HWND getHwndParent();
	void setHwndParent(HWND aHwndParent);
	int getIndicesCount();
	UINT getUiVAO();
	CreateGeometryScene::CreateGeometryScene(HWND aHwndDlg);
	CreateGeometryScene::CreateGeometryScene();
	~CreateGeometryScene();

private:
	ImageData* mImage;
	VertexStruct* vertices;
	COLORREF * lpPixels;
	static bool stateForImage;
	float**hmap ;
	int IndicesCount;
	CShader shVertex, shFragment; 
	CShaderProgram spMain;
	CTexture Tex;
	RotateImage *revolveObject;
	HWND _hwndParent;
	UINT uiVBO[4]; 
	UINT uiVAO[1];



};

