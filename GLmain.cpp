#pragma once
#pragma comment (lib,"opengl32.lib")
#pragma comment (lib,"glew32.lib")
#pragma comment (lib,"glew32mx.lib")
#pragma comment (lib,"glew32mxs.lib")
#pragma comment (lib,"glew32s.lib")
#pragma comment (lib,"FreeImage.lib")

#include "GL/glew.h"
#include "GL/wglew.h"
#include <stdio.h>
#include "Resource.h"
#include "Renderer.h"
#include "RotateImage.h"


HINSTANCE               g_hInst = NULL;
HWND                    g_hWnd = NULL;
HGLRC					hRC = NULL;
WORD xPosDown, yPosDown, nSize;
WORD xPosMove, yPosMove;
bool mStartMes = false;
bool mMouseMove;
bool flag = false;



HRESULT InitWindow( HINSTANCE hInstance, int nCmdShow );
HRESULT InitCompatibleContext();
HRESULT InitContext();
LRESULT CALLBACK    WndProc( HWND, UINT, WPARAM, LPARAM );





int WINAPI wWinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow )
{
    UNREFERENCED_PARAMETER( hPrevInstance );
    UNREFERENCED_PARAMETER( lpCmdLine );

	Renderer *render = NULL;

    if( FAILED( InitWindow( hInstance, nCmdShow ) ) )
        return 0;

	if( FAILED( InitCompatibleContext() ) )
		return 0;

	if( FAILED( InitContext() ) )
    {
		render = new Renderer(g_hWnd);
        render->CleanupContext();
        return 0;
    }
	render = new Renderer(g_hWnd);
	render->getScene()->InitGeometryScene();
	

    MSG msg = {0};
    while( WM_QUIT != msg.message )
    {
		 if( PeekMessage( &msg, NULL, 0, 0, PM_REMOVE ) )
			{
				TranslateMessage( &msg );
				DispatchMessage( &msg );
			}
		  else
			{
				render->Render();
			}
    }

    render->CleanupContext();

    return ( int )msg.wParam;
}

void czCreateMenu(HWND hwnd)
{
	HMENU MainMenu = CreateMenu();
    HMENU hPopupMenu = CreatePopupMenu();
 
    AppendMenu(MainMenu, MF_STRING | MF_POPUP, (UINT)hPopupMenu, L"&Файл"); 
    {
        AppendMenu(hPopupMenu, MF_STRING, IDM_FILE_OP, L"Новый");
        AppendMenu(hPopupMenu, MF_STRING, 1000, L"Сохранить");
        AppendMenu(hPopupMenu, MF_STRING, 1000, L"Сохранить как...");
        AppendMenu(hPopupMenu, MF_STRING, 1000, L"Выход");
     }
  
     AppendMenu(MainMenu, MF_STRING | MF_POPUP, 0, L"&Настройки");
 
     SetMenu(hwnd, MainMenu);
}


HRESULT InitWindow( HINSTANCE hInstance, int nCmdShow )
{
    // Register class
    WNDCLASSEX wcex;
    wcex.cbSize = sizeof( WNDCLASSEX );
    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = 0; 
    wcex.hCursor = LoadCursor( NULL, IDC_ARROW );
    wcex.hbrBackground = ( HBRUSH )( COLOR_WINDOW  );
    wcex.lpszMenuName = NULL;
    wcex.lpszClassName = L"GLProject";
    wcex.hIconSm = 0; 
    if( !RegisterClassEx( &wcex ) )
        return E_FAIL;

    // Create window
    g_hInst = hInstance;
    RECT rc = { 0, 0, 1200, 1800 };
    AdjustWindowRect( &rc, WS_OVERLAPPEDWINDOW, FALSE );
    g_hWnd = CreateWindow(	L"GLProject",
							L"GLProgram",
							WS_OVERLAPPEDWINDOW,
      0, 0, DEFAULTWINDOWH + DEFAULTTOOLSW, DEFAULTWINDOWH, NULL, NULL, hInstance, NULL );
	czCreateMenu(g_hWnd);
    if( !g_hWnd )
        return E_FAIL;
    ShowWindow( g_hWnd, nCmdShow );
	mStartMes = true;

    return S_OK;
}


LRESULT CALLBACK WndProc( HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam )
{
    PAINTSTRUCT ps;
    HDC hdc;
	int wmId, wmEvent;
	RotateImage *rotate = new RotateImage();
    switch( message )
    {
        case WM_PAINT:
            hdc = BeginPaint( hWnd, &ps );
            EndPaint( hWnd, &ps );
            break;
		case WM_LBUTTONDOWN:
		{
		  // Сохраняем координаты курсора мыши
		  xPosDown   = LOWORD(lParam);
		  yPosDown   = HIWORD(lParam); 
		  mMouseMove = true;
        }

		case WM_MOUSEMOVE:
			{
				xPosMove   = LOWORD(lParam);
				yPosMove   = HIWORD(lParam);

			if(mMouseMove)
				rotate->mouseMove(xPosMove -xPosDown , yPosMove - yPosDown );
			xPosDown = xPosMove;
			yPosDown = yPosMove;
				break;
			}

		case WM_LBUTTONUP:
			mMouseMove = FALSE;
		break;

        case WM_DESTROY:
            PostQuitMessage( 0 );
            break;

		case WM_COMMAND:
		wmId    = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		switch (wmId)
		{
			case IDM_FILE_OP:
				flag =true;
				InitContext();
				CreateGeometryScene *scene = new CreateGeometryScene(g_hWnd);
				scene->InitGeometryScene();
				//InitGeometry() ;
				break;
		}

			break;

        default:
            return DefWindowProc( hWnd, message, wParam, lParam );
    }

    return 0;
}

