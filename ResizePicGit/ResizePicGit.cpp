// ResizePicGit.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "RescaleFuncs.h"


namespace RescalingFunds{

	void rescalefuns::Downscale(char nimi, int size){
		// Prepare GDIplus
		Gdiplus::GdiplusStartupInput gdiplusStartupInput;
		ULONG_PTR gdiplusToken;
		Gdiplus::GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, 0);

		// load the image from the disk
		Gdiplus::Bitmap* original;
		wchar_t const* name = L"D:\Kuvat\gitproj\test.jpg";
		wchar_t const* name2 = L"D:\Kuvat\gitproj\test2.jpg";
		original->FromFile(name);

		UINT o_height = original->GetHeight();
		UINT o_width = original->GetWidth();

		INT n_width = 150;
		INT n_height = 150;

		Gdiplus::Bitmap* newBitmap = new Gdiplus::Bitmap(n_width, n_height, original->GetPixelFormat());
		Gdiplus::Graphics graphics(newBitmap);
		graphics.DrawImage(original, 0, 0, n_width, n_height);

		CLSID jpgCLsid;
		if (GetEncoderClsid(L"image/jpeg", &jpgCLsid) > -1){
			newBitmap->Save(name2, &jpgCLsid);
		}

		// Stop Gdiplus
		Gdiplus::GdiplusShutdown(gdiplusToken);
	}

	int rescalefuns::GetEncoderClsid(const WCHAR* form, CLSID* pClsid){

		UINT num;
		UINT size;
		Gdiplus::ImageCodecInfo* pImageCodecInfo = NULL;
		Gdiplus::GetImageEncodersSize(&num, &size);
		if (size == 0)
			return -1;
		pImageCodecInfo = (Gdiplus::ImageCodecInfo*)(malloc(size));
		if (pImageCodecInfo == NULL)
			return -1;
		Gdiplus::GetImageEncoders(num, size, pImageCodecInfo);
		for (UINT j = 0; j < num; j++)
		{
			if (wcscmp(pImageCodecInfo[j].MimeType, form) == 0)
			{
				*pClsid = pImageCodecInfo[j].Clsid;
				free(pImageCodecInfo);
				return j;
			}
		}
		free(pImageCodecInfo);
		return -1;
	}
}