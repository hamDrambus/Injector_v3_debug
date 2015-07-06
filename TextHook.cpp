#include "TextHook.h"

#define event_default L"event_name_10999"
#define SHIFT_UP_PREVENTING 1

struct shortcut
{
	SHORT way;
	SHORT keys[4];
};

SHORT Num_of_shortcuts=0;
shortcut *arr_k = NULL;
SHORT stage=0;
int modification = 0;
DWORD main_id = 0;
HWND h_main_window = NULL;
BYTE unclear_counter = SHIFT_UP_PREVENTING;
HANDLE h_event = NULL;
HANDLE h_thread = NULL;
DWORD thread_id = 0;

struct T_T_debug
{
	HWND handle;
	DWORD desired_id;
	std::ofstream *debug; //for debugging obv.
};

struct T_T
{
	HWND handle;
	DWORD desired_id;
};

void initialize(BYTE* buffer);
DWORD intercept_shortcut(KBDLLHOOKSTRUCT *info, WPARAM wpar, std::ostream &debug_stream);
DWORD intercept_shortcut(KBDLLHOOKSTRUCT *info, WPARAM wpar);
int SetMainToListeningClipboard(DWORD main_id);
int SetMainToListeningClipboard(DWORD main_id,std::ofstream & debug_stream);
DWORD WINAPI ThreadProc(LPVOID lp_info);
int RemoveMainFromListeningClipboard(DWORD main_id);
int RemoveMainFromListeningClipboard(DWORD main_id, std::ofstream &debug_stream);
BOOL CALLBACK EnumWindowsProc(HWND hwnd, LPARAM lpar);
BOOL CALLBACK EnumWindowsProc_debug(HWND hwnd, LPARAM lpar);
int change_text(int way);

void simulate_copying(void);
void simulate_inserting(void);
void simulate_key_up(WORD vk_code);

void upload(void);

void initialize(BYTE* buffer) //guaranteed to contain at least 5 bytes
{
	main_id = ((DWORD)(*buffer) << 24) | ((DWORD)(*(buffer + 1)) << 16) | ((DWORD)(*(buffer + 2)) << 8) | ((DWORD)(*(buffer + 3)));
	Num_of_shortcuts = *(buffer + 4);
	arr_k = new shortcut[Num_of_shortcuts];
	for (int o_O = 0; o_O < Num_of_shortcuts; o_O++)
	{
		arr_k[o_O].keys[0] = *(buffer + 5 + 5*o_O);  //trigger VK_KEY
		arr_k[o_O].keys[1] = *(buffer + 6 + 5*o_O);
		arr_k[o_O].keys[2] = *(buffer + 7 + 5*o_O);
		arr_k[o_O].keys[3] = *(buffer + 8 + 5*o_O);
		arr_k[o_O].way = *(buffer + 9 + 5*o_O); //must be >0
	}
}
void upload(void)
{
	delete arr_k;
}

