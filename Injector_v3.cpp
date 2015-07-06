#include <Windows.h>
#include <fstream>
#define logfile "log_of_main.txt"
#define com_file L"pref.pre"
#define event_default L"event_name_10999"

HWND h_window=NULL;
HHOOK h_hook=NULL;
HMODULE h_hook_dll=NULL;
int clip_counter=0;
HANDLE pref_file = NULL;
HANDLE h_mutex = NULL;
//HANDLE event_ = NULL;
//class log* p_log;
std::ofstream p_log;
LRESULT (*p_hook_func) (int, DWORD, DWORD);

LRESULT CALLBACK main_loop(HWND hwnd, UINT msg, WPARAM wpar, LPARAM lpar)
{
	p_log << "message: " << msg << std::endl;
	switch (msg)
	{
	case WM_NULL:
	{
		if ((wpar == 12) && (lpar == 10999))
		{
			p_log << "clip_counter set to 0" << std::endl;
			clip_counter = 0;
		}
		if ((wpar == 12) && (lpar == 10998))
		{
			p_log << "copying awaiting timeout" << std::endl;
			keybd_event(0x0e, 0, KEYEVENTF_KEYUP, 0);
		}
		return 0;
		break;
	}
	case WM_CLIPBOARDUPDATE:
	{
		p_log << "clipboard update message" << std::endl;
		switch (clip_counter)
		{
		case 0:
		{
			p_log << "clipboard update message sent" << std::endl;
			clip_counter++;
			keybd_event(0xe8, 0 , KEYEVENTF_KEYUP, 0);
			break;
		}
		case 1:
		{
			p_log << "clipboard update message not sent" << std::endl;
			p_log << "(own modification)" << std::endl;
			clip_counter--;
			break;
		}
		}
		break;
	}
	case WM_KEYDOWN:
	{
		p_log << "key\t" << wpar << "\tDOWN";
		p_log << std::endl;
		break;
	}
	case WM_KEYUP:
	{
		p_log << "key\t" << wpar << "\tUP";
		p_log << std::endl;
		break;
	}
	case WM_CLOSE:
	{
		DestroyWindow(h_window);
		break;
	}
	case WM_DESTROY:
	{
		if (h_hook_dll)
		{
			void(*p_uninit_f)(void);
			p_uninit_f = (void(*)(void))GetProcAddress(h_hook_dll, "upload");
			if (!p_uninit_f)
			{
				p_log << "Error loading upload function" << std::endl;
				p_log << "Error code: " << GetLastError() << std::endl;
			}
			else
			{
				p_log << "uploading" << std::endl;
				p_uninit_f();
			}
			if (h_hook)
			{
				UnhookWindowsHookEx(h_hook);	
			}
			FreeLibrary(h_hook_dll);
		}
		if (pref_file) CloseHandle(pref_file);
		else
		{
			pref_file = CreateFile(com_file, GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
			if (pref_file != NULL)
			{
				DWORD ferrari = GetCurrentProcessId();
				BYTE dendi[4] = { 0, 0, 0, 0 };
				p_log << "writing: 4 zeroes"<< std::endl;
				if (!WriteFile(pref_file, dendi, 4, &ferrari, NULL))
				{
					p_log << "Error writing main id: " << GetLastError() << std::endl;
				}
				p_log << "Wrote file" << std::endl;
			}
		}
		if (h_mutex) CloseHandle(h_mutex);
		p_log.close();
		PostQuitMessage(0);
		break;
	}
	default: 
		return DefWindowProc(hwnd, msg, wpar, lpar);
	}
	return 0; // DefWindowProc(hwnd, msg, wpar, lpar);
}

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR lp_com_line, int nCom)
{
	p_log.open(logfile);
	std::ofstream templar;
	templar.open("lastlog.txt", std::ios_base::trunc);
	templar.close();
	WNDCLASSEX wc;
	MSG message;
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = 0;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.lpfnWndProc = main_loop;
	wc.hInstance = hInst;
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wc.lpszMenuName = L"Main menu";
	wc.lpszClassName = L"test";
	wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	if (!RegisterClassEx(&wc)) 
	{
		p_log<<"Error class registring"<<std::endl;
		p_log << "Error code: " << GetLastError() << std::endl;
		return 0;
	}
	h_window = CreateWindow(L"test", L"some", WS_DISABLED, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL, hInst, NULL);
	if (!h_window)
	{
		p_log<<"Error CreateWindow"<<std::endl;
		p_log << "Error code: " << GetLastError() << std::endl;
		return 0;
	}
	h_mutex = CreateMutex(NULL, FALSE, L"injector_v3_preferences_mutex");
	if (h_mutex == NULL)
	{
		p_log << "Failed to create mutex, error: #" << GetLastError() << std::endl;
		SendMessage(h_window, WM_CLOSE, 0, 0);
	}
	DWORD wait_res;
	wait_res=WaitForSingleObject(h_mutex, INFINITE);
	pref_file = CreateFile(com_file, GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (pref_file == NULL)
	{
		p_log << "Error opening pref.pre" << GetLastError() << std::endl;
		SendMessage(h_window, WM_CLOSE, 0, 0);
	}
	DWORD ferrari = GetCurrentProcessId();
	BYTE dendi[5];
	dendi[0] = 0x000000ff & (ferrari >> 24);
	dendi[1] = 0x000000ff & (ferrari >> 16);
	dendi[2] = 0x000000ff & (ferrari >> 8);
	dendi[3] = 0x000000ff & ferrari;
	p_log << "id is: " << GetCurrentProcessId() << std::endl;
	p_log << "id is: " <<std::hex<< GetCurrentProcessId() << std::endl;
	p_log << "writing: " <<(int) dendi[0] << "\t" <<(int) dendi[1] << "\t" << (int)dendi[2] << "\t" << (int)dendi[3] << "\t" <<std::dec<< std::endl;
	if (!WriteFile(pref_file, dendi, 4, &ferrari, NULL))
	{
		p_log << "Error writing main id: " << GetLastError() << std::endl;
		SendMessage(h_window, WM_CLOSE, 0, 0);
	}
	p_log << "Wrote file" << std::endl;
	
	if (!ReadFile(pref_file, dendi+4, 1, &ferrari, NULL))	
	{
		p_log << "Error rading number of shortcuts: " << GetLastError() << std::endl;
		p_log << "read sybols: " << ferrari << std::endl; 
		SendMessage(h_window, WM_CLOSE, 0, 0);
	}
	p_log << "read " << ferrari << "bytes" << std::endl;
	p_log << std::hex << "read: " << (int)dendi[0] << "\t" << (int)dendi[1] << "\t" << (int)dendi[2] << "\t" << (int)dendi[3] << "\t" << (int)dendi[4] << std::dec << std::endl;
	if (dendi[4] == 0)
	{
		p_log << "No shortcuts, closing programm" << std::endl;
		SendMessage(h_window, WM_CLOSE, 0, 0);
	}
	else
	{
		p_log << "dendi is: " << (int)dendi[4]<<std::endl;
		BYTE *ohayo=NULL;
		ohayo = new BYTE[dendi[4] * 5 + 5];
		for (int Fng = 0; Fng < 5; Fng++) Fng[ohayo] = dendi[Fng];
		if (!ReadFile(pref_file, ohayo+5, dendi[4] * 5, &ferrari, NULL))
		{
			p_log << "Error rading pref.txt" << GetLastError() << std::endl;
			SendMessage(h_window, WM_CLOSE, 0, 0);
		}
		h_hook_dll = LoadLibrary(L"TextHook.dll");
		if (h_hook_dll)
		{
			p_log << "Thread: " << GetCurrentThreadId() << std::endl;
			p_log << "Process Id: " << GetCurrentProcessId() << std::endl;
			p_log << "Loaded library" << std::endl;
			void(*p_init_f)(BYTE*);
			p_init_f = (void(*)(BYTE*))GetProcAddress(h_hook_dll, "initialize");
			if (!p_init_f)
			{
				p_log << "Error loading initialize" << std::endl;
				p_log << "Error code: " << GetLastError() << std::endl;
				SendMessage(h_window, WM_CLOSE, 0, 0);
			}
			else
			{
				p_log << "initialization" << std::endl;
				p_init_f(ohayo);
				CloseHandle(pref_file);
				ReleaseMutex(h_mutex);
				CloseHandle(h_mutex);
				pref_file = NULL;
				h_mutex = NULL;
			}
			p_hook_func = (LRESULT(*)(int, DWORD, DWORD))GetProcAddress(h_hook_dll, "_text_hook@12");
			if (!p_hook_func)
			{
				p_log << "Error loading text_hook" << std::endl;
				p_log << "Error code: " << GetLastError() << std::endl;
				SendMessage(h_window, WM_CLOSE, 0, 0);
			}
			else
			{
				h_hook = SetWindowsHookEx(WH_KEYBOARD_LL, (HOOKPROC)p_hook_func, h_hook_dll, 0);// GetThreadId(h_window));
				if (!h_hook)
				{
					p_log << "Error SetWindowsHookEx" << std::endl;
					p_log << "Error code: " << GetLastError() << std::endl;
					SendMessage(h_window, WM_CLOSE, 0, 0);
				}
				else
				{
					p_log << "Set hook" << std::endl;
				}
			}
		}
		else
		{
			p_log << "Error DLL load" << std::endl;
			p_log << "Error code: " << GetLastError() << std::endl;
			SendMessage(h_window, WM_CLOSE, 0, 0);
		}
		delete ohayo;
	}
	ShowWindow(h_window, SW_HIDE);
	
	while (GetMessage(&message, NULL, 0, 0))
	{
		TranslateMessage(&message);
		DispatchMessage(&message);
	}
	return message.wParam;
}