LRESULT CALLBACK WndProc2( HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam )
{
    PAINTSTRUCT ps;
    HDC hdc;

    switch( message )
    {
        case WM_PAINT:
            hdc = BeginPaint( hWnd, &ps );
            EndPaint( hWnd, &ps );
            break;
	
        case WM_DESTROY:
            PostQuitMessage( 0 );
            break;

        default:
            return DefWindowProc( hWnd, message, wParam, lParam );
    }
    return 0;
}


HRESULT InitCompatibleContext()
{
	int iMajorVersion=0;
	int iMinorVersion=0;

	HDC hDC = GetDC(g_hWnd);
	PIXELFORMATDESCRIPTOR pfd;

	memset(&pfd, 0, sizeof(PIXELFORMATDESCRIPTOR));
	pfd.nSize		= sizeof(PIXELFORMATDESCRIPTOR);
	pfd.nVersion   = 1;
	pfd.dwFlags    = PFD_DOUBLEBUFFER | PFD_SUPPORT_OPENGL | PFD_DRAW_TO_WINDOW;
	pfd.iPixelType = PFD_TYPE_RGBA; 
	pfd.cColorBits = 32;		    
	pfd.cDepthBits = 24;            
	pfd.iLayerType = PFD_MAIN_PLANE;
 
	int iPixelFormat = ChoosePixelFormat(hDC, &pfd);
	if (iPixelFormat == 0) return false;
	if(!SetPixelFormat(hDC, iPixelFormat, &pfd)) return false;


	HGLRC hRCCompatible = wglCreateContext(hDC);
	wglMakeCurrent(hDC, hRCCompatible);

	bool bResult = true;

	if(glewInit() != GLEW_OK)
	{
			MessageBoxA(g_hWnd, "Couldn't initialize GLEW!", "Fatal Error", MB_ICONERROR);
			bResult = false;
	}

	wglMakeCurrent(NULL, NULL);
	wglDeleteContext(hRCCompatible);

	return bResult;
}

HRESULT InitContext()
{
	int iMajorVersion=3;
	int iMinorVersion=0;

	HDC hDC = GetDC(g_hWnd);

	PIXELFORMATDESCRIPTOR pfd;
	ZeroMemory(&pfd,sizeof(pfd)); 

	bool bError=false;
	

	if(WGLEW_ARB_create_context && WGLEW_ARB_pixel_format)
	{
		const int iPixelFormatAttribList[] =
		{
			WGL_DRAW_TO_WINDOW_ARB, GL_TRUE,
			WGL_SUPPORT_OPENGL_ARB, GL_TRUE,
			WGL_DOUBLE_BUFFER_ARB, GL_TRUE,
			WGL_PIXEL_TYPE_ARB, WGL_TYPE_RGBA_ARB, 
			WGL_COLOR_BITS_ARB, 32,			       
			WGL_DEPTH_BITS_ARB, 24,             
			WGL_STENCIL_BITS_ARB, 8,
			0 // End of attributes list
		};
		int iContextAttribs[] =
		{
			WGL_CONTEXT_MAJOR_VERSION_ARB, iMajorVersion,
			WGL_CONTEXT_MINOR_VERSION_ARB, iMinorVersion,
			WGL_CONTEXT_FLAGS_ARB, WGL_CONTEXT_FORWARD_COMPATIBLE_BIT_ARB,
			0 // End of attributes list
		};

		int iPixelFormat, iNumFormats;
		wglChoosePixelFormatARB(hDC, iPixelFormatAttribList, NULL, 1, &iPixelFormat, (UINT*)&iNumFormats);
		if(!SetPixelFormat(hDC, iPixelFormat, &pfd))return false; 

		hRC = wglCreateContextAttribsARB(hDC, 0, iContextAttribs);
		// If everything went OK
		if(hRC) wglMakeCurrent(hDC, hRC);
		else bError = true;
	}
	else bError = true;
	
	if(bError)
	{
		// Generate error messages
		char sErrorMessage[255], sErrorTitle[255];
		sprintf(sErrorMessage, "OpenGL %d.%d is not supported! Please download latest GPU drivers!", iMajorVersion, iMinorVersion);
		sprintf(sErrorTitle, "OpenGL %d.%d Not Supported", iMajorVersion, iMinorVersion);
		MessageBoxA(g_hWnd, sErrorMessage, sErrorTitle, MB_ICONINFORMATION);
		return false;
	}
   return S_OK;
}