int GetAsyncKeyboardState(BYTE* Sonneiko)
{
	for (int XBOCT = 0; XBOCT < 256; XBOCT++)
	{
		Sonneiko[XBOCT] = GetAsyncKeyState(XBOCT);
		//if (Sonneiko[XBOCT]==0) return 0;
	}
	return 1;
}
int GetKeyboardState_(SHORT* Sonneiko)
{
	for (int XBOCT = 0; XBOCT < 256; XBOCT++)
	{
		*(Sonneiko + XBOCT) = GetKeyState(XBOCT);
	}
	return 1;
}
//return: lowest byte = way, next  = index of shortcut or 0 if failed
DWORD intercept_shortcut(KBDLLHOOKSTRUCT *info, WPARAM wpar, std::ostream &O_O)
{
	if ((stage != 0) || (wpar != WM_KEYDOWN)) return 0;
	int vk_i;
	SHORT  temp_arr[256];/*
	BYTE temp_arr2[256];
	if (GetKeyboardState(temp_arr2))
	{
		O_O << std::hex;	//<temp
		O_O << "\tGetKeyboardState: ";
		for (int ___ = 0; ___ < 256; ___++)
		{
			if (temp_arr2[___] >> 7)
			{
				O_O << "key " << ___;
				O_O << " DN\t";
			}
			//else O_O << " up\t";
		}
		O_O << std::dec << std::endl;//temp>
	}
	else
	{
		O_O << "GetKeyboardState error: " << GetLastError() << std::endl;
	}/*
	if (GetAsyncKeyboardState(temp_arr2))
	{
		O_O << std::hex;	//<temp
		O_O << "\tGetAsyncKeyState: ";
		for (int ___ = 0; ___ < 256; ___++)
		{
			if (temp_arr2[___] >> 7)
			{
				O_O << "key " << ___;
				O_O << " DN\t";
			}
			//else O_O << " up\t";
		}
		O_O << std::dec << std::endl;//temp>
	}
	else
	{
		O_O << "GetKeyboardState error: " << GetLastError() << std::endl;
	}*/
	if (GetKeyboardState_(temp_arr))
	{
		O_O << std::hex;	//<temp
		O_O << "\tGetKeyState: ";
		for (int ___ = 0; ___ < 256; ___++)
		{
			if (temp_arr[___] >> 7)
			{
				O_O << "key " << ___;
				O_O << " DN\t";
			}
			//else O_O << " up\t";
		}
		O_O << std::dec << std::endl;//temp>
	}
	else
	{
		O_O << "GetKeyboardState error: " << GetLastError() << std::endl;
		return 0;
	}
	for (int oo = 0; oo < Num_of_shortcuts; oo++)
	{
		if (arr_k[oo].keys[0]==info->vkCode)
		{
			O_O << "Trying shortcut # " << oo<<std::endl;
			int match = 1;
			vk_i = oo; //found trigger key in the list of shortcuts
			int state = 0;
			int needed_state = 0;
			for (int ___ = 1; ___ < 4; ___++)
			{
				if (arr_k[vk_i].keys[___] != 0) needed_state++; //amount of required pressed keys
			}
			for (int ___ = 0x05; ___ < 0x9F; ___++) //
			{
				if (temp_arr[___]>>7) state++; //amount of pressed keys
			}
			for (int ___ = 0xA6; ___ <= 0xFE; ___++) //don't count right and left keys (ctrl, shift and windows key) -> missed 0x10 - 0x15
			{
				if (temp_arr[___]>>7) state++; //amount of pressed keys
			}
			for (int ___ = 1; ___ < 4; ___++)
			{
				//do not distinguish L and R keys, at the moment at least
				if ((arr_k[vk_i].keys[___] == VK_LSHIFT) || (arr_k[vk_i].keys[___] == VK_RSHIFT)) arr_k[vk_i].keys[___] = VK_SHIFT;
				if ((arr_k[vk_i].keys[___] == VK_CONTROL) || (arr_k[vk_i].keys[___] == VK_RCONTROL)) arr_k[vk_i].keys[___] = VK_CONTROL;
				if ((arr_k[vk_i].keys[___] == VK_LMENU) || (arr_k[vk_i].keys[___] == VK_RMENU)) arr_k[vk_i].keys[___] = VK_MENU;
				if (arr_k[vk_i].keys[___] != 0)
				{
					if (temp_arr[arr_k[vk_i].keys[___]] >> 7)
					{
					}
					else
					{
						match = 0; //not pressed riquired key
					}
				}
			}
			O_O << "neeeded state = " <<needed_state<< std::endl;
			O_O << "state = " << state << std::endl;
			O_O << "match = " << match << std::endl;
			if (needed_state != state) match = 0;
			if (match) return ((DWORD)arr_k[vk_i].way) | (((DWORD)vk_i) << 8);
			//continue trying other keyshorts
		}
	}
	return 0;
}
DWORD intercept_shortcut(KBDLLHOOKSTRUCT *info, WPARAM wpar)
{
	int vk_i;
	SHORT temp_arr[256];
	if (!GetKeyboardState_(temp_arr)) return 0;
	if ((stage != 0) || (wpar != WM_KEYDOWN)) return 0;
	for (int oo = 0; oo < Num_of_shortcuts; oo++)
	{
		if (arr_k[oo].keys[0] == info->vkCode)
		{
			int match = 1;
			vk_i = oo; //found trigger key in the list of shortcuts
			int state = 0;
			int needed_state = 0;
			for (int ___ = 1; ___ < 4; ___++)
			{
				if (arr_k[vk_i].keys[___] != 0) needed_state++; //amount of required pressed keys
			}
			for (int ___ = 0x05; ___ < 0x9F; ___++) //don't count mouse buttons -> missed 0x01 - 0x04
			{
				if (temp_arr[___] >> 7) state++; //amount of pressed keys
			}
			for (int ___ = 0xA6; ___ <= 0xFE; ___++) //don't count right and left keys (ctrl, shift and windows key) -> missed 0x10 - 0x15
			{
				if (temp_arr[___] >> 7) state++; //amount of pressed keys
			}
			for (int ___ = 1; ___ < 4; ___++)
			{
				//do not distinguish L and R keys, at the moment at least
				if ((arr_k[vk_i].keys[___] == VK_LSHIFT) || (arr_k[vk_i].keys[___] == VK_RSHIFT)) arr_k[vk_i].keys[___] = VK_SHIFT;
				if ((arr_k[vk_i].keys[___] == VK_CONTROL) || (arr_k[vk_i].keys[___] == VK_RCONTROL)) arr_k[vk_i].keys[___] = VK_CONTROL;
				if ((arr_k[vk_i].keys[___] == VK_LMENU) || (arr_k[vk_i].keys[___] == VK_RMENU)) arr_k[vk_i].keys[___] = VK_MENU;
				if (arr_k[vk_i].keys[___] != 0)
				{
					if (temp_arr[arr_k[vk_i].keys[___]] >> 7)
					{
					}
					else
					{
						match = 0; //not pressed riquired key
					}
				}
			}
			if (needed_state != state) match = 0;
			if (match) return ((DWORD)arr_k[vk_i].way)|(((DWORD)vk_i) << 8);
			//continue trying other keyshorts
		}
	}
	return 0;
}

