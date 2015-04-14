// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//
#ifdef PICTURESCALINGDLL_EXPORTS
#define PICTURESCALINGDLL_API __declspec(dllexport) 
#else
#define PICTURESCALINGDLL_API __declspec(dllimport) 
#endif
 
#pragma once

#include "targetver.h"

#include <stdio.h>
#include <tchar.h>



// TODO: reference additional headers your program requires here
