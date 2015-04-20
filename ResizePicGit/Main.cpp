#include "stdafx.h"
#include "RescaleFuncs.h"

#ifdef eng
string registryerror = "Registry did not work";
string picpathcreatemsg = "Default path has not been set for pictures. Set a new path, like D:\\Kuvat\\";
string picnamemsg = "Give name of the picture and its filetype, like test.jpg";
string pathchanged = "Default filepath changed to: ";
string helpmsg = "If you want to change default picture folder, use -k as parameter and add the folder, like -k D:\\Koodaus\\";
#else
string registryerror = "Rekisteri ei toiminut";
string picpathcreatemsg = "Oletus sovelluspolkua kuville ei ole asetettu. Aseta uusi sovelluspolku esim D:\\Kuvat\\";
string picnamemsg = "Anna pienennettävän kuvan nimi ja tiedostotyyppi, esim test.jpg\n";
string pathchanged = "Oletuskansion polku muutettu: ";
string helpmsg = "Jos haluat vaihtaa oletuskansiota, käytä komentoparametrina -k kansipolku. Esimerkiksi -k D:\\Koodaus\\";
#endif


int main(int argc, char *argv[])
{

	//Tarkastetaan, että laittomia operaattoreita ei ole käytetty KESKEN
	/*if (argc > 1){

		if (string(argv[1]) != "-k" || string(argv[1] != "-h")){
			return 0;
		}

	}*/

	HKEY key;
	LONG Registry;
	string picpath = "D:\\Kuvat\\gitproj\\";
	string picname = "test.jpg";

	////Tarkistetaan, onko rekisterissä kansiota sovellukselle ...
	Registry = RegOpenKey(HKEY_CURRENT_USER, TEXT("Software\\PicResizer\\"), &key);
	if (Registry == ERROR_FILE_NOT_FOUND)
	{
		//... ´jos ei ole, luodaan se...
		Registry = RegCreateKeyEx(HKEY_CURRENT_USER, TEXT("Software\\PicResizer\\"), NULL, NULL, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &key, NULL);
		if (Registry){
			cout << registryerror << endl;
			return 0;
		}

		//... ja kysytään oletuskansion polku
		cout << picpathcreatemsg;
		cin >> picpath;
		RegSetValueExA(key, "picpath", 0, REG_SZ, (const BYTE*)picpath.c_str(), picpath.length() + 1);
	}

	////jos käytetään -k parametriä, voidaan asettaa uusi oletuskansio sovellukselle, joka lisätään rekisteriin
	if (argc > 1 && string(argv[1]) == "-k"){
		picpath = string(argv[2]);
		cout << pathchanged << " " << picpath << endl;
		RegSetValueExA(key, "picpath", 0, REG_SZ, (const BYTE*)picpath.c_str(), picpath.length() + 1);

	}

	if (argc > 1 && string(argv[1]) == "-h"){

		cout << helpmsg << endl;

	}

	//DWORD y_size = sizeof(picpath);
	//DWORD y_type = REG_SZ;

	//Registry = RegQueryValueExA(key, "picpath", NULL, &y_type, (LPBYTE)&picpath, &y_size);

	///*kysytään tiedoston nimi*/
	cout << picnamemsg;
	cin >> picname;



	RescalingFunds::rescalefuns::Downscale(picpath, picname, 150);


	printf("toimiiko");
	return 0;
}