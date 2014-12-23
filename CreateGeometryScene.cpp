#include "CreateGeometryScene.h"

void CreateGeometryScene::CreateMap()
{
	if(!stateForImage){
		mImage->LoadImageDefault ();
		stateForImage = true;
	}
	else
		mImage->LoadSelectedImage ();
    HDC hdcSrc = CreateCompatibleDC(NULL);
    HDC hdcDst = CreateCompatibleDC(NULL);
    int u = mImage->getWidthImage();
	int v = mImage->getHeightImage();

	IndicesCount= (u-1)*(v-1)*6;
    hmap = new float*[u];
	lpPixels = new COLORREF [u*v];
	GetDIBits( hdcSrc , mImage->gethBitmap() , 0 , v , lpPixels , &(mImage->getBmpInfo()) , DIB_RGB_COLORS );
 
	for (int count = 0; count < u; count++)
	{
        hmap[count] = new float [v];
	}

    for (int i = 0; i < u; i++) 
	{
        for (int j = 0; j < v; j++) 
		{
			int pos = lpPixels[ (i*v) + j];
			hmap[i][j] = ((float)(( GetBValue(pos) + GetGValue(pos) + GetRValue(pos) ) / 3.0f) / 255.0f)/5;
        }
    }
}

void CreateGeometryScene::GenerateSurface()
{
 
	this->CreateMap();
    int u = mImage->getWidthImage();
	int v = mImage->getHeightImage();
	vertices = new VertexStruct(u,v);

	unsigned int* indices = new unsigned int[IndicesCount];

	for (int i = 0; i < u; i++)
	for (int j = 0; j < v; j++)
	{
		float x=(float)i/(float)u - 0.5f;
		float z=(float)j/(float)v - 0.5f;
		vertices->pos[j*u+i]=glm::vec3(x,hmap[i][j],z) * 7.5f;
		vertices->normal[j*u+i]=glm::vec3(0,1,0);
		vertices->tex[j*u+i]=glm::vec2(x , 1.0f - ((z * (FLOAT)u / (FLOAT)v) ));
	}

	for (int i=0; i<(u-1); i++)
		for (int j=0; j<(v-1); j++)
		{
			unsigned int indexa=j*(u-1)+i;
			unsigned int indexb=j*u+i;
			indices[indexa*6+0]=indexb;
			indices[indexa*6+1]=indexb+1+u;
			indices[indexa*6+2]=indexb+1;

			indices[indexa*6+3]=indexb;
			indices[indexa*6+4]=indexb+u;
			indices[indexa*6+5]=indexb+u+1;
		}

   int verticesCount=u*v;
   int indicesCount=IndicesCount;

   glDeleteBuffers(4, uiVBO);
   glDeleteVertexArrays(2, uiVAO);
   glGenVertexArrays(2, uiVAO); 
   glGenBuffers(4, uiVBO);		

   glBindVertexArray(uiVAO[0]); 
   glBindBufferARB(GL_ARRAY_BUFFER, uiVBO[0]); 
   glBufferDataARB(GL_ARRAY_BUFFER, 3*verticesCount*sizeof(float), vertices->pos, GL_STATIC_DRAW); 
   glEnableVertexAttribArrayARB(0); 
   glVertexAttribPointerARB(0, 3, GL_FLOAT, GL_FALSE, 0, 0); 

   glBindBufferARB(GL_ARRAY_BUFFER, uiVBO[1]); 
   glBufferDataARB(GL_ARRAY_BUFFER, 3*verticesCount*sizeof(float), vertices->normal, GL_STATIC_DRAW); 
   glEnableVertexAttribArrayARB(1); 
   glVertexAttribPointerARB(1, 3, GL_FLOAT, GL_FALSE, 0, 0); 

   glBindBufferARB(GL_ARRAY_BUFFER, uiVBO[2]); 
   glBufferDataARB(GL_ARRAY_BUFFER, 2*verticesCount*sizeof(float), vertices->tex, GL_STATIC_DRAW); 
   glEnableVertexAttribArrayARB(2); 
   glVertexAttribPointerARB(2, 2, GL_FLOAT, GL_FALSE, 0, 0); 

   glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER, uiVBO[3]); 
   glBufferDataARB(GL_ELEMENT_ARRAY_BUFFER, indicesCount*sizeof(unsigned int), indices, GL_STATIC_DRAW); 
}

void CreateGeometryScene::InitGeometryScene() 
{ 
   this->GenerateSurface();

   Tex.loadTexture2D("texdiag.jpg", true);
   Tex.setFiltering(TEXTURE_FILTER_MAG_BILINEAR, TEXTURE_FILTER_MIN_BILINEAR_MIPMAP);

   shVertex.loadShader("data\\shaders\\shader.vert", GL_VERTEX_SHADER); 
   shFragment.loadShader("data\\shaders\\shader.frag", GL_FRAGMENT_SHADER); 

   spMain.createProgram(); 
   spMain.addShaderToProgram(&shVertex); 
   spMain.addShaderToProgram(&shFragment); 
   spMain.linkProgram(); 
   spMain.useProgram(); 

   revolveObject = new RotateImage();

   wglSwapIntervalEXT(1);
   glEnable(GL_DEPTH_TEST);
   glClearDepth(1.0f);
} 

CShader CreateGeometryScene::getShVertex(){
	return this->shVertex;
}
CShader CreateGeometryScene::getShFragment(){
	return this->shFragment;
}


CShaderProgram CreateGeometryScene::getSpMain(){
	return this->spMain;
}
CTexture CreateGeometryScene::getTex(){
	return this->Tex;
}
HWND CreateGeometryScene::getHwndParent(){
	return this->_hwndParent;
}
void CreateGeometryScene::setHwndParent(HWND aHwndParent){
	this->_hwndParent = aHwndParent;
}

int CreateGeometryScene::getIndicesCount(){
	return this->IndicesCount;
}

UINT CreateGeometryScene::getUiVAO(){
	return this->uiVAO[0];
}



CreateGeometryScene::CreateGeometryScene(HWND hwndDlg):
	vertices(NULL), lpPixels(NULL),hmap(NULL),IndicesCount(0),
	_hwndParent(hwndDlg)
{
	mImage = new ImageData(hwndDlg);
	revolveObject = new RotateImage();

}

CreateGeometryScene::CreateGeometryScene(void)
{
}

CreateGeometryScene::~CreateGeometryScene(void)
{
}

bool CreateGeometryScene::stateForImage =false;
