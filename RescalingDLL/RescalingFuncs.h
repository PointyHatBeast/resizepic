#ifdef RESCALINGFUNCSDLL_EXPORTS
#define RESCALINGFUNCSDLL_API __declspec(dllexport)
#else
#define RESCALINGFUNCSDLL_API __declspec(dllimport)
#endif

#pragma once
namespace RescalingFuncs
{

	class RescalingFuncs
	{
	public:
		RescalingFuncs();
		~RescalingFuncs();
		// creates copy of a picture and rescales it
		static void RESCALINGFUNCSDLL_API Downscale(char name, int size);

	};
}