int change_text(int way)
{
	int out=0;
		if (IsClipboardFormatAvailable(CF_UNICODETEXT))
		{
			if (OpenClipboard(NULL))
			{
				HANDLE hglb;
				hglb = GetClipboardData(CF_UNICODETEXT);
				if (hglb != NULL)
				{
					CStringW str;
					LPTSTR lpstr;
					WCHAR* cdata = (WCHAR*)GlobalLock(hglb);
					str = cdata;
					GlobalUnlock(hglb);
					HANDLE hlcid = GetClipboardData(CF_LOCALE);
					LCID* read_lcid = (LCID*)GlobalLock(hlcid);
					GlobalUnlock(hlcid);
					if (!str.IsEmpty())
					{
						int code;
						//loading func
						HMODULE l_mod;
						l_mod = LoadLibraryA("DLL_Try.dll");
						if (l_mod)
						{
							if (way == 1)
							{
								void(*pFunc) (CStringW&);
								pFunc = (void(*)(CStringW&)) GetProcAddress(l_mod, "_modificate6");
								if (pFunc != NULL)
								{
									pFunc(str);
									out = 0;
								}
								else out = 6; //function download error
							}
							if (way==2)
							{
								void(*pFunc) (CStringW&,int&);
								int useless_code;
								pFunc = (void(*)(CStringW&,int&)) GetProcAddress(l_mod, "_modificate5");
								if (pFunc != NULL)
								{
									pFunc(str,useless_code);
									out = 0;
								}
								else out = 6; //function download error
							}
							FreeLibrary(l_mod);
						}//uploading func
						else out = 5; //library download error 
						EmptyClipboard();
						hglb = GlobalAlloc(GMEM_DDESHARE, sizeof(WCHAR)*(str.GetLength() + 1));
						HANDLE g_lcid;
						LCID* lcid;
						g_lcid = GlobalAlloc(GMEM_MOVEABLE, sizeof(LCID));
						lcid = (LCID*)GlobalLock(g_lcid);
						*lcid = *read_lcid;
						GlobalUnlock(g_lcid);
						SetClipboardData(CF_LOCALE, g_lcid);
						cdata = (WCHAR*)GlobalLock(hglb);
						memcpy(cdata, (WCHAR*)str.GetString(), sizeof(WCHAR)*(str.GetLength() + 1));
						GlobalUnlock(hglb);
						SetClipboardData(CF_UNICODETEXT, hglb);
					}
					else out = 4; //empty str
				}
				else out = 3; //can't get data
				CloseClipboard();
			}
			else out = 2; //can't open clipboard
		}
		else out = 1;	//not approprite format
	return out;
}

