//#include <Windows.h>
#include <afx.h>
#include <fstream>
#include <limits>
//#include <iostream>
#include <vector>
extern "C" __declspec (dllexport) LRESULT CALLBACK text_hook(int code, DWORD wpar, DWORD lpar);

extern "C" __declspec (dllexport) void initialize(BYTE* buffer);
extern "C" __declspec (dllexport) void upload(void);
