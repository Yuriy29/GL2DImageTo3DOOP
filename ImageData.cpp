#include "ImageData.h"


ImageData::ImageData(HWND hwndDlg){
	g_hWnd = hwndDlg;
	hBitmap = NULL;
	//GetCurrentDirectory(MAX_PATH, mImagePath);
	//wcscat_s (mImagePath, L"Demo.bmp");
	this->LoadImageDefault();
	GetObject(hBitmap, sizeof(bm), &bm);
	bmpInfo.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
    bmpInfo.bmiHeader.biWidth = bm.bmWidth;
    bmpInfo.bmiHeader.biHeight = -bm.bmHeight;
    bmpInfo.bmiHeader.biPlanes = 1;
    bmpInfo.bmiHeader.biBitCount = 32;
    bmpInfo.bmiHeader.biCompression = BI_RGB;        
    bmpInfo.bmiHeader.biSizeImage = 0;

	widthImage = bm.bmWidth;
	heightImage = bm.bmHeight;
}

void ImageData::LoadImageDefault (){
	SAFE_DELETE_OBJECT (hBitmap);
	hBitmap = (HBITMAP)LoadImage(NULL, L"Demo.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE|LR_CREATEDIBSECTION);
	  if (NULL != hBitmap)
	  {
		  ;
	  }
 }

 void ImageData::LoadSelectedImage (){
	if (mFileDialog.ShowDialog(g_hWnd))
    {   
		hBitmap = (HBITMAP)LoadImage(NULL, mFileDialog.GetFileName(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE|LR_CREATEDIBSECTION);
	}
 
 }

 INT32 ImageData::getWidthImage(){
	 return this->widthImage;
 }
 INT32 ImageData::getHeightImage(){
	 return this->heightImage;
 }
 HBITMAP ImageData::gethBitmap(){
	  return this->hBitmap;
 
 }

 BITMAPINFO ImageData::getBmpInfo(){
	 return this->bmpInfo;
 }



ImageData::~ImageData(void)
{
}