DWORD WINAPI ThreadProc(LPVOID lp_info)
{
	DWORD result;
	result=WaitForSingleObject(h_event, 600);
	if (result == WAIT_TIMEOUT)
	{
		PostMessage(h_main_window, WM_NULL, 12, 10998);
		return 1;
	}
	return 0;
}

//input - main window's process id (aka PID)
//return 0 - success, 1- could not find handle, 2 - AddCliboardFormaListener error
int SetMainToListeningClipboard(DWORD main_id)
{
	T_T temp;
	temp.handle = NULL;
	temp.desired_id = main_id;
	if (0 == EnumWindows(EnumWindowsProc, (LPARAM)(&temp)))
	{
		if (ERROR_SUCCESS == GetLastError()) //see mdsn EnumWindows()
		{
			if (TRUE == AddClipboardFormatListener(temp.handle))
			{
				PostMessage(temp.handle, WM_NULL, 12, 10999);//want to set 'clip_counter' in main to 0
				return 0;
			}
			else return 2;
		}
		else return 1;
	}
	else //probably is not ever happening 
	{
		if (NULL == temp.handle) return 1;
		else
		{
			if (TRUE == AddClipboardFormatListener(temp.handle))
			{
				PostMessage(temp.handle, WM_NULL, 12, 10999);//want to set 'counter' in main to 0
				return 0;
			}
			else return 2;
		}
	}
}

//input - main window's process id, and debug stream 
//return 0 - success, 1- could not find handle, 2 - AddCliboardFormaListener error
int SetMainToListeningClipboard(DWORD main_id, std::ofstream &O_O) 
{
	if (h_main_window != NULL)
	{
		O_O << "Using old handle" << std::endl;
		if (TRUE == AddClipboardFormatListener(h_main_window))//access rights?
		{
			PostMessage(h_main_window, WM_NULL, 12, 10999);//want to set 'clip_counter' in main to 0
			h_event = CreateEvent(NULL, FALSE, FALSE, NULL);
			if (h_event == NULL)
			{
				O_O << "!Failed to create event, error: #" << GetLastError() << std::endl;
			}
			else
			{
				O_O << "Event created" << std::endl;
				h_thread = CreateThread(NULL, 0, ThreadProc, 0, 0, &thread_id);
				if (NULL == h_thread)
				{
					O_O << "!Failed to create thread, error: #" << GetLastError() << std::endl;
				}
			}
			O_O << "\t#clipboard listener set up, simulating copying" << std::endl;
			return 0;
		}
		O_O << "wrong old handle" << std::endl;
	}
	T_T_debug temp;
	temp.handle = NULL;
	temp.desired_id = main_id;
	temp.debug = &O_O;
	O_O<< "main id before searching: " << temp.desired_id << std::endl;
	if (0 == EnumWindows(EnumWindowsProc_debug, (LPARAM)(&temp)))
	{
		if (ERROR_SUCCESS == GetLastError()) //see mdsn EnumWindows()
		{
			if (TRUE == AddClipboardFormatListener(temp.handle))//access rights?
			{
				h_main_window = temp.handle;
				O_O<< std::endl;
				PostMessage(temp.handle, WM_NULL, 12, 10999);//want to set 'clip_counter' in main to 0
				h_event = CreateEvent(NULL, FALSE, FALSE, NULL);
				if (h_event == NULL)
				{
					O_O << "!Failed to create event, error: #" << GetLastError() << std::endl;
				}
				else
				{
					O_O << "event created" << std::endl;
					h_thread = CreateThread(NULL, 0, ThreadProc, 0, 0, &thread_id);
					if (NULL == h_thread)
					{
						O_O << "!Failed to create thread, error: #" << GetLastError() << std::endl;
					}
				}
				O_O << "\t#clipboard listener set up, simulating copying" << std::endl;
				return 0;
			}
			else
			{
				O_O<< "ERROR clipboard listener set up" << std::endl;
				return 2;
			}
		}
		else
		{
			O_O<< "ERROR getting main handle" << std::endl;
			return 1;
		}
	}
	else return 3;
	return 0;
}

