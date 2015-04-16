#include "stdafx.h"
#include "RescaleFuncs.h"

#ifdef eng
string helpmsg = "";
string registryerror = "Registry did not work";
string picpathcreatemsg = "Default path has not been set for pictures. Set a new path, like D://Kuvat//";
string picnamemsg = "Give name of the picture and its filetype, like test.jpg";
#else
string helpmsg = "";
string registryerror = "Rekisteri ei toiminut";
string picpathcreatemsg = "Oletus sovelluspolkua kuville ei ole asetettu. Aseta uusi sovelluspolku esim D://Kuvat//";
string picnamemsg = "Anna pienennettävän kuvan nimi ja tiedostotyyppi, esim test.jpg";
#endif


int main(int argc, char *argv[])
{
	HKEY key;
	LONG Registry;
	string picpath = "D:\\Kuvat\\gitproj\\";
	string picname = "test.jpg";
	Registry = RegOpenKey(HKEY_CURRENT_USER, TEXT("Software\\PicResizer\\"), &key);
	if (Registry == ERROR_FILE_NOT_FOUND)
	{
		Registry = RegCreateKeyEx(HKEY_CURRENT_USER, TEXT("Software\\PicResizer\\"), NULL, NULL, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &key, NULL);
		if (Registry){
			cout << registryerror << endl;
			return 0;
		}
		cout << picpathcreatemsg;
		cin >> picpath;
		RegSetValueExA(key, "picpath", 0, REG_SZ, (const BYTE*)picpath.c_str(), picpath.length() + 1);
	}

	DWORD y_size = sizeof(picpath);
	DWORD y_type = REG_SZ;
	
	Registry = RegQueryValueExA(key, "picpath", NULL, &y_type, (LPBYTE)&picpath, &y_size);


	cout << picnamemsg;
	cin >> picname;

	RescalingFunds::rescalefuns::Downscale(picpath, picname, 150);

	
	printf("toimiiko");
	return 0;
}