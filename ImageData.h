#pragma once
#include "stdafx.h"
#include "OpenFileDialog.h"
class ImageData
{
private:
	HBITMAP hBitmap;
	BITMAPINFO bmpInfo;
	BITMAP bm;
	COpenFileDialog mFileDialog;  
	TCHAR mImagePath[MAX_PATH]; 
	INT32 widthImage;
	INT32 heightImage;
    HWND g_hWnd;

public:
	void LoadImageDefault();
	void LoadSelectedImage ();
	INT32 getWidthImage();
	INT32 getHeightImage();
	HBITMAP gethBitmap();
	BITMAPINFO getBmpInfo();
	ImageData(HWND hwndDlg);
	~ImageData(void);
};

