#include <Windows.h>

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR lp_com_line, int nCom)
{
	HANDLE file;
	DWORD Chuan;
	file = CreateFile(L"pref.pre", GENERIC_READ | GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	BYTE ARS_ART[15];
	ARS_ART[0] = 0;
	ARS_ART[1] = 0;
	ARS_ART[2] = 0;
	ARS_ART[3] = 0;
	ARS_ART[4] = 2;
	ARS_ART[5] = 0x51;  //Q
	ARS_ART[6] = VK_CONTROL;
	ARS_ART[7] = 0;
	ARS_ART[8] = 0;
	ARS_ART[9] = 1;//way
	ARS_ART[10] = 0x53;
	ARS_ART[11] = VK_CONTROL;
	ARS_ART[12] = VK_MENU;
	ARS_ART[13] = 0;
	ARS_ART[14] = 2;//way
	WriteFile(file, ARS_ART, 15, &Chuan, NULL);
	CloseHandle(file);
	return 0;
}
