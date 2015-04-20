// ResizePicGit.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "RescaleFuncs.h"


//namespace RescalingFunds{
using namespace RescalingFunds;
using namespace Gdiplus;

void rescalefuns::Downscale(string path, string nimi, int size){
	
	
	//tehdään kuvan polusta yhteensopiva Gdiplussan funktioille
	string originalfilepath = path + nimi;
	wstring originalpathwide(originalfilepath.begin(), originalfilepath.end());

	//copyFile(path, nimi);

	// Prepare GDIplus
	Gdiplus::GdiplusStartupInput gdiplusStartupInput;
	ULONG_PTR gdiplusToken;
	Gdiplus::GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, 0);



	wchar_t const* name = L"D:\\Kuvat\\gitproj\\test.jpg";
	//wchar_t const* name = originalpathwide.c_str();
	wchar_t const* name2 = L"D:\\Kuvat\gitproj\\test2.jpg";
	//// load the image from the disk
	Gdiplus::Bitmap* original = Gdiplus::Bitmap::FromFile(name);

	UINT o_height = original->GetHeight();
	UINT o_width = original->GetWidth();

	INT n_width = 150;
	INT n_height = 150;
	

	Gdiplus::Bitmap* newBitmap = new Gdiplus::Bitmap(n_width, n_height, original->GetPixelFormat());
	/*Gdiplus::Graphics graphics(newBitmap);
	graphics.DrawImage(original, 0, 0, n_width, n_height);
	

	CLSID jpgCLsid;
	if (GetEncoderClsid(L"image/jpeg", &jpgCLsid) > -1){
		newBitmap->Save(name2, &jpgCLsid);
	}*/

	delete original;
	delete newBitmap;
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

void rescalefuns::copyFile(string path, string name){

	string file1 = "D:\\Kuvat\\gitproj\\test.jpg";
	string file2 = "D:\\Kuvat\gitproj\\test2.jpg";

	std::wstring stemp = std::wstring(file1.begin(), file1.end());
	LPCWSTR sw = stemp.c_str();

	std::wstring stemp2 = std::wstring(file2.begin(), file2.end());
	LPCWSTR sw2 = stemp2.c_str();

	CopyFile(sw, sw2, false);
}
//}
//laina funktiot
void rescalefuns::compressImpl(const std::string& path, int size, ULONG quality)
{
	HBITMAP hbmReturn = NULL;
	Bitmap* bmPhoto = NULL;

	std::wstring upath;
	//UnicodeConverter::toUTF16(path, upath);

	{
		Bitmap image(upath.c_str());

		int srcWidth = image.GetWidth();
		int srcHeight = image.GetHeight();

		float percent = 0;
		int destX = 0, destY = 0;
		if (srcWidth > srcHeight)
		{
			percent = ((float)size / (float)srcWidth);
			destX = (int)((size - (srcWidth * percent)) / 2);
		}
		else
		{
			percent = ((float)size / (float)srcHeight);
			destY = (int)((size - (srcHeight * percent)) / 2);
		}

		if (percent >= 1.0f)
			return; // skip compress

		int destWidth = (int)(srcWidth * percent);
		int destHeight = (int)(srcHeight * percent);

		bmPhoto = new Bitmap(destWidth, destHeight, PixelFormat24bppRGB);
		bmPhoto->SetResolution(image.GetHorizontalResolution(), image.GetVerticalResolution());

		Graphics *grPhoto = Graphics::FromImage(bmPhoto);
		Color colorW(255, 255, 255, 255);
		grPhoto->Clear(colorW);
		grPhoto->SetInterpolationMode(InterpolationModeHighQualityBicubic);
		grPhoto->DrawImage(&image, Rect(destX, destY, destWidth, destHeight));

		bmPhoto->GetHBITMAP(colorW, &hbmReturn);
		delete grPhoto;
	}

	// find appropriate encoder, jpeg
	CLSID encoderClsid;
	getEncoderClsid(L"image/jpeg", &encoderClsid);

	// set output quality for jpeg alone
	EncoderParameters encoderParameters;
	setEncoderQuality(&encoderParameters, &quality);

	// output to image file with desired quality
	bmPhoto->Save(upath.c_str(), &encoderClsid, &encoderParameters);

	// release resources
	delete bmPhoto;
	DeleteObject(hbmReturn);
}
int rescalefuns::getEncoderClsid(const WCHAR* format, void* clsid)
{
	UINT num = 0; // number of image encoders
	UINT size = 0; // size of the image encoder array in bytes

	ImageCodecInfo* pImageCodecInfo = NULL;
	GetImageEncodersSize(&num, &size);
	if (size == 0)
		return -1; // Failure

	pImageCodecInfo = (ImageCodecInfo*)(malloc(size));
	if (pImageCodecInfo == NULL)
		return -1; // Failure

	GetImageEncoders(num, size, pImageCodecInfo);
	for (UINT j = 0; j < num; ++j)
	{
		if (wcscmp(pImageCodecInfo[j].MimeType, format) == 0)
		{
			*(CLSID*)clsid = pImageCodecInfo[j].Clsid;
			free(pImageCodecInfo);
			return j;  //Success
		}
	}

	free(pImageCodecInfo);
	return -1; // Failure
}

void rescalefuns::setEncoderQuality(void* params, ULONG *quality)
{
	EncoderParameters* encoderParams = (EncoderParameters*)params;
	encoderParams->Count = 1;
	encoderParams->Parameter[0].Guid = EncoderQuality;
	encoderParams->Parameter[0].Type = EncoderParameterValueTypeLong;
	encoderParams->Parameter[0].NumberOfValues = 1;

	encoderParams->Parameter[0].Value = quality;
}