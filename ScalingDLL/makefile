ScalingDLL.dll.: RescaleFuncs.obj dllmain.obj stdafx.obj
	LINK /DLL RescaleFuncs.obj dllmain.obj stdafx.obj /OUT:..\make\ScalingDLL.dll
RescaleFuncs.obj : ResizePicGit.cpp RescaleFuncs.h stdafx.h
	CL /c ResizePicGit.cpp
dllmain.obj: dllmain.cpp stdafx.h
	CL /c dllmain.cpp
stdafx.obj: stdafx.cpp stdafx.h
	CL /c stdafx.cpp
clean : 
	rm RescaleFuncs.obj dllmain.obj stdafx.obj
all : clean ScalingDLL.dll