//input - main window's process id 
//return 0 - success, 1- could not find handle, 2 - AddCliboardFormaListener error
int RemoveMainFromListeningClipboard(DWORD main_id)
{
	T_T temp;
	temp.handle = NULL;
	temp.desired_id = main_id;
	if (0 == EnumWindows(EnumWindowsProc, (LPARAM)(&temp)))
	{
		if (ERROR_SUCCESS == GetLastError())
		{
			if (TRUE == RemoveClipboardFormatListener(temp.handle))	return 0;
			else return 2;
		}
		else return 1;
	}
	else
	{
		if (NULL == temp.handle) return 1;
		else
		{
			if (TRUE == RemoveClipboardFormatListener(temp.handle)) return 0;
			else return 2;
		}
	}
}

//input - main window's process id, and debug stream 
//return 0 - success, 1- could not find handle, 2 - AddCliboardFormaListener error
int RemoveMainFromListeningClipboard(DWORD main_id, std::ofstream &O_O)
{
	if (h_main_window != NULL)
	{
		O_O << "Using old handle" << std::endl;
		if (TRUE == RemoveClipboardFormatListener(h_main_window))
		{
			O_O << "successful listener removing" << std::endl;
			return 0;
		}
		O_O << "wrong old handle" << std::endl;
	}
	T_T_debug temp;
	temp.handle = NULL;
	temp.desired_id = main_id;
	temp.debug = &O_O;
	if (0 == EnumWindows(EnumWindowsProc_debug, (LPARAM)(&temp)))
	{
		if (ERROR_SUCCESS == GetLastError())
		{
			if (TRUE == RemoveClipboardFormatListener(temp.handle))
			{
				h_main_window = temp.handle;
				O_O << "successful listener removing" << std::endl;
				return 0;
			}
			else
			{
				O_O << "ERROR listener removing" << std::endl;
				return 2;
			}
		}
		else
		{
			O_O << "ERROR getting main handle" << std::endl;
			return 1;
		}
	}
	else return 3;
	return 0;
}

void simulate_copying(void)
{
	INPUT I_T[4];
	I_T[0].type = INPUT_KEYBOARD;
	I_T[0].ki.time = NULL;
	I_T[0].ki.wVk = VK_LCONTROL;
	I_T[0].ki.wScan = 0;
	I_T[0].ki.dwFlags = 0;
	I_T[0].ki.dwExtraInfo = 0;
	I_T[1].type = INPUT_KEYBOARD;
	I_T[2].type = INPUT_KEYBOARD;
	I_T[1].ki.time = NULL;
	I_T[2].ki.time = NULL;
	I_T[1].ki.wVk = VK_INSERT;
	I_T[2].ki.wVk = VK_INSERT;
	I_T[1].ki.wScan = 0;
	I_T[2].ki.wScan = 0;
	I_T[1].ki.dwFlags = 0;
	I_T[2].ki.dwFlags = KEYEVENTF_KEYUP;
	I_T[1].ki.dwExtraInfo = 0;
	I_T[2].ki.dwExtraInfo = 0;
	I_T[3].type = INPUT_KEYBOARD;
	I_T[3].ki.time = NULL;
	I_T[3].ki.wVk = VK_LCONTROL;
	I_T[3].ki.wScan = 0;
	I_T[3].ki.dwFlags = KEYEVENTF_KEYUP;
	I_T[3].ki.dwExtraInfo = 0;
	SendInput(4, I_T, sizeof(I_T[0]));
}

void test_shift_behavior(void)
{
	INPUT I_T[2];
	I_T[0].type = INPUT_KEYBOARD;
	I_T[1].type = INPUT_KEYBOARD;
	I_T[0].ki.time = NULL;
	I_T[1].ki.time = NULL;
	I_T[2].ki.time = NULL;
	I_T[3].ki.time = NULL;
	I_T[0].ki.wVk = VK_LSHIFT;
	I_T[1].ki.wVk =0;
	I_T[0].ki.wScan = 0;
	I_T[1].ki.wScan = MapVirtualKey(VK_LSHIFT, MAPVK_VK_TO_VSC);
	I_T[0].ki.dwFlags = 0;
	I_T[1].ki.dwFlags = 0;
	I_T[0].ki.dwExtraInfo = 0;
	I_T[1].ki.dwExtraInfo = 0;
	SendInput(1, I_T, sizeof(I_T[0]));
}

