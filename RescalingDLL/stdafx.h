// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//
#pragma once

#ifndef DLLclass
#define DLLclass

#include "targetver.h"

#include <cstdint>
#include <objidl.h>
#include <Gdiplus.h>
#include <GdiPlusImageCodec.h>
#include <string>
#include <fstream>

#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
// Windows Header Files:
#include <windows.h>

#ifdef RESCALINGFUNCSDLL_EXPORTS
#define RESCALINGFUNCSDLL_API __declspec(dllexport)
#else
#define RESCALINGFUNCSDLL_API __declspec(dllimport)
#endif


extern "C"
{
	RESCALINGFUNCSDLL_API void Downscale(char nimi, int size);

	RESCALINGFUNCSDLL_API int GetEncoderClsid(const WCHAR* form, CLSID* pClsid);
}

//class RescalingFuncs
//{
//public:
//	// creates copy of a picture and rescales it
//	
//private:
//	
//};


#endif 