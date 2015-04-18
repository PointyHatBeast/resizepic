ResizePicGit.exe: ResizePicGit.obj
	LINK ResizePicGit.obj Lib\ScalingDLL.obj /OUT:..\out\ResizePicGit.exe
Main.obj : Main.cpp stdafx.h
	CL /c Main.cpp
clean : 
	rm ResizePicGit.exe Main.obj
all : clean ResizePicGit.exe