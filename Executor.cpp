#include <fstream>
#include <Windows.h>

#define __ L"pref.pre"

struct T_T
{
	HWND handle;
	DWORD desired_id;
};
BOOL CALLBACK EnumWindowsProc(HWND hwnd, LPARAM lpar)
{
	DWORD id;
	GetWindowThreadProcessId(hwnd, &id);
	if (((T_T*)lpar)->desired_id == id)
	{
		((T_T*)lpar)->handle = hwnd;
		SetLastError(ERROR_SUCCESS);
		return FALSE;
	}
	return TRUE;
}

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR lp_com_line, int nCom)
{
	std::ofstream O_O;
	O_O.open("log_of_executor.txt");
	if (!O_O.is_open()) return 1;
	HANDLE h_mutex=NULL;
	HANDLE I_L=NULL;
	h_mutex = CreateMutex(NULL, FALSE, L"injector_v3_preferences_mutex");
	if (h_mutex == NULL)
	{
		O_O << "Error creating mutex: #" << GetLastError()<<std::endl;
		O_O.close();
		return 1;
	}
	WaitForSingleObject(h_mutex, INFINITE);
	I_L = CreateFile(__, GENERIC_READ, FILE_SHARE_WRITE|FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (I_L == NULL)
	{
		O_O << "Error opening pref.pre: #" << GetLastError() << std::endl;
		O_O.close();
		ReleaseMutex(h_mutex);
		CloseHandle(h_mutex);
		return 2;
	}
	O_O << "Last error: #" << GetLastError() << std::endl;
	BYTE I_D[4];
	DWORD H_G;
	if (!ReadFile(I_L, I_D, 4, &H_G, NULL))
	{
		O_O << "Error reading file: #" << GetLastError() << std::endl;
		O_O.close();
		CloseHandle(I_L);
		ReleaseMutex(h_mutex);
		CloseHandle(h_mutex);
		return 3;
	}
	DWORD main_id = ((DWORD)(*I_D) << 24) | ((DWORD)(*(I_D+ 1)) << 16) | ((DWORD)(*(I_D+ 2)) << 8) | ((DWORD)(*(I_D+ 3)));
	T_T temp;
	temp.handle = NULL;
	temp.desired_id = main_id;
	O_O << "main id before searching: " << temp.desired_id << std::endl;
	if (0 == EnumWindows(EnumWindowsProc, (LPARAM)(&temp)))
	{
		if (ERROR_SUCCESS == GetLastError()) //see mdsn EnumWindows()
		{
			if (NULL == temp.handle)
			{
				O_O << "ERROR main handle is not got" << std::endl;
				O_O.close();
				CloseHandle(I_L);
				ReleaseMutex(h_mutex);
				CloseHandle(h_mutex);
				return 4;
			}
			else
			{
			}
		}
		else
		{
			O_O << "ERROR getting main handle" << std::endl;
			O_O.close();
			CloseHandle(I_L);
			ReleaseMutex(h_mutex);
			CloseHandle(h_mutex); 
			return 4;
		}
	}
	else //probably is not ever happening
	{
		if (NULL == temp.handle)
		{
			O_O << "ERROR main handle is not got" << std::endl;
			O_O.close();
			CloseHandle(I_L);
			ReleaseMutex(h_mutex);
			CloseHandle(h_mutex); 
			return 4;
		}
	}
	if (PostMessage(temp.handle, WM_CLOSE, 0, 0))
	{
		O_O << "WM_CLOSE successfully sent" << std::endl;
	}
	else
	{
		O_O << "failed to send WM_CLOSE, error: "<<GetLastError()<< std::endl;
		O_O.close();
		CloseHandle(I_L);
		ReleaseMutex(h_mutex);
		CloseHandle(h_mutex); 
		return 5;
	}
	O_O.close();
	CloseHandle(I_L);
	ReleaseMutex(h_mutex);
	CloseHandle(h_mutex);
	return 0;
}