void simulate_inserting(void)
{
	//I_T[1].ki.wScan = MapVirtualKey(VK_LSHIFT, MAPVK_VK_TO_VSC);
	INPUT I_T[3] = { 0, 0, 0};
	I_T[0].type = INPUT_KEYBOARD;
	I_T[1].type = INPUT_KEYBOARD;
	I_T[2].type = INPUT_KEYBOARD;
	I_T[0].ki.wVk = VK_LSHIFT;
	I_T[1].ki.wVk = VK_INSERT; 
	I_T[2].ki.wVk = VK_INSERT;
	I_T[2].ki.dwFlags = KEYEVENTF_KEYUP;
	SendInput(3, I_T, sizeof(I_T[0]));
}
void simulate_key_up(WORD vk_code)
{
	INPUT I_T;
	I_T.type = INPUT_KEYBOARD;
	I_T.ki.time = NULL;
	I_T.ki.wVk = vk_code;
	I_T.ki.wScan = 0;
	I_T.ki.dwFlags = KEYEVENTF_KEYUP;
	I_T.ki.dwExtraInfo = 0;
	SendInput(1, &I_T, sizeof(I_T));
}

BOOL CALLBACK EnumWindowsProc_debug(HWND hwnd, LPARAM lpar)
{
	DWORD id;
	GetWindowThreadProcessId(hwnd, &id);
	(*((T_T_debug*)lpar)->debug) << "ID: " << id<<"\t";
	if (((T_T_debug*)lpar)->desired_id == id)
	{
		((T_T_debug*)lpar)->handle = hwnd;
		SetLastError(ERROR_SUCCESS);
		return FALSE;
	}
	return TRUE;
}

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


