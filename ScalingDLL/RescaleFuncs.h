// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//
#pragma once

#pragma comment(lib,"gdiplus.lib")

#ifndef DLLclass
#define DLLclass

#include <cstdint>
#include <objidl.h>
#include <Gdiplus.h>
#include <GdiPlusImageCodec.h>
#include <string>
#include <fstream>

#define RESCALINGFUNCSDLL_EXPORTS

#ifdef RESCALINGFUNCSDLL_EXPORTS
#define RESCALINGFUNCSDLL_API __declspec(dllexport)
#else
#define RESCALINGFUNCSDLL_API __declspec(dllimport)
#endif

using namespace std;

namespace RescalingFunds{
	class RESCALINGFUNCSDLL_API rescalefuns{
	public:
		static void Downscale(string path, string nimi, int size);

		static int GetEncoderClsid(const WCHAR* form, CLSID* pClsid);
	};
	
}
#endif 
