#include "Renderer.h"


void Renderer::Render()
{
	HDC hDC = GetDC(mScene->getHwndParent());
	
	glClearColor(0.9f, 0.9f, 0.5f, 0.5f);
	glClearDepth(1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glm::vec3   Eye( 5.0f, 3.0f, 5.0f );
	glm::mat4	mWorld;
	glm::mat4	mView;
	glm::mat4	mProjection;


	mWorld =  glm::translate(0.0f, 0.0f, 0.0f);
	mWorld = mWorld * glm::rotate(RotateImage::mOrbitX, 0.0f, 1.0f, 0.0f); 
	mWorld = mWorld * glm::rotate(RotateImage::mOrbitY, 1.0f, 0.0f, 0.0f);
	mView=		glm::lookAt(Eye,glm::vec3(0,0,1),glm::vec3(0.0f,1.0f,0.0f));
	mProjection=glm::perspectiveFov(90.0f,533.0f,400.0f,0.001f,1000.0f);

	int iWorld=	glGetUniformLocation(mScene->getSpMain().getProgramID(),"mWorld");
	int iView=	glGetUniformLocation(mScene->getSpMain().getProgramID(),"mView");
	int iProjection=	glGetUniformLocation(mScene->getSpMain().getProgramID(),"mProjection");

	glUniformMatrix4fv(iWorld,1,GL_FALSE,glm::value_ptr(mWorld));
	glUniformMatrix4fv(iView,1,GL_FALSE,glm::value_ptr(mView));
	glUniformMatrix4fv(iProjection,1,GL_FALSE,glm::value_ptr(mProjection));

	glm::vec3 LightPos[1];
	glm::vec3 LightColor[1];
	LightPos[0]=glm::vec3(-1.0f,1.0f,1.0f);
	LightColor[0]=glm::vec3(0,1,1);
	int iLightPos=	glGetUniformLocation(mScene->getSpMain().getProgramID(),"vLightPos");
	int iLightColor=glGetUniformLocation(mScene->getSpMain().getProgramID(),"vLightColor");

	glUniform3fv(iLightPos,1,  (GLfloat*)LightPos);
	glUniform3fv(iLightColor,1,(GLfloat*)LightColor);

	glBindVertexArray(mScene->getUiVAO());
	glUniformMatrix4fv(iWorld,1,GL_FALSE,glm::value_ptr(mWorld));

	glDrawElements(GL_TRIANGLES,mScene->getIndicesCount(),GL_UNSIGNED_INT,0);
	SwapBuffers(hDC);
	DeleteObject(hDC);
}

void Renderer:: CleanupContext()
{
	mScene->getTex().releaseTexture();
	mScene->getSpMain().deleteProgram();
	mScene->getShVertex().deleteShader();
	mScene->getShFragment().deleteShader();

	HDC hDC = GetDC(mScene->getHwndParent());
	wglMakeCurrent(NULL, NULL);
	ReleaseDC(mScene->getHwndParent(), hDC);

	mScene->setHwndParent(NULL);
}

CreateGeometryScene* Renderer::getScene(){
	return this->mScene;
}

Renderer::Renderer(HWND hwnd)
{
	mHwnd = hwnd;
	mScene = new CreateGeometryScene(hwnd);
}


Renderer::~Renderer(void)
{
}