LRESULT CALLBACK text_hook(int code, DWORD wpar, DWORD lpar)
{
	switch (code)
	{
	case HC_ACTION:
	{
		std::ofstream O_O;
		KBDLLHOOKSTRUCT *info = (KBDLLHOOKSTRUCT *)lpar;
		
		O_O.open("lastlog.txt", std::ostream::app);
		O_O << std::endl;
		O_O << "action captured: " << info->vkCode;
		if (wpar == WM_KEYDOWN)	O_O << " DOWN" << std::endl;
		else O_O << " UP" << std::endl;
		O_O << "stage is: " << stage<< std::endl;

		if ((unclear_counter)&&(1 == stage) && ((info->vkCode == VK_SHIFT) || (info->vkCode == VK_RSHIFT) || (info->vkCode == VK_LSHIFT)) && (wpar == WM_KEYUP))
		{
			unclear_counter--;
			O_O << "\t#undesirable SHIFT upping preventing !!!" << std::endl;	//somehow I get excess LSHIFT UP message  
			return 1;															//after having generated SHIFT (Any: L,R,_) DOWN message
		}																		//(regardlessly using keybd_event or SendInput)
		DWORD temp = intercept_shortcut(info, wpar,O_O);
		O_O << std::hex << "temp = " << temp << std::dec << std::endl;
		if (temp)
		{
			modification = (temp&0x000000ff);
			O_O << "modififcation: " << modification<<std::endl;
			SHORT YYF = temp >> 8;
			O_O << "shortcut intercepted" << std::endl;
			if (0 == SetMainToListeningClipboard(main_id,O_O))
			{
				for (int P_0 = 0; P_0 < 4; P_0++)
				{
					if (arr_k[YYF].keys[P_0] != 0)
					{
						O_O << "sent stage 0 (" << P_0[YYF[arr_k].keys] << ") UP" << std::endl;
						simulate_key_up(P_0[YYF[arr_k].keys]);
					}
				}
				//O_O << "sending LSHIFT up" << std::endl;
				//simulate_key_up(VK_LSHIFT);
				O_O << "sent stage 0 LCONTROL (162) DOWN" << std::endl;
				O_O << "sent stage 0 INSERT (45) DOWN" << std::endl;
				O_O << "sent stage 0 INSERT (45) UP" << std::endl;
				O_O << "sent stage 0 LCONTROL (162) UP" << std::endl;
				simulate_copying();
				O_O << "Emulated coping: wrote 1" << std::endl;
				stage = 1;
				return 1; //not passing trigger key
			}
			else
			{
				O_O << "Error #" << GetLastError() << std::endl;
			}
		}
		if ((1 == stage) && (info->vkCode == 0xE8))//unassigened key, used as signal
		{
			O_O << "\t#stage 1 intercepted: 0xE8" << std::endl;
			unclear_counter = SHIFT_UP_PREVENTING;
			SetEvent(h_event);
			DWORD wait_result = WaitForSingleObject(h_thread, 2000);
			switch (wait_result)
			{
			case WAIT_TIMEOUT:
			{
				O_O << "thread have not responded" << std::endl;
				TerminateThread(h_thread, 2);
				break;
			}
			case WAIT_FAILED:
			{
				O_O << "WaitForSingleObject failed: #" << GetLastError() << std::endl;
				break;
			}
			}
			if (!CloseHandle(h_event))
			{
				O_O << "CloseHandle failed: #" << GetLastError() << std::endl;
			}
			int s = change_text(modification);
			if (!s)
			{
				O_O << "text modificated" << std::endl;
			}
			else
			{
				O_O << "error text modification: wrote 0" << std::endl;
				O_O << "error: " <<s<<" error code:"<<GetLastError()<< std::endl;
				stage = 0;
				if (0 == RemoveMainFromListeningClipboard(main_id,O_O))
				{
					O_O << "Succeessful clipboard listener removing" << std::endl;
				}
				else
				{
					O_O << "Error: " << GetLastError() << std::endl;
				}
				O_O << "\t#finished process" << std::endl;
				//simulate_key_up(0xE8);//for initial keyboard state
				return 1; //not passing virtual key
			}
			O_O << "\t#Emulating inserting text" << std::endl;
			//O_O << "sent stage 1 LCtrl (162) UP" << std::endl;
			O_O << "sent stage 1 LSHIFT (160) DOWN" << std::endl;
			O_O << "sent stage 1 INSERT (45) DOWN" << std::endl;
			O_O << "sent stage 1 INSERT (45) UP" << std::endl;
			simulate_inserting();
			
			O_O << "\t#Emulated inserting: wrote 2" << std::endl;
			stage = 2;
			O_O << "Sent LSHIFT (160) UP" << std::endl;
			simulate_key_up(VK_LSHIFT);
			return 1; //not passing virtual key
		}
		if ((1 == stage) && (info->vkCode == 0x0E))//unassigened key, timeout copying time
		{
			O_O << "copying waiting timeout!" << std::endl;
			unclear_counter = SHIFT_UP_PREVENTING;
			stage = 0;
			DWORD wait_result = WaitForSingleObject(h_thread, 50);
			switch (wait_result)
			{
			case WAIT_TIMEOUT:
			{
				O_O << "thread have not responded" << std::endl;
				TerminateThread(h_thread, 2);
				break;
			}
			case WAIT_FAILED:
			{
				O_O << "WaitForSingleObject failed: #" << GetLastError() << std::endl;
				break;
			}
			}
			if (!CloseHandle(h_event))
			{
				O_O << "CloseHandle failed: #" << GetLastError();
			}
			if (0 == RemoveMainFromListeningClipboard(main_id, O_O))
			{
				//O_O << "Succeessful clipboard listener removing" << std::endl;
			}
			else
			{
				O_O << "Error: " << GetLastError() << std::endl;
			}
			O_O << "\t#finished process" << std::endl;
			return 1; //not passing virtual key
		}
		if ((stage == 2) && (info->vkCode == VK_LSHIFT) && (wpar == WM_KEYUP))
		{
			O_O << "\t#stage 2 intercepted: LSHIFT (160) UP" << std::endl;
			O_O << "wrote 0" << std::endl;
			stage = 0;
			if (0 == RemoveMainFromListeningClipboard(main_id,O_O))
			{
				//O_O << "Succeessful clipboard listener removing" << std::endl;
			}
			else
			{
				O_O << "Error: " << GetLastError() << std::endl;
			}
			O_O << "\t#finished process" << std::endl;
		}
		O_O << "closing log file" << std::endl;
		O_O.close();
		break;
	}
	}
	return CallNextHookEx(NULL, code, wpar, lpar);
}